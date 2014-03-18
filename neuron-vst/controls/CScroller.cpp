///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CScroller.cpp,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "CScroller.h"

#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

static const CColor kTransparent = {128,128,128,0};  // private transparency

#define LEDBAR_WIDTH    5   // width of the ledbar
#define LEDBAR_HEIGHT   29  // height of one ledbar


// create own table of initialization data

typedef struct
{
  int idbhm,idbled;
  int hmleft,hmtop;
  bool vert;

} info;

const info stInfo[kNumScTypes] =
{
  {IDB_SCROLLERHITMAP1,IDB_SCROLLERLED1,   4, 11, true },
  {IDB_SCROLLERHITMAP2,IDB_SCROLLERLED2,  23,  1, false},
};

typedef struct
{
  short top;
  short left;
  int type;
  int display;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4,p5) {p2,p3,p4,p5},
#include "CScroller.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CScrollerView : public CView
{
public:

  friend class CScroller;

  CScrollerView(int index);
	~CScrollerView();

  void SetFrame(CFrame *frame, CPoint ofs);

  static void stNotifyPstCb( float *val, CParam *inParam, void **inInfo );
  void dragval(CDrawContext *dstcon, CPoint &where);

  virtual void draw(CDrawContext *);
	virtual void mouse(CDrawContext *, CPoint &);
  virtual long notify(CView *sender, const char *message);

private:

  CParam *mParam;
  CParam::td_notify mParamNtf;
  CRect   mSize;

  CFrame  *mFrame;

  int     mType;
  CBitmap *mHitmap;
  int     mHmLeft;
  int     mHmTop;
  CBitmap *mLedbmp;
  int     mLedbarValue;
  bool    mVert;

  CDisplay *mDisplay;
  bool     mDisplayMouse;
};


///////////////////////////////////////////////////////////////////////////////
//

CScrollerView::CScrollerView(int index) : CView (size)
{
  // init some stuff
  if(index<0 || index>=kNumScrollers)
  {
    index = 0;
  }
  mFrame = 0;
  mParam = 0;

  mType = stData[index].type;

  // get bitmap for hitmap and adjust target location
  const info *scinf = &stInfo[mType];
  mHitmap = new CBitmap(scinf->idbhm);
  mSize(0, 0, mHitmap->getWidth(), mHitmap->getHeight());
  mSize.offset(stData[index].left - scinf->hmleft, stData[index].top - scinf->hmtop);
  mHmLeft = scinf->hmleft;
  mHmTop = scinf->hmtop;
  size = mSize;

  // get bitmap for ledbars
  mLedbmp = new CBitmap(scinf->idbled);
  mLedbarValue = 33;
  mVert = scinf->vert;

  // get the according display
  mDisplay = new CDisplay(stData[index].display);
  mDisplayMouse = false;
}


///////////////////////////////////////////////////////////////////////////////
//

CScrollerView::~CScrollerView()
{
  if(mFrame) mFrame->removeView(this);
  mLedbmp->forget(); mLedbmp = 0;
  mHitmap->forget(); mHitmap = 0;
  delete mDisplay;

  // if we have a param we need to remove our notify-fn
  if(mParam)
  {
    mParam->RmvNotify(&mParamNtf);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CScrollerView::SetFrame(CFrame *frame, CPoint ofs)
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
  mDisplay->SetFrame(frame,ofs,this);
}


///////////////////////////////////////////////////////////////////////////////
//

void CScrollerView::stNotifyPstCb( float *val, CParam *param, void **inf )
{
  CScrollerView *pview = (CScrollerView *)inf[0];
  bool bipolar = pview->mParam->IsBipolar();

  pview->mDisplay->SetInt((int)param->GetVal(),bipolar);
  pview->mLedbarValue = (int)val[1];
  pview->setDirty();
}


///////////////////////////////////////////////////////////////////////////////
//

void CScrollerView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y,w,h;
  int bar = 0;
  
	setDirty(false);
  if(mParam) bar += mParam->IsBipolar() ? 0: 1;

  w = mLedbmp->getWidth();
  h = mLedbmp->getHeight();

  switch(mType)
  {
  case kScTpVS:
    x = size.left + mHmLeft;
    y = size.top + mHmTop;
    cr = CRect(x,y, x+LEDBAR_WIDTH, y+LEDBAR_HEIGHT);
    cp = CPoint(bar*LEDBAR_WIDTH, (mLedbarValue/2)*LEDBAR_HEIGHT);
    mLedbmp->draw(dstcon, cr, cp);
    break;

  case kScTpHB:
    x = size.left + 1 + mHmLeft;
    y = size.top - 1 + mHmTop;
    cr = CRect(x,y, x+w, y+h);
    int v,b;

    if(bar)
    {
      v = 63-mLedbarValue;;
      for(int l=0; l<10; l++)
      {
        if(mFrame) 
			mFrame->getBackground()->draw(dstcon, cr, CPoint(x,y));
        b = v>7 ? v>16 ? 78-(v/12) : 7 : v<=0 ? 0 : v;
        b *= 36;
        mLedbmp->drawAlphaBlend(dstcon, cr, CPoint(0,0), b);
        cr.offset(w+1,0);
        v -= 6;
      }
    }
    else
    {
      if(mLedbarValue < 33)
      {
        v = 68-mLedbarValue;
        for(int l=0; l<10; l++)
        {
          if(mFrame) 
			  mFrame->getBackground()->draw(dstcon, cr, CPoint(x,y));
          b = l<4 ? 0 : v>7 ? v>16 ? 80-(v/6) : 7 : v<=0 ? 0 : v;
          b *= 36;
          mLedbmp->drawAlphaBlend(dstcon, cr, CPoint(0,0), b);
          cr.offset(w+1,0);
          v -= 6;
        }
      }
      else
      {
        v = mLedbarValue+3;
        cr.offset(9*(w+1),0);
        for(int l=0; l<10; l++)
        {
          if(mFrame) 
			  mFrame->getBackground()->draw(dstcon, cr, CPoint(x,y));
          b = l<4 ? 0 : v>7 ? v>16 ? 80-(v/6) : 7 : v<=0 ? 0 : v;
          b *= 36;
          mLedbmp->drawAlphaBlend(dstcon, cr, CPoint(0,0), b);
          cr.offset(-(w+1),0);
          v -= 6;
        }
      }
    }
    break;
  }

#if 0
  mHitmap->drawAlphaBlend(dstcon, size, cp(0,0));
#endif
}


///////////////////////////////////////////////////////////////////////////////
//

void CScrollerView::dragval(CDrawContext *dstcon, CPoint &where)
{
  CPoint ref = where;
  float old = mParam->GetVal();
  bool allow = false; // need to drag a bit before edit
  int d;

	while(1)
	{
		long button = dstcon->getMouseButtons();
		if (!(button & kLButton))
    {
			break;
    }

		dstcon->getMouseLocation(where);
    d = mVert ? ref.y-where.y : where.x-ref.x;
    if(allow==false)
    {
      if(d<-2 || d>2)
      {
        allow = true;
        ref = where;
      }
    }
    else
    {
      mParam->SetVal(old+d, NFLG_ALL);
    }

		if(mFrame) 
			mFrame->doIdleStuff();
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void CScrollerView::mouse(CDrawContext *dstcon, CPoint &where)
{
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton) || !mParam)
  {
		return;
  }

	// see whether to set the default value
	if(button == (kControl|kLButton))
	{
    mParam->SetVal(mParam->mDef, NFLG_ALL);
		return;
	}

  if(mDisplayMouse)
  {
    // this event is sent by the attached display
    mDisplayMouse = false;
    bool vert=mVert;
    mVert = true;
    dragval(dstcon,where);
    mVert = vert;
  }
  else
  {
    // this event is from our own area, so get the hitmap and see whats to do
    long dsplw = mHitmap->getWidth();
    long dsplh = mHitmap->getHeight();
    CPoint cp = CPoint(0,0);
    CRect  cr = CRect(0,0,dsplw,dsplh);
    COffscreenContext *hitmap = new COffscreenContext(mFrame,dsplw,dsplh);
    mHitmap->draw(hitmap, cr, cp);
    //mHitmap->drawAlphaBlend(dstcon, size, cp);
    where.offset(-size.left, -size.top);
    CColor cl = hitmap->getPoint(where);
    delete hitmap;

    if(cl==kGreenCColor)
    {
      mParam->StepVal(1, NFLG_ALL);
    }
    else if(cl==kRedCColor)
    {
      mParam->StepVal(-1, NFLG_ALL);
    }
    else if(cl==kWhiteCColor)
    {
      dragval(dstcon,where);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

long CScrollerView::notify(CView *sender, const char *message)
{
  switch((int)message)
  {
  case VNTF_MOUSE:  // next ::mouse() is an alien
    mDisplayMouse = true;
    break;

  default:
    int in;

    sscanf(message,"%i",&in);
    mParam->SetVal((float)in,NFLG_ALL);
  }

  return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CScroller::CScroller(int index)
{
  // allocate a view
  mHandle = new CScrollerView(index);
}


///////////////////////////////////////////////////////////////////////////////
//

CScroller::~CScroller()
{
  // destroy view if allocated
  CScrollerView *pview = (CScrollerView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CScroller::SetFrame(CFrame *frame, CPoint ofs)
{
  CScrollerView *pview = (CScrollerView *)mHandle;

  if(pview)
  {
    pview->SetFrame(frame,ofs);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CScroller::SetParam( CParam *inParam )
{
  CScrollerView *pview = (CScrollerView *)mHandle;

  if(pview)
  {
    // if we have already a param we need to remove our notify-fn
    if(pview->mParam)
    {
      pview->mParam->RmvNotify(&(pview->mParamNtf));
    }

    // set new parameter
    pview->mParam = inParam;

    if(pview->mParam)
    {
      pview->mParamNtf.min = 65.99f;
      pview->mParamNtf.max = 0.;
      pview->mParamNtf.inf[0] = pview;
      pview->mParamNtf.PstCbFn = pview->stNotifyPstCb;
      pview->mParam->AddNotify(&(pview->mParamNtf), false, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CScroller.cpp,v $
// Revision 1.3  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.2  2004/10/18 06:41:33  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
