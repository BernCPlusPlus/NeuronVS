///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CStick.cpp,v $
// $Revision: 1.11 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

#include "CStick.h"
#include "CDisplay.h"

#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

static const CColor kTransparent = {128,128,128,0};  // private transparency

static unsigned char stClip[3*256];
static bool stClipInit = false;

#define STICK_WIDTH    128  // width of the Sticks
#define STICK_HEIGHT   128  // height of one Stick


// create own table of initialization data

typedef struct
{
  short top;
  short left;
  short display[8];

} data;

const data stData[] =
{
#define CM(p1,p2,p3,v1,n1,v2,n2,v3,n3,v4,n4) {p2-STICK_HEIGHT/2,p3-STICK_WIDTH/2, v1,n1,v2,n2,v3,n3,v4,n4},
#include "CStick.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CStickView : public CView
{
public:

  friend class CStick;

  CStickView(int index, CBitmap *bgnd);
	~CStickView();

  static void stNtf1Cb( float *val, CParam *param, void **inf );
  static void stNtf2Cb( float *val, CParam *param, void **inf );

  void SetFrame(CFrame *frame, CPoint ofs);

  virtual void draw(CDrawContext *);
  virtual void mouse(CDrawContext *, CPoint &);
  virtual long notify(CView *sender, const char *message);

private:

  CFrame  *mFrame;
  CRect   mSize;

  void    (*mResetAll)(void *parent);
  void    *mResetAllParent;

  CBitmap *mResyring;
  CBitmap *mResybowl;
  CBitmap *mBlister;
  CBitmap *mSticks;
  int     mLevel;
  int     mType;
  CDisplay *mDisplay[8];
  CParam   *mVal1;
  CParam   *mVal2;
  CParam   *mDisplayVal;
  CParam::td_notify mNtf1;
  CParam::td_notify mNtf2;
};


///////////////////////////////////////////////////////////////////////////////
//

CStickView::CStickView(int index, CBitmap *bgnd) : CView (size)
{
  // init some stuff
  if(index<0 || index>=kNumSticks)
  {
    index = 0;
  }
  mFrame = 0;
  mResetAll = 0;

  // get bitmap and defaults for Leds
  mResyring = new CBitmap(IDB_RESYRING);
  mResybowl = new CBitmap(IDB_RESYBOWL);
  mBlister = new CBitmap(IDB_BLISTER);
  if(mBlister) mBlister->setTransparentColor(kTransparent);
  mLevel = 0;
  mType = 0;

  index = (index>=0 && index<kNumSticks) ? index:0;
  mSize(0, 0, STICK_WIDTH, STICK_HEIGHT);
  mSize.offset(stData[index].left, stData[index].top);
  size = mSize;

  CFrame *tempframe = new CFrame(size,"temp",this);
  mSticks = new CBitmap(*tempframe, STICK_WIDTH*3, STICK_HEIGHT*2);

  if(bgnd)
  {
    int x,y,zr,zg,zb;
    CColor scl,dcl,mcl;
    CRect cr;
    CDrawContext      *srccon = new CDrawContext(tempframe,0);
    COffscreenContext *dstcon = new COffscreenContext(srccon,mSticks,true);
    COffscreenContext *mskcon = new COffscreenContext(srccon,mResyring,true);

    // level 1
    cr = CRect(0,0,STICK_WIDTH,STICK_HEIGHT);
    //obsolete: bgnd->draw(dstcon,cr,CPoint(size.left,size.top));
    mResybowl->draw(dstcon,cr,CPoint(0,0));
    cr = CRect(0,STICK_HEIGHT,STICK_WIDTH,STICK_HEIGHT*2);
    mResybowl->draw(dstcon,cr,CPoint(STICK_WIDTH,0));

    // level 2+3
    // get dc-offset (point 0,0)
    scl = mskcon->getPoint(CPoint(0,0));
    zr = scl.red;
    zg = scl.green;
    zb = scl.blue;

    for(x=0; x<STICK_WIDTH; x++)
    {
      for(y=0; y<STICK_HEIGHT; y++)
      {
        int p;
        scl = dstcon->getPoint(CPoint(x,y));
 
        mcl = mskcon->getPoint(CPoint(x,y));
        p = (mcl.red + scl.red)-zr;
        dcl.red = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.green + scl.green)-zg;
        dcl.green = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.blue + scl.blue)-zb;
        dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
        dstcon->drawPoint(CPoint(x+STICK_WIDTH,y), dcl);

        mcl = mskcon->getPoint(CPoint(x+STICK_WIDTH,y));
        p = (mcl.red + scl.red)-zr;
        dcl.red = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.green + scl.green)-zg;
        dcl.green = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.blue + scl.blue)-zb;
        dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
        dstcon->drawPoint(CPoint(x+STICK_WIDTH*2,y), dcl);

        scl = dstcon->getPoint(CPoint(x,y+STICK_HEIGHT));

        mcl = mskcon->getPoint(CPoint(x,y));
        p = (mcl.red + scl.red)-zr;
        dcl.red = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.green + scl.green)-zg;
        dcl.green = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.blue + scl.blue)-zb;
        dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
        dstcon->drawPoint(CPoint(x+STICK_WIDTH,y+STICK_HEIGHT), dcl);

        mcl = mskcon->getPoint(CPoint(x+STICK_WIDTH,y));
        p = (mcl.red + scl.red)-zr;
        dcl.red = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.green + scl.green)-zg;
        dcl.green = p<0 ? 0 : p>255 ? 255 : p;
        p = (mcl.blue + scl.blue)-zb;
        dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
        dstcon->drawPoint(CPoint(x+STICK_WIDTH*2,y+STICK_HEIGHT), dcl);

      }
    }

    delete srccon;
    delete dstcon;
    delete mskcon;
  }

  for(int d=0; d<8; d++)
  {
    mDisplay[d] = new CDisplay(stData[index].display[d]);
  }
  mDisplayVal = 0;

  mVal1 = 0;
  mVal2 = 0;
}


///////////////////////////////////////////////////////////////////////////////
//

CStickView::~CStickView()
{
  // if we have  params we need to remove our notify-fn
  if(mVal1) mVal1->RmvNotify(&mNtf1);
  if(mVal2) mVal2->RmvNotify(&mNtf2);

  if(mFrame) SetFrame(0,0);
  if(mResyring) mResyring->forget();
  if(mResybowl) mResybowl->forget();
  if(mBlister) mBlister->forget();
  if(mSticks) mSticks->forget();
  for(int d=0; d<8; d++)
  {
    delete mDisplay[d];
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStickView::stNtf1Cb( float *val, CParam *param, void **inf )
{
  CStickView *pview = (CStickView *)inf[0];
  bool bipolar = param->IsBipolar();
  int out = (int)val[1];

  pview->mDisplay[0]->SetInt(out,bipolar);
  pview->mDisplay[1]->SetText(param->mDscr1);
  if(*(param->mDscr2))
  {
    out = bipolar ? -1-out : 127-out;
    pview->mDisplay[4]->SetInt(out,bipolar);
    pview->mDisplay[5]->SetText(param->mDscr2);
  }
  else
  {
    pview->mDisplay[4]->SetInt(out,bipolar);
    pview->mDisplay[5]->SetText(param->mDscr1);
  }

  pview->setDirty();
}


///////////////////////////////////////////////////////////////////////////////
//

void CStickView::stNtf2Cb( float *val, CParam *param, void **inf )
{
  CStickView *pview = (CStickView *)inf[0];
  bool bipolar = param->IsBipolar();
  int out = (int)val[1];

  pview->mDisplay[2]->SetInt(out,bipolar);
  pview->mDisplay[3]->SetText(param->mDscr1);
  if(*(param->mDscr2))
  {
    out = bipolar ? -1-out : 127-out;
    pview->mDisplay[6]->SetInt(out,bipolar);
    pview->mDisplay[7]->SetText(param->mDscr2);
  }
  else
  {
    pview->mDisplay[6]->SetInt(out,bipolar);
    pview->mDisplay[7]->SetText(param->mDscr1);
  }

  pview->setDirty();
}


///////////////////////////////////////////////////////////////////////////////
//

void CStickView::SetFrame(CFrame *frame, CPoint ofs)
{
  if(frame)
  {
    size = mSize;
    size.offset(-ofs.x, -ofs.y);
    // add this view to the frame
    frame->addView(this);
  }
  else
  {
    // remove this view from the current frame
    if(mFrame)
    {
      mFrame->removeView(this);
    }
  }
  mFrame = frame;
  for(int d=0; d<8; d++)
  {
    mDisplay[d]->SetFrame(frame,ofs,this);
  }
}

  
///////////////////////////////////////////////////////////////////////////////
//

#define SIN45 0.70710678119f // same as COS45 or sqr(2)
#define PI    3.14159265359f

float msin(float phi)
{
/*
r = ((x-n)/n)**2, k=0.225, n=PI/2
sin(0..pi) = (1-r)(1-kr)
*/

  float r,sin;
  bool pos=false;

  if(phi>=0)
    while(phi>PI)  phi -= 2.*PI;
  else
    while(phi<-PI) phi += 2.*PI;

  if(phi>=0)
    pos = true;
  else
    phi = -phi;

  r = (phi-PI*0.5f)*1/(PI*0.5f);
  r *= r;
  sin = (1.f-r)*(1.f-0.225f*r);

  return pos ? sin : -sin;
}

float masin(float in)
{
  return in*in*in+(PI/2-1.f)*in;
}


///////////////////////////////////////////////////////////////////////////////
//

void CStickView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  x = size.left;
  y = size.top;

  cr = CRect(x,y, x+STICK_WIDTH, y+STICK_HEIGHT);
  cp = CPoint(mLevel*STICK_WIDTH, mType*STICK_HEIGHT);
  setDirty(false);
  mSticks->draw(dstcon, cr, cp);

  if(mVal1 && mVal2)
  {
    CParam::td_notify vntf;
    int ix,iy,tx,ty;
    float ox,oy,rad,phi,tmp;
    CColor scl,dcl;
    CFrame *parentframe = getParent();
    COffscreenContext *blstcon = new COffscreenContext(parentframe,15,15);
    COffscreenContext *srccon  = new COffscreenContext(parentframe,15,15);

    vntf.clear();
    vntf.min = 1.;
    vntf.max = -1.;

    ox = mVal1->GetVal(&vntf);
    if(mVal1->IsBipolar()) ox = -ox;

    oy = mVal2->GetVal(&vntf);
    if(mVal2->IsBipolar()) oy = -oy;

    tmp=oy;
    rad = (float)sqrt(ox*ox + oy*oy);
    if(!rad)
    {
      phi = 0;
    }
    else
    {
      phi = (float)(oy<0 ? masin(ox/rad) : PI + masin(-ox/rad));
      if(rad>1.) rad=1.;
    }

    int rx = (int)((PI*.5+phi)*63.99/(2.*PI))*15;
    if(rx<0) rx += 64*15;

    CRect tcr = CRect(-rx,-(int)(rad*15.99)*15,15,15);
    mBlister->draw(blstcon, tcr, CPoint(0,0));

    tx = STICK_HEIGHT/2-7;
    ty = STICK_HEIGHT/2-7;

    tx += (int)(msin(phi-PI*0.25f+PI*0.5f)*rad*48.f+.5f);
    ty += (int)(msin(phi-PI*0.25f)*rad*48.f+.5f);

    tcr = CRect(0,0, 15,15);
    CPoint tcp = CPoint(tx + mLevel*STICK_WIDTH, ty + mType*STICK_HEIGHT);
    mSticks->draw(srccon, tcr, tcp);

    x += tx;
    y += ty;

    for(iy=0; iy<15; iy++)
    {
      for(ix=0; ix<15; ix++)
      {
        scl = blstcon->getPoint(CPoint(ix,iy));
      //dstcon->drawPoint(CPoint(ix,iy), scl);
        if( scl.red==128 && scl.green==128 && scl.blue==128 ) continue;
        dcl = srccon->getPoint(CPoint(ix,iy));
      //dstcon->drawPoint(CPoint(ix+20,iy), dcl);
        dcl.red   = stClip[scl.red + scl.red/2 + dcl.red];
        dcl.green = stClip[scl.green + scl.green/2 + dcl.green];
        dcl.blue  = stClip[scl.blue + scl.blue/2 + dcl.blue];
        dstcon->drawPoint(CPoint(ix+x,iy+y), dcl);
      }
    }

    delete srccon;
    delete blstcon;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStickView::mouse(CDrawContext *dstcon, CPoint &where)
{
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton) )
  {
		return;
  }

	if(button == (kControl|kLButton))
	{
    if(mDisplayVal)
    {
      // this event is sent by the attached display
	    // see whether to set the default value
      mDisplayVal->SetVal(mDisplayVal->mDef, NFLG_ALL);
      mDisplayVal = 0;
	  }
    else
    {
      if(mResetAll) mResetAll(mResetAllParent);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

long CStickView::notify(CView *sender, const char *message)
{

  for(int d=0; d<8; d++)
  {
    if((long)sender == (long)(mDisplay[d]))
    {
      switch(d)
      {
      case 0:
      case 1:
      case 4:
      case 5:
        mDisplayVal = mVal1;
        break;

      case 2:
      case 3:
      case 6:
      case 7:
        mDisplayVal = mVal2;
        break;

      default:
        mDisplayVal = 0;
        break;
      }
    }
  }
  return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CStick::CStick(int index, CBitmap *bgnd)
{
  // allocate a view
  mHandle = new CStickView(index,bgnd);

  if(stClipInit==false)
  {
    for(int i=0; i<(int)sizeof(stClip); i++)
    {
      stClip[i] = (i<192) ? 0 : (i>(192+255)) ? 255 : (i-192);
    }
    stClipInit = true;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

CStick::~CStick()
{
  // destroy view if allocated
  CStickView *pview = (CStickView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStick::SetFrame(CFrame *frame, CPoint ofs)
{
  CStickView *pview = (CStickView *)mHandle;

  if(pview)
  {
    pview->SetFrame(frame,ofs);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStick::SetView( int level, int type )
{
  CStickView *pview = (CStickView *)mHandle;

  if(pview)
  {
    if(level>=0 && level<=2) pview->mLevel = level;
    if(type>=0 && type<=1) pview->mType = type;
    pview->setDirty();  // update ring
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStick::SetParam( CParam *val1, CParam *val2 )
{
  CStickView *pview = (CStickView *)mHandle;

  if(pview)
  {
    // remove our notify-fn
    if(pview->mVal1) pview->mVal1->RmvNotify(&(pview->mNtf1));
    if(pview->mVal2) pview->mVal2->RmvNotify(&(pview->mNtf2));

    // set new parameters
    pview->mVal1 = val1;
    pview->mVal2 = val2;

    // add our notifyer to the params
    if(pview->mVal1)
    {
      pview->mNtf1.clear();
      pview->mNtf1.inf[0] = pview;
      pview->mNtf1.PstCbFn = pview->stNtf1Cb;
      pview->mVal1->AddNotify(&(pview->mNtf1), true);
    }
    if(pview->mVal2)
    {
      pview->mNtf2.clear();
      pview->mNtf2.inf[0] = pview;
      pview->mNtf2.PstCbFn = pview->stNtf2Cb;
      pview->mVal2->AddNotify(&(pview->mNtf2), true);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CStick::SetResetAllCb(void (*callback)(void *), void *parent)
{
  CStickView *pview = (CStickView *)mHandle;

  if(pview)
  {
    pview->mResetAll = callback;
    pview->mResetAllParent = parent;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CStick.cpp,v $
// Revision 1.11  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.10  2004/11/19 11:03:37  joffe
// stickdraw speedup
//
// Revision 1.9  2004/11/11 03:08:32  joffe
// reset-all callback added
//
// Revision 1.8  2004/09/29 09:55:30  joffe
// polarity-bug fixed
//
// Revision 1.7  2004/09/29 08:19:39  joffe
// scape/sphere bitmap added / page 2 type-button fixed
//
// Revision 1.6  2004/09/29 06:34:18  joffe
// blister-show mac-adaptions
//
// Revision 1.5  2004/09/28 02:29:40  joffe
// first blister-show implementation
//
// Revision 1.4  2004/08/26 00:49:13  joffe
// callback displayparameters fixed
//
// Revision 1.3  2004/08/25 03:54:37  joffe
// more checking/security
//
// Revision 1.2  2004/08/14 06:09:20  joffe
// reduced parameter usage
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
