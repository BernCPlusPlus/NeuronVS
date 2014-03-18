///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CRemote.cpp,v $
// $Revision: 1.7 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "CRemote.h"
#include "RemoteDriver.h"


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CRemoteInfo
{
public:

  friend class CRemote;

  CRemoteInfo();
	~CRemoteInfo();

  static void stNtfStick1Cb( float *val, CParam *param, void **inf );
  static void stNtfStick2Cb( float *val, CParam *param, void **inf );
  static void stNtfDials( float *val, CParam *param, void **inf );

  static void stButton(bool pressed, void *this_p);
  static void stDial(signed char dial[4], void *this_p);
  static void stStick(unsigned char stick[2], void *this_p);
  static void stCheckRc(int numrcs, void *this_p);

private:
  bool mError;
  CParam *mIndex;

  CParam            *mStick1[3];
  CParam            *mStick2[3];
  CParam            *mDials[4][3];
  CParam::td_notify mNtfStick1[3];
  CParam::td_notify mNtfStick2[3];
  CParam::td_notify mNtfDials[4][3];
  RemoteDriver *mRemoteDriver;
  void (*mAllowCb)(void*);
  void (*mDenyCb)(void*);
  void *mAuthParent;
};


///////////////////////////////////////////////////////////////////////////////
//

CRemoteInfo::CRemoteInfo()
{
  int i,j;

  mError = false;
  mAllowCb = 0;
  mDenyCb = 0;

  // init some stuff
  for(i=0; i<3; i++)
  {
    mStick1[i] = 0;
    mStick2[i] = 0;
    mNtfStick1[i].clear();
    mNtfStick1[i].min = 0; mNtfStick1[i].max = 255;
    mNtfStick2[i].clear();
    mNtfStick2[i].min = 0; mNtfStick2[i].max = 255;
    for(j=0; j<4; j++)
    {
      mDials[j][i] = 0;
      mNtfDials[j][i].clear();
    }
  }

  mIndex = new CParam();
  if(mIndex)
  {
    mIndex->mMin = 0; mIndex->mMax = 2;
    mIndex->SetVal(0);
  }
  else
  {
    mError = true;
  }

  mRemoteDriver = new RemoteDriver;
  if(mRemoteDriver)
  {
    mRemoteDriver->Open();
    mRemoteDriver->SetButtonCbfoc(stButton, this);
    mRemoteDriver->SetDialCbfoc(stDial, this);
    mRemoteDriver->SetStickCbfoc(stStick, this);
  }
  else
  {
    mError = true;
  }
  stButton(false,this);
}


///////////////////////////////////////////////////////////////////////////////
//

CRemoteInfo::~CRemoteInfo()
{
  int i,j;

  if(mRemoteDriver)
  {
	  mRemoteDriver->SetButtonCbfoc(stButton, NULL);
	  mRemoteDriver->SetDialCbfoc(stDial, NULL);
	  mRemoteDriver->SetStickCbfoc(stStick, NULL);
	  mRemoteDriver->Close();
    delete mRemoteDriver;
	  mRemoteDriver = NULL;
  }

  // remove some stuff
  for(i=0; i<3; i++)
  {
    if(mStick1[i]) mStick1[i]->RmvNotify(&mNtfStick1[i]);
    if(mStick2[i]) mStick2[i]->RmvNotify(&mNtfStick2[i]);
    for(j=0; j<4; j++)
    {
      if(mDials[j][i]) mDials[j][i]->RmvNotify(&mNtfDials[j][i]);
    }
  }

  if(mIndex) delete mIndex;
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemoteInfo::stButton(bool pressed, void *this_p)
{
  CRemoteInfo *ri = (CRemoteInfo *)this_p;
	if (!ri) return;
  int val;

  if(ri->mRemoteDriver)
  {
    if(pressed)
    {
      ri->mIndex->StepVal(1,NFLG_CLIP);
    }

    val = (int)ri->mIndex->GetVal();
    switch(val)
    {
    case 0: ri->mRemoteDriver->SetLed(true, false, false); break;
    case 1: ri->mRemoteDriver->SetLed(false, true, false); break;
    case 2: ri->mRemoteDriver->SetLed(false, false, true); break;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemoteInfo::stDial(signed char dial[4], void *this_p)
{
  CRemoteInfo *ri = (CRemoteInfo *)this_p;
	if (!ri) return;

  if(ri->mRemoteDriver)
  {
    int i,idx = (int)ri->mIndex->GetVal();

    for(i=0; i<4; i++)
    {
      if(dial[i] && ri->mDials[i][idx])
      {
        ri->mDials[i][idx]->StepVal(dial[i],NFLG_OTHERS);
        dial[i] = 0;
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

CParam::td_notify stStickNtf;

void CRemoteInfo::stStick(unsigned char stick[2], void *this_p)
{
  CRemoteInfo *ri = (CRemoteInfo *)this_p;
	if (!ri) return;

  if(ri->mRemoteDriver)
  {
    int idx = (int)ri->mIndex->GetVal();
    stStickNtf.clear();

    if(ri->mStick1[idx])
    {
      stStickNtf.min = 255.;
      stStickNtf.max = 0.;
      ri->mStick1[idx]->SetVal((float)(stick[0]),NFLG_OTHERS,&stStickNtf);
    }
    if(ri->mStick2[idx])
    {
      stStickNtf.min = 255.;
      stStickNtf.max = 0.;
      ri->mStick2[idx]->SetVal((float)(stick[1]),NFLG_OTHERS,&stStickNtf);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemoteInfo::stCheckRc(int numrcs, void *this_p)
{
  CRemoteInfo *ri = (CRemoteInfo *)this_p;
	if (!ri) return;

  if(numrcs)
  {
    if(ri->mAllowCb)
    {
      ri->mAllowCb(ri->mAuthParent);
    }
  }
  else
  {
    if(ri->mDenyCb)
    {
      ri->mDenyCb(ri->mAuthParent);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CRemote::CRemote()
{
  mHandle = new CRemoteInfo();
}


///////////////////////////////////////////////////////////////////////////////
//

CRemote::~CRemote()
{
  // destroy view if allocated
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;
  if(ri)
  {
    this->SetAuthCb(0,0);
    delete ri;
    ri = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

bool CRemote::IsBad()
{
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;

  bool err=true;
  if(ri)
  {
    err = ri->mError;
  }

  return err;
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemote::SetParamStick( int idx, CParam *val[2] )
{
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;

  if(ri && idx>=0 && idx<=2)
  {
    ri->mRemoteDriver->SetFirst();
    if(ri->mStick1[idx])
    {
      ri->mStick1[idx]->RmvNotify(&(ri->mNtfStick1[idx]));
    }
    if(ri->mStick2[idx])
    {
      ri->mStick2[idx]->RmvNotify(&(ri->mNtfStick2[idx]));
    }
    ri->mStick1[idx] = val[0];
    ri->mStick2[idx] = val[1];
    if(ri->mStick1[idx])
    {
      ri->mNtfStick1[idx].inf[0] = ri;
      ri->mStick1[idx]->AddNotify(&(ri->mNtfStick1[idx]));
    }
    if(ri->mStick2[idx])
    {
      ri->mNtfStick2[idx].inf[0] = ri;
      ri->mStick2[idx]->AddNotify(&(ri->mNtfStick2[idx]));
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemote::SetParamDials( int idx, CParam *val[4] )
{
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;

  if(ri && idx>=0 && idx<=2)
  {
    for(int i=0; i<4; i++)
    {
      if(ri->mDials[i][idx])
      {
        ri->mDials[i][idx]->RmvNotify(&(ri->mNtfDials[i][idx]));
      }
      ri->mDials[i][idx] = val[i];
      if(ri->mDials[i][idx])
      {
        ri->mNtfDials[i][idx].inf[0] = ri;
        ri->mDials[i][idx]->AddNotify(&(ri->mNtfDials[i][idx]));
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemote::SetRemoteFocus( void )
{
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;

  if(ri)
  {
    if(ri->mRemoteDriver)
    {
      ri->mRemoteDriver->GrabFocus();
    }
    ri->stButton(false,ri);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CRemote::SetAuthCb( void (*authcb[2])(void *), void *parent )
{
  CRemoteInfo *ri = (CRemoteInfo *)mHandle;

  if(ri && ri->mRemoteDriver)
  {
    ri->mRemoteDriver->SetAuthCb(authcb,parent);
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CRemote.cpp,v $
// Revision 1.7  2004/10/05 18:21:40  joffe
// destructor improvements
//
// Revision 1.6  2004/09/28 02:29:40  joffe
// first blister-show implementation
//
// Revision 1.5  2004/09/15 22:41:26  joffe
// crash removed
//
// Revision 1.4  2004/09/07 16:16:16  joffe
// removed useless code
//
// Revision 1.3  2004/08/26 00:48:08  joffe
// remote-auth added and setparm interface changed
//
// Revision 1.1  2004/08/14 06:09:42  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
