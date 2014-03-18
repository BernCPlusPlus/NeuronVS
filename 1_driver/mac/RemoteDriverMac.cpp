///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: RemoteDriverMac.cpp,v $
// $Revision: 1.7 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "RemoteDriverMac.h"

RemoteDriverPool *gstRemoteDriverPool = NULL;



///////////////////////////////////////////////////////////////////////////////
// Tooling

///////////////////////////////////////////////////////////////////////////////
//

static int GetStringDescriptor(IOUSBDeviceInterface **deviceIntf, UInt8 descIndex, char *buf, UInt16 len, UInt16 lang)
{
	//printf("NukeDbg: GetStringDescriptor\n"); fflush(stdout);
	
	IOUSBDevRequest req;
	int stringLen,i;
	IOReturn err;
	
	if(!lang) lang=0x0409;
	
	req.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBDevice);
	req.bRequest = kUSBRqGetDescriptor;
	req.wValue = (kUSBStringDesc << 8) | descIndex;
	req.wIndex = lang;
	req.wLength = len;
	req.pData = buf;
	err = (*deviceIntf)->DeviceRequest(deviceIntf, &req);
	if ( (err != kIOReturnSuccess) && (err != kIOReturnOverrun) )
	{
		return -1;
	}
	
	stringLen = buf[0];
	
	if(stringLen)
	{
		// convert unicode to ascii
		stringLen>>=1;
		for(i=0; i<stringLen; i++) buf[i]=buf[2+i+i];
		buf[--i]=0;  
		stringLen = req.wLenDone;
	}
	return stringLen;  
}


///////////////////////////////////////////////////////////////////////////////
// RemoteDriverPool:: methods

///////////////////////////////////////////////////////////////////////////////
//
int RaiseThreadSafeAlert(double timeout, CFStringRef alertHeader, CFStringRef alertMessage, CFStringRef defaultButtonTitle, CFStringRef alternateButtonTitle, CFStringRef otherButtonTitle);

RemoteDriverPool::RemoteDriverPool()
{
	//	RaiseThreadSafeAlert(0, CFSTR("RemoteDriverPool::RemoteDriverPool"), CFSTR("Yess"), CFSTR("OK"), NULL, NULL);
	
#ifdef VERBOSE
	printf("NukeDbg: RemoteDriverPool\n"); fflush(stdout);
#endif
	mNumRcs = 0;
	mNumIns = 0;
	mUsbIf = 0;
	mFocDriverInfo = NULL;
	mInPipeRef=mOutPipeRef = 0;
	mTaskLoop=mPipeLoop = 0;
	mActive = true;
	mMpQueue = NULL;
	mMpTask = NULL;
	mDev = NULL;
	
	long a=0,b=0;
	OSErr err = MPCreateQueue(&mMpQueue);
	if (err!=noErr)
		printf("MPCreateTask failed");
	
	err = MPCreateTask(this->stTask,0,8192,mMpQueue,&a,&b,0,&mMpTask);
	if (err!=noErr)
		printf("MPCreateTask failed");
}


///////////////////////////////////////////////////////////////////////////////
//

RemoteDriverPool::~RemoteDriverPool()
{
#ifdef VERBOSE
	printf("NukeDbg: ~RemoteDriverPool\n"); fflush(stdout);
#endif
	mActive = false;
	if (gstRemoteDriverPool) {
		if(gstRemoteDriverPool->mPipeLoop)
		{
			CFRunLoopStop(gstRemoteDriverPool->mPipeLoop);
		}
		if(gstRemoteDriverPool->mTaskLoop)
		{
			CFRunLoopStop(gstRemoteDriverPool->mTaskLoop);
		}
	}
	//TODO: exchange wait with a task-handshake-mechanism
	//SMB  Sleep(1);
	//printf("NukeDbg: ~pool\n");
	MPTerminateTask(mMpTask,noErr);
	
}


///////////////////////////////////////////////////////////////////////////////
//

OSStatus RemoteDriverPool::stTask(void *whoknows)
{
#ifdef VERBOSE
	printf("NukeDbg: stTask\n"); fflush(stdout);
#endif
	
	sleep(1);
	
	if (!gstRemoteDriverPool)
		return -1;
	
	kern_return_t		err;
	IONotificationPortRef notificationObject;
	CFRunLoopSourceRef notificationRunLoopSource;
	CFMutableDictionaryRef 	matchingDictionary = 0;		// requires <IOKit/IOKitLib.h>
	mach_port_t 	masterPort = 0;				// requires <mach/mach.h>
	io_iterator_t 		iterator = 0,gAddedIter,gRemovedIter;
	
	CFNumberRef			numberRef;
	SInt32			idVendor = 0x14C7;
	SInt32			idProduct = 1;
	
	err = IOMasterPort(MACH_PORT_NULL, &masterPort);				
	if (err)
	{
		printf("Nuke: no master port (err %08x)\n", err);
		return err;
	}
	
	matchingDictionary = IOServiceMatching(kIOUSBDeviceClassName);
	if (!matchingDictionary)
	{
		printf("Nuke: no matching dictionary\n");
		return -1;
	}
	
	numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &idVendor);
	if(!numberRef)
	{
		printf("Nuke: no reference for vendor\n");
		return -1;
	}
	CFDictionaryAddValue(matchingDictionary, CFSTR(kUSBVendorID), numberRef);
	CFRelease(numberRef);
	
	numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &idProduct);
	if (!numberRef)
	{
		printf("Nuke: no reference for product\n");
		return -1;
	}
	CFDictionaryAddValue(matchingDictionary, CFSTR(kUSBProductID), numberRef);
	CFRelease(numberRef);
	
	err = IOServiceGetMatchingServices(masterPort, matchingDictionary, &iterator);
	
	notificationObject = IONotificationPortCreate(masterPort);
	notificationRunLoopSource = IONotificationPortGetRunLoopSource(notificationObject);
	
	CFRunLoopAddSource(CFRunLoopGetCurrent(), notificationRunLoopSource, kCFRunLoopDefaultMode);
	
	err = IOServiceAddMatchingNotification
	(
	 notificationObject,
	 kIOFirstMatchNotification,
	 IOServiceMatching(kIOUSBDeviceClassName),
	 gstRemoteDriverPool->stDevAttachedCb,
	 (void *)123,
	 &gAddedIter
	 );
	if(err != KERN_SUCCESS) return -1;
    
	err = IOServiceAddMatchingNotification
	(
	 notificationObject,
	 kIOTerminatedNotification,
	 IOServiceMatching(kIOUSBDeviceClassName),
	 gstRemoteDriverPool->stDevDetachedCb,
	 (void *)123,
	 &gRemovedIter
	 );
	if(err != KERN_SUCCESS) return -1;
    
	gstRemoteDriverPool->stDevDetachedCb(0, gRemovedIter);
	gstRemoteDriverPool->stDevAttachedCb(0, gAddedIter);
	
	//printf("NukeDbg: task running\n");
	gstRemoteDriverPool->mTaskLoop = CFRunLoopGetCurrent();
	CFRunLoopRun();
	//printf("NukeDbg: task ending\n");
	
	IOObjectRelease(iterator);
	IOObjectRelease(gAddedIter);
	IOObjectRelease(gRemovedIter);
	if (notificationObject) 
		IONotificationPortDestroy(notificationObject);
	
	mach_port_deallocate(mach_task_self(), masterPort);
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriverPool::stDevAttachedCb(void *refCon, io_iterator_t iterator)
{
	//printf("NukeDbg: stDevAttachedCb\n"); fflush(stdout);
	
	io_service_t ioDeviceObj=NULL;
	if (!gstRemoteDriverPool) return;
	RemoteDriverInfo *rd = gstRemoteDriverPool->mFocDriverInfo;
    if (!rd) return;
	
	while( ioDeviceObj = IOIteratorNext(iterator) )
	{
		if(refCon)
		{
			//printf("NukeDbg: attached\n"); fflush(stdout);
			gstRemoteDriverPool->mNumRcs++;
		}
		if(gstRemoteDriverPool->mNumRcs)
		{
			if(rd && rd->mAllowCb)
			{
				rd->mAllowCb(rd->mAuthParent);
			}
		}
		
		gstRemoteDriverPool->ServeDevice(ioDeviceObj);
		IOObjectRelease(ioDeviceObj);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriverPool::stDevDetachedCb(void *refCon, io_iterator_t iterator)
{
	//printf("NukeDbg: stDevDetachedCb\n"); fflush(stdout);
	io_service_t ioDeviceObj=NULL;
	if (!gstRemoteDriverPool) return;
	
	RemoteDriverInfo *rd = gstRemoteDriverPool->mFocDriverInfo;
	if (!rd) return;
	
	while( (ioDeviceObj = IOIteratorNext(iterator)))
	{
		if(refCon)
		{
			//printf("NukeDbg: detached\n"); fflush(stdout);
			gstRemoteDriverPool->mNumRcs--;
		}
		if(gstRemoteDriverPool->mNumRcs<=0)
		{
			gstRemoteDriverPool->mNumRcs = 0;
			if(rd && rd->mDenyCb)
			{
				rd->mDenyCb(rd->mAuthParent);
			}
		}
		if(gstRemoteDriverPool->mPipeLoop)
		{
			CFRunLoopStop(gstRemoteDriverPool->mPipeLoop);
		}
		IOObjectRelease(ioDeviceObj);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

/*
 static int led=0;
 if((Buf[2]&3) == 3)
 {
 unsigned char buf[8];
 buf[0]=buf[1] = 0;
 switch(led)
 {
 case 0:  buf[2] = 128; buf[3] = 0; buf[4] = 0; break;
 case 1:  buf[2] = 0; buf[3] = 128; buf[4] = 0; break;
 case 2:  buf[2] = 0; buf[3] = 0; buf[4] = 128; led=-1; break;
 }    
 led++;
 if(outPipeRef)
 (*intf)->WritePipe(intf, outPipeRef, buf,8);
 }
 */


static unsigned char oldtag;
static int blockx=-1, blocky=-1;
static signed char e,enc[4]={0};

void RemoteDriverPool::stDevReadCb(void *vintf, IOReturn result, void *arg0)
{
	//printf("NukeDbg: stDevReadCbb\n"); fflush(stdout);
	if (!gstRemoteDriverPool) return;
	
	IOUSBInterfaceInterface **intf = (IOUSBInterfaceInterface **)vintf;
	//static unsigned char x,y,b;
	//static unsigned int lasti;
	RemoteDriverInfo *rd = gstRemoteDriverPool->mFocDriverInfo;
	if (!rd) return;
	
	int upddial=0;
	//	unsigned int i;
	
	//printf("#"); fflush(stdout);
	
	unsigned char *buf = gstRemoteDriverPool->mBuf;
	if(oldtag != buf[2])
	{
		oldtag = buf[2];
		
		switch(result)
		{
			default:
				if(result<0)
				{
					printf("Nuke: error:%i kIOReturnVMError:%i\n",result,kIOReturnVMError); fflush(stdout);
				}
				break;
		}
		
		switch(buf[0]&0xF0)
		{
			case 0x00:
				e=buf[5] & 0xF0;
				upddial |= e;
				enc[1]+=e>>4;
				e=buf[5] & 0x0F;
				upddial |= e;
				if(e&8) e|=0xF0;
				enc[0]+=e;
				
				e=buf[6];
				upddial |= e;
				enc[2]+=e>>4;
				e=buf[6] & 0x0F;
				upddial |= e;
				if(e&8) e|=0xF0;
				enc[3]+=e;
				
				if(rd)
				{
					if(buf[2]&1 || rd->mFirst) {blockx=buf[3]; blocky=buf[4]; rd->mFirst=false;}
					if( (blockx-buf[3])>5 || (blockx-buf[3])<-5 ) blockx=-1;
					if( (blocky-buf[4])>5 || (blocky-buf[4])<-5 ) blocky=-1;
					
					//printf("%02X:%02X:%02X:%02X:%02X\n",buf[2],buf[3],buf[4],buf[5],buf[6]); fflush(stdout);
					
					if(rd->mButton && (buf[2]&2))
					{
						rd->mButton(buf[2]&1, rd->mButtonParent);
					}
					
					if(rd->mDial && upddial)
					{
						rd->mDial(enc, rd->mDialParent);
					}
					
					if(rd->mStick && blockx<0 && blocky<0)
					{
						// 'fisheye' stick, from neuron-G1
						for(int index=0; index<2; index++)
						{
							float stick = (float)(buf[3+index]) - 128.;
							rd->mCsData[index].anv = stick*stick;
							if(rd->mCsData[index].anv > rd->mCsData[index].anr) rd->mCsData[index].anv = rd->mCsData[index].anr;
							stick *= (1 + rd->mCsData[index^1].anv * rd->mCsData[index].ans);
							
							// clip
							stick = stick>127 ? 127 : stick<-128 ? -128 : stick;
							stick += 128;
							buf[3+index] = (unsigned char)stick;
						}
						rd->mStick(buf+3, rd->mStickParent);
					}
				}
				buf[2] &= ~2;
				break;
				
			case 0x10:
				//i=decode(Buf,HVNUSB_GetRcID(rd->mHvn,-1));
				//printf("Key value %d: %d [%s]\n",Buf[2],Buf[3],i?"valid":"invalid");
				break;
				
			case 0x20:
				//i=decode(Buf,HVNUSB_GetRcID(rd->mHvn,-1));
				//printf("App index %d [%s]\n",Buf[2],i?"valid":"invalid");
				break;
				
			case 0x30:
				//i=decode(Buf,HVNUSB_GetRcID(rd->mHvn,-1));
				//printf("RC index %d [%s]\n",Buf[2],i?"valid":"invalid");
				break;
		}
	}
	
	if(gstRemoteDriverPool->mActive)
	{
		(*intf)->ReadPipeAsync(intf, gstRemoteDriverPool->mInPipe, buf, 8, (IOAsyncCallback1)&(gstRemoteDriverPool->stDevReadCb), (void *)intf);
		// if attached has not been called but we received smth, we have at least
		// one remote connected
		if(!gstRemoteDriverPool->mNumRcs) gstRemoteDriverPool->mNumRcs = 1;
	}
}


///////////////////////////////////////////////////////////////////////////////
//
#define kOurVendorID			0x14C7
#define kOurProductID			0x1

void RemoteDriverPool::ServeDevice(io_service_t usbDeviceRef)
{
	//printf("NukeDbg: ServeDevice\n"); fflush(stdout);
	
	IOReturn                err;
	IOCFPlugInInterface     **iodev;
	IOUSBDeviceInterface    **dev;
	SInt32  score;
	UInt8   numConf;
	IOUSBConfigurationDescriptorPtr confDesc;
	IOUSBFindInterfaceRequest       interfaceRequest;
	io_iterator_t iterator;
	io_service_t  usbInterfaceRef;
	
	// create service
	err = IOCreatePlugInInterfaceForService(usbDeviceRef, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &iodev, &score);
	if(err || !iodev)
	{
		printf("Nuke: no service, ret=%08X, iodev=%p\n", err, iodev);
		return;
	}
	
	// query interface
	err = (*iodev)->QueryInterface(iodev, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (void **)&dev);
	IODestroyPlugInInterface(iodev);
	//  (*iodev)->Release(iodev);
	if(err || !dev)
	{
		printf("Nuke: no device interface, ret=%08X, dev=%p\n", err, dev);
		return;
	}
	
	
	{
		UInt16			vendor=0;
		UInt16			product=0;
		// technically should check these kr values
		err = (*dev)->GetDeviceVendor(dev, &vendor);
		err = (*dev)->GetDeviceProduct(dev, &product);
		//        kr = (*dev)->GetDeviceReleaseNumber(dev, &release);
		if ((vendor != kOurVendorID) || (product != kOurProductID) /*|| (release != 1)*/)
		{
			// We should never get here because the matching criteria we specified above
			// will return just those devices with our vendor and product IDs
#ifdef VERBOSE
			printf("found device I didn't want (vendor = %d, product = %d)\n", vendor, product);
#endif
			//		gError = kUnknownErr;
			(*dev)->Release(dev);
			return;
			
			//		continue;
		}
	}
	
	
	
	// open device
	err = (*dev)->USBDeviceOpen(dev);
	if(err)
	{
		printf("Nuke: unable to open device, ret = %08x\n", err);
		RaiseThreadSafeAlert(0, CFSTR("Could not open USB device"), CFSTR("The <NUKE> controller appears to be in use by another program or process. Try restarting the application and switching the device on and off by unplugging it"), CFSTR("OK"), NULL, NULL);
		return;
	}
	
	// get&set configuration
	err = (*dev)->GetNumberOfConfigurations(dev, &numConf);
	if(err || !numConf)
	{
		printf("Nuke: bad number of configurations, ret = %08x\n", err);
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		return;
	}
	printf("Nuke: found %i configurations\n", numConf);
	err = (*dev)->GetConfigurationDescriptorPtr(dev, 0, &confDesc);
	if(err)
	{
		printf("Nuke: no config descriptor for index-0\n");
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		return;
	}
	err = (*dev)->SetConfiguration(dev, confDesc->bConfigurationValue);
	if(err)
	{
		printf("Nuke: error setting configuration\n");
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		return;
	}
	
	// configure interface
	interfaceRequest.bInterfaceClass = kIOUSBFindInterfaceDontCare;		// requested class
	interfaceRequest.bInterfaceSubClass = kIOUSBFindInterfaceDontCare;		// requested subclass
	interfaceRequest.bInterfaceProtocol = kIOUSBFindInterfaceDontCare;		// requested protocol
	interfaceRequest.bAlternateSetting = kIOUSBFindInterfaceDontCare;		// requested alt setting
	
	err = (*dev)->CreateInterfaceIterator(dev, &interfaceRequest, &iterator);
	if(err)
	{
		printf("Nuke: no interface iterator\n");
		(*dev)->USBDeviceClose(dev);
		(*dev)->Release(dev);
		return;
	}
	
	//char string[256];
	//if(GetStringDescriptor(dev,1,string,256,0)) printf("NukeDbg: %s\n",string);
	//if(GetStringDescriptor(dev,2,string,256,0)) printf("NukeDbg: %s\n",string);
	//if(GetStringDescriptor(dev,3,string,256,0)) printf("NukeDbg: %s\n",string);
	
	while(usbInterfaceRef = IOIteratorNext(iterator))
	{
		//printf("NukeDbg: found interface %p\n", (void*)usbInterfaceRef);
		ServeInterface(usbInterfaceRef);
		IOObjectRelease(usbInterfaceRef);
	}
	
	IOObjectRelease(iterator);
	(*dev)->USBDeviceClose(dev);
	(*dev)->Release(dev);
}



///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriverPool::ServeInterface(io_service_t usbInterfaceRef)
{
	//printf("NukeDbg: ServeInterface\n"); fflush(stdout);
	
	IOReturn              err;
	IOCFPlugInInterface   **iodev;
	IOUSBInterfaceInterface **intf;
	SInt32  score;
	UInt8   numPipes;
	
	err = IOCreatePlugInInterfaceForService(usbInterfaceRef, kIOUSBInterfaceUserClientTypeID, kIOCFPlugInInterfaceID, &iodev, &score);
	if(err || !iodev)
	{
		printf("Nuke: no interface-plugin, ret = %08x, iodev = %p\n", err, iodev);
		return;
	}
	err = (*iodev)->QueryInterface(iodev, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID),(void **)&intf);
	//  (*iodev)->Release(iodev);
	IODestroyPlugInInterface(iodev);			// done with this
	if(err || !intf)
	{
		printf("Nuke: no device interface, ret = %08x, intf = %p\n", err, intf);
		return;
	}
	
	{
		UInt16			vendor=0;
		UInt16			product=0;
		// technically should check these kr values
		err = (*intf)->GetDeviceVendor(intf, &vendor);
		err = (*intf)->GetDeviceProduct(intf, &product);
		//        kr = (*dev)->GetDeviceReleaseNumber(dev, &release);
		if ((vendor != kOurVendorID) || (product != kOurProductID) /*|| (release != 1)*/)
		{
			// We should never get here because the matching criteria we specified above
			// will return just those devices with our vendor and product IDs
#ifdef VERBOSE
			printf("found device I didn't want (vendor = %d, product = %d)\n", vendor, product);
#endif
			//		gError = kUnknownErr;
			(*intf)->Release(intf);
			return;
			
			//		continue;
		}
	}
	
	
	err = (*intf)->USBInterfaceOpen(intf);
	if(err)
	{
		printf("Nuke: error opening interface. ret = %08x\n", err);
		return;
	}
	err = (*intf)->GetNumEndpoints(intf, &numPipes);
	if (err)
	{
		printf("Nuke: unable to get number of endpoints. ret = %08x\n", err);
		(*intf)->USBInterfaceClose(intf);
		(*intf)->Release(intf);
		return;
	}
	
	//printf("Nuke: found %d pipes\n", numPipes);
	if(numPipes == 0)
	{
		// try alternate setting 1
		err = (*intf)->SetAlternateInterface(intf, 1);
		if (err)
		{
			printf("Nuke: unable to set alternate interface 1. ret = %08x\n", err);
			(*intf)->USBInterfaceClose(intf);
			(*intf)->Release(intf);
			return;
		}
		err = (*intf)->GetNumEndpoints(intf, &numPipes);
		if (err)
		{
			printf("Nuke: unable to get number of endpoints, ret = %08x\n", err);
			(*intf)->USBInterfaceClose(intf);
			(*intf)->Release(intf);
			return;
		}
		numPipes = 13;  // workaround. GetNumEndpoints does not work after SetAlternateInterface
	}
	
	mUsbIf = intf;
	if(numPipes)
	{
		ServePipes(intf, numPipes);
	}
	
	(*intf)->USBInterfaceClose(intf);
	(*intf)->Release(intf);
}


///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriverPool::ServePipes(IOUSBInterfaceInterface **intf, UInt8 numPipes)
{
	//printf("NukeDbg: ServePipes\n"); fflush(stdout);
	
	int       i;
	IOReturn  err;			
	//  UInt8     inPipeRef = 0;
	UInt8     direction, number, transferType, interval;
	UInt16    maxPacketSize;
	
	// pipes-num start with 1, zero is the default control pipe
	for (i=1; i <= numPipes; i++)
	{
		err = (*intf)->GetPipeProperties(intf, i, &direction, &number, &transferType, &maxPacketSize, &interval);
		if(err)
		{
			printf("Nuke: error getting pipe properties for pipe %d, err = %08x\n", i, err);
			return;
		}
		if(transferType != kUSBInterrupt)
		{
			printf("Nuke: skipping non-interrupt pipe %d\n", i);
			continue;
		}
		if((direction == kUSBIn) && !mInPipeRef)
		{
			//printf("Nuke: grabbing interrupt IN pipe %d, number %d\n",i, number);
			mInPipeRef = i;
		}
		if ((direction == kUSBOut) && !mOutPipeRef)
		{
			//printf("Nuke: grabbing interrupt OUT pipe %d, number %d\n", i, number);
			mOutPipeRef = i;
		}
	}
	if(mInPipeRef && mOutPipeRef)
	{
		CFRunLoopSourceRef		cfSource;
		IOReturn			err;
		err = (*intf)->CreateInterfaceAsyncEventSource(intf, &cfSource);
		if(err)
		{
			printf("Nuke: no event source, err = %08x\n", err);
			return;
		}
		CFRunLoopAddSource(CFRunLoopGetCurrent(), cfSource, kCFRunLoopDefaultMode);
		err = (*intf)->ReadPipeAsync(intf, mInPipe=mInPipeRef, mBuf,8, (IOAsyncCallback1)&(gstRemoteDriverPool->stDevReadCb), (void*)intf);
		if(err)
		{
			printf("Nuke: ReadPipeAsyncFailed, err = %08x\n", err);
			CFRunLoopRemoveSource(CFRunLoopGetCurrent(), cfSource, kCFRunLoopDefaultMode);
			return;
		}
		
		//printf("NukeDbg: receiving data\n"); fflush(stdout);
		mPipeLoop = CFRunLoopGetCurrent();
		CFRunLoopRun();
		mOutPipeRef = 0;
		//printf("NukeDbg: receiving data finished\n"); fflush(stdout);
	}
}


///////////////////////////////////////////////////////////////////////////////
// RemoteDriver:: methods

///////////////////////////////////////////////////////////////////////////////
// RemoteDriver

RemoteDriver::RemoteDriver()
{
#ifdef VERBOSE
	printf("NukeDbg: RemoteDriver\n"); fflush(stdout);
#endif
	Handle = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// ~RemoteDriver

RemoteDriver::~RemoteDriver()
{
#ifdef VERBOSE
	printf("NukeDbg: ~RemoteDriver\n"); fflush(stdout);
#endif
	
	if(pRemoteDriverInfo)
	{
		
		pRemoteDriverInfo->mButton = NULL;
		pRemoteDriverInfo->mDial = NULL;
		pRemoteDriverInfo->mStick = NULL;
		pRemoteDriverInfo->mAllowCb = NULL;
		pRemoteDriverInfo->mDenyCb = NULL;
		
		if (Handle) {
			delete Handle;
			Handle = NULL;
		}
		
		if (gstRemoteDriverPool)
			gstRemoteDriverPool->mFocDriverInfo = NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////
// Open

#define SIN45 0.70710678119 // same as COS45 or sqr(2)
#define CSANS(val) (((2*SIN45-1)/(SIN45*SIN45)) / ((val)*(val)))
#define CSANR(val) (SIN45*SIN45*(val)*(val))

bool RemoteDriver::Open()
{
#ifdef VERBOSE
	printf("NukeDbg: Open\n"); fflush(stdout);
#endif
	if(!pRemoteDriverInfo)
	{
		Handle = new RemoteDriverInfo;
		if (gstRemoteDriverPool)
			gstRemoteDriverPool->mFocDriverInfo =  (RemoteDriverInfo *)Handle;
		
		if(pRemoteDriverInfo)
		{
			float max0,max1;
			
			max0=max1 = 128.;
			pRemoteDriverInfo->mButton = NULL;
			pRemoteDriverInfo->mDial = NULL;
			pRemoteDriverInfo->mStick = NULL;
			pRemoteDriverInfo->mAllowCb = NULL;
			pRemoteDriverInfo->mDenyCb = NULL;
			if (gstRemoteDriverPool)
				gstRemoteDriverPool->mNumIns++;
			pRemoteDriverInfo->mCsData[0].anv = 0;
			pRemoteDriverInfo->mCsData[0].ans = (float)CSANS(max1);
			pRemoteDriverInfo->mCsData[0].anr = (float)CSANR(max0);
			pRemoteDriverInfo->mCsData[1].anv = 0;
			pRemoteDriverInfo->mCsData[1].ans = (float)CSANS(max0);
			pRemoteDriverInfo->mCsData[1].anr = (float)CSANR(max1);
		}
	}
	pRemoteDriverInfo->mFirst = true;
	return true;
};


///////////////////////////////////////////////////////////////////////////////
// Close

void RemoteDriver::Close()
{
#ifdef VERBOSE
	printf("NukeDbg: Close\n"); fflush(stdout);
#endif
	if(pRemoteDriverInfo)
	{
		SetLed(false,false,false);
		if (gstRemoteDriverPool)
			if(gstRemoteDriverPool->mNumIns>0) 
				gstRemoteDriverPool->mNumIns--; 
		
	}
};


///////////////////////////////////////////////////////////////////////////////
// SetLed

void RemoteDriver::SetLed(bool led1, bool led2, bool led3)
{
#ifdef VERBOSE
	printf("NukeDbg: SetLed\n"); fflush(stdout);
#endif
	
	if (!gstRemoteDriverPool) return;
	
	if(pRemoteDriverInfo)
	{
		unsigned char buf[8];
		
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = led3?128:0;
		buf[3] = led2?128:0;
		buf[4] = led1?128:0;
		if(gstRemoteDriverPool->mOutPipeRef)
		{
			IOUSBInterfaceInterface **intf = gstRemoteDriverPool->mUsbIf;
			
			(*intf)->WritePipe(intf, gstRemoteDriverPool->mOutPipeRef, buf,8);
		}
		pRemoteDriverInfo->mFirst = true;
	}
}


///////////////////////////////////////////////////////////////////////////////
// SeFirst

void RemoteDriver::SetFirst(bool first)
{
#ifdef VERBOSE
	printf("NukeDbg: SetFirst\n"); fflush(stdout);
#endif
	if(pRemoteDriverInfo)
	{
		pRemoteDriverInfo->mFirst = first;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriver::GrabFocus( void )
{
	if (!gstRemoteDriverPool) return;
	
#ifdef VERBOSE
	printf("NukeDbg: BrabFocus\n"); fflush(stdout);
#endif
	gstRemoteDriverPool->mFocDriverInfo =  (RemoteDriverInfo *)Handle;
}


///////////////////////////////////////////////////////////////////////////////
// 

void RemoteDriver::SetButtonCbfoc( void (*button)(bool, void *), void *parent)
{
	if(pRemoteDriverInfo)
	{
#ifdef VERBOSE
		printf("NukeDbg: SetButtonCbfoc\n"); fflush(stdout);
#endif
		pRemoteDriverInfo->mButton = button;
		pRemoteDriverInfo->mButtonParent = parent;
	}
}


///////////////////////////////////////////////////////////////////////////////
// 

void RemoteDriver::SetDialCbfoc( void (*dial)(signed char [4], void *), void *parent)
{
	if(pRemoteDriverInfo)
	{
		pRemoteDriverInfo->mDial = dial;
		pRemoteDriverInfo->mDialParent = parent;
	}
}


///////////////////////////////////////////////////////////////////////////////
// 

void RemoteDriver::SetStickCbfoc( void (*stick)(unsigned char [2], void *), void *parent)
{
#ifdef VERBOSE
	printf("NukeDbg: SetStickCbfoc\n"); fflush(stdout);
#endif
	if(pRemoteDriverInfo)
	{
		pRemoteDriverInfo->mStick = stick;
		pRemoteDriverInfo->mStickParent = parent;
	}
}


///////////////////////////////////////////////////////////////////////////////
// 

void RemoteDriver::SetAuthCb( void (*authcb[2])(void *), void *parent )
{
#ifdef VERBOSE
	printf("NukeDbg: SetAuthCb\n"); fflush(stdout);
#endif
	if(pRemoteDriverInfo)
	{
		pRemoteDriverInfo->mDenyCb = authcb ? authcb[0] : 0;
		pRemoteDriverInfo->mAllowCb = authcb ? authcb[1] : 0;
		pRemoteDriverInfo->mAuthParent = parent;
		if (gstRemoteDriverPool) {
			if(gstRemoteDriverPool->mNumRcs)
			{
				if(pRemoteDriverInfo->mAllowCb)
				{
					pRemoteDriverInfo->mAllowCb(pRemoteDriverInfo->mAuthParent);
				}
			}
			else
			{
				if(pRemoteDriverInfo->mDenyCb)
				{
					pRemoteDriverInfo->mDenyCb(pRemoteDriverInfo->mAuthParent);
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: RemoteDriverMac.cpp,v $
// Revision 1.7  2004/11/17 16:24:24  joffe
// statics moved out of function-bodies
//
// Revision 1.6  2004/11/03 12:45:02  joffe
// few more debug printf
//
// Revision 1.5  2004/09/29 10:22:03  joffe
// fisheye scaling added
//
// Revision 1.4  2004/09/29 06:34:18  joffe
// blister-show mac-adaptions
//
// Revision 1.3  2004/09/15 22:40:37  joffe
// crash removed/small improvements
//
// Revision 1.2  2004/09/09 03:15:19  joffe
// first working version
//
// Revision 1.1  2004/08/14 07:14:28  joffe
// initial revision
//
// Revision 1.1  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
///////////////////////////////////////////////////////////////////////////////
