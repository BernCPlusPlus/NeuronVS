///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: RemoteDriverWin.cpp,v $
// $Revision: 1.6 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "0_lib/usbrc/win/hvnlib.h"
#include "../RemoteDriver.h"


void stDevReadCb( unsigned char *buf, int numremotes, void *parent );

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
  int  mPool;
  struct
  {
    float anv;    // angle value
    float ans;    // angle scale
    float anr;    // angle range

  }       mCsData[2];

  HVNHANDLE mHvn;
};


#define NUM_RDS 16

static RemoteDriverInfo *stRd[NUM_RDS] = {0};

#define pRemoteDriverInfo ((RemoteDriverInfo *)Handle)


///////////////////////////////////////////////////////////////////////////////
// RemoteDriver:: methods


///////////////////////////////////////////////////////////////////////////////
// RemoteDriver

RemoteDriver::RemoteDriver()
{
  Handle = 0;
}


///////////////////////////////////////////////////////////////////////////////
// ~RemoteDriver

RemoteDriver::~RemoteDriver()
{
}


///////////////////////////////////////////////////////////////////////////////
// Open

#define SIN45 0.70710678119 // same as COS45 or sqr(2)
#define CSANS(val) (((2*SIN45-1)/(SIN45*SIN45)) / ((val)*(val)))
#define CSANR(val) (SIN45*SIN45*(val)*(val))

bool RemoteDriver::Open()
{
  if(!pRemoteDriverInfo)
  {
    Handle = new RemoteDriverInfo;
    if(pRemoteDriverInfo)
    {
      float max0,max1;
      
      max0=max1 = 128.;
      pRemoteDriverInfo->mPool = -1;
      pRemoteDriverInfo->mButton = 0;
      pRemoteDriverInfo->mDial = 0;
      pRemoteDriverInfo->mStick = 0;
      pRemoteDriverInfo->mAllowCb = 0;
      pRemoteDriverInfo->mDenyCb = 0;
      pRemoteDriverInfo->mHvn = HVNUSB_Open();
      HVNUSB_SetReadCallback(pRemoteDriverInfo->mHvn,stDevReadCb,Handle);
      pRemoteDriverInfo->mCsData[0].anv = 0;
      pRemoteDriverInfo->mCsData[0].ans = (float)CSANS(max1);
      pRemoteDriverInfo->mCsData[0].anr = (float)CSANR(max0);
      pRemoteDriverInfo->mCsData[1].anv = 0;
      pRemoteDriverInfo->mCsData[1].ans = (float)CSANS(max0);
      pRemoteDriverInfo->mCsData[1].anr = (float)CSANR(max1);
    }
  }
  pRemoteDriverInfo->mFirst = true;
  for(int i=0; i<NUM_RDS; i++)
  {
    if(!stRd[i])
    {
      stRd[i] = pRemoteDriverInfo;
      pRemoteDriverInfo->mPool = i;
      break;
    }
  }

  return true;
}


///////////////////////////////////////////////////////////////////////////////
// Close

void RemoteDriver::Close()
{
  if(pRemoteDriverInfo)
  {
    int i=pRemoteDriverInfo->mPool;

    if(i>=0 && i<NUM_RDS) stRd[i] = 0;
    SetLed(false,false,false);
    HVNUSB_SetReadCallback(pRemoteDriverInfo->mHvn,0,0);
    HVNUSB_Close(pRemoteDriverInfo->mHvn);
    Handle = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
// SetLed

void RemoteDriver::SetLed(bool led1, bool led2, bool led3)
{
  if(pRemoteDriverInfo)
  {
    unsigned char buf[8];

    buf[0] = 0;
    buf[1] = 0;
    buf[2] = led3?128:0;
    buf[3] = led2?128:0;
    buf[4] = led1?128:0;
    HVNUSB_WriteMsg(pRemoteDriverInfo->mHvn,buf);
    pRemoteDriverInfo->mFirst = true;
  }
};


///////////////////////////////////////////////////////////////////////////////
// SeFirst

void RemoteDriver::SetFirst(bool first)
{
  if(pRemoteDriverInfo)
  {
    pRemoteDriverInfo->mFirst = first;
  }
}

///////////////////////////////////////////////////////////////////////////////
//

void RemoteDriver::GrabFocus( void )
{
  if(pRemoteDriverInfo)
  {
    HVNUSB_GrabFocus(pRemoteDriverInfo->mHvn);
  }
}


///////////////////////////////////////////////////////////////////////////////
// 

void RemoteDriver::SetButtonCbfoc( void (*button)(bool, void *), void *parent)
{
  if(pRemoteDriverInfo)
  {
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
  if(pRemoteDriverInfo)
  {
    pRemoteDriverInfo->mDenyCb = authcb ? authcb[0] : 0;
    pRemoteDriverInfo->mAllowCb = authcb ? authcb[1] : 0;
    pRemoteDriverInfo->mAuthParent = parent;
    stDevReadCb(0,HVNUSB_GetNumRemotes(),pRemoteDriverInfo);
  }
}


///////////////////////////////////////////////////////////////////////////////
// RemoteDriverInfo:: methods


///////////////////////////////////////////////////////////////////////////////
// stDevReadCb, this is static, so be carefull

void stDevReadCb(unsigned char *buf, int numremotes, void *parent)
{
  static int blockx = -1, blocky = -1;
  static unsigned char x,y,b;
	static signed char e,enc[4]={0};
	static unsigned int lasti;
	static unsigned long cnt=0;
	unsigned int i;
  static int stNumRcs = -1;
  RemoteDriverInfo *rd = (RemoteDriverInfo *)parent;


  if(stNumRcs != numremotes)
  {
    for(i=0; i<NUM_RDS; i++)
    {
      rd = stRd[i];
      if(!rd)
        continue;

      if(numremotes)
      {
        if(rd->mAllowCb)
        {
          rd->mAllowCb(rd->mAuthParent);
          stNumRcs = numremotes;
        }
      }
      else
      {
        if(rd->mDenyCb)
        {
          rd->mDenyCb(rd->mAuthParent);
          stNumRcs = numremotes;
        }
      }
    }
  }

  if(buf)
  {
    int upddial=0;

	  i=buf[1]&0x0F;						// remote index
	  cnt++;

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
            float stick = (float)(buf[3+index]) - (float)128.;
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
		  //i=decode(buf,HVNUSB_GetRcID(rd->mHvn,-1));
		  //printf("Key value %d: %d [%s]\n",buf[2],buf[3],i?"valid":"invalid");
		  break;

	  case 0x20:
		  //i=decode(buf,HVNUSB_GetRcID(rd->mHvn,-1));
		  //printf("App index %d [%s]\n",buf[2],i?"valid":"invalid");
		  break;

	  case 0x30:
		  //i=decode(buf,HVNUSB_GetRcID(rd->mHvn,-1));
		  //printf("RC index %d [%s]\n",buf[2],i?"valid":"invalid");
		  break;
	  }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: RemoteDriverWin.cpp,v $
// Revision 1.6  2004/12/02 15:24:14  joffe
// instance reference list added
//
// Revision 1.5  2004/10/05 16:53:09  joffe
// dropdown-menu implementation
//
// Revision 1.4  2004/09/29 09:56:41  joffe
// fisheye scaling added
//
// Revision 1.3  2004/09/28 02:29:40  joffe
// first blister-show implementation
//
// Revision 1.2  2004/08/26 01:05:20  joffe
// dial, stick and auth added
//
// Revision 1.1  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
///////////////////////////////////////////////////////////////////////////////
