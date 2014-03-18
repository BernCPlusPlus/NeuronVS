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

#include <stdio.h>
#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>
#include <ApplicationServices.h>

#include "../RemoteDriver.h"


struct RemoteDriverInfo
{
	static void stEmpty( char *, short, void * ){};
	
	void (*GetBuffer)( char *buf, short size, void *parent );
	void *GetBufferParent;
	
	void (*mButton)(bool, void *);
	void *mButtonParent;
	
	void (*mDial)(signed char [4], void *);
	void *mDialParent;
	
	void (*mStick)(unsigned char [2], void *);
	void *mStickParent;
	
	void (*mAllowCb)(void*);
	void (*mDenyCb)(void*);
	void *mAuthParent;
	
	bool mFirst;
	struct
	{
		float anv;    // angle value
		float ans;    // angle scale
		float anr;    // angle range
		
	}       mCsData[2];
};

#define pRemoteDriverInfo ((RemoteDriverInfo *)Handle)


/*static*/ class RemoteDriverPool
{
	friend class RemoteDriver;
	
public:
	RemoteDriverPool();
	~RemoteDriverPool();
	
	int mNumRcs;
	int mNumIns;
	bool mActive;
	
private:
	unsigned char mBuf[8];
	UInt32 mInPipe, mOutPipe;
	UInt8  mInPipeRef, mOutPipeRef;
	CFRunLoopRef mPipeLoop;
	CFRunLoopRef mTaskLoop;
	
	IOUSBInterfaceInterface **mUsbIf;
	IOUSBDeviceInterface    **mDev;

	MPQueueID mMpQueue;
	MPTaskID  mMpTask;
	
	// this doesn't exist if the plug in is deinstantiated! We need to zap it before leaving...
	RemoteDriverInfo *mFocDriverInfo;
	
	static OSStatus stTask(void *whoknows);
	static void stDevAttachedCb(void *refCon, io_iterator_t iterator);
	static void stDevDetachedCb(void *refCon, io_iterator_t iterator);
	static void stDevReadCb(void *vintf, IOReturn result, void *arg0);
	
	void ServeDevice(io_service_t usbDeviceRef);
	void ServeInterface(io_service_t usbInterfaceRef);
	void ServePipes(IOUSBInterfaceInterface **intf, UInt8 numPipes);
	
};


