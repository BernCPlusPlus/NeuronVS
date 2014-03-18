///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDial.cpp,v $
// $Revision: 1.4 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#define SHOW_POSx    // shows a black frame to adjust *.def and hmleft/hmtop

#include <stdio.h>

#include "CDial.h"

#include "resource.h"


static CColor kTransparent = {255,255,255,0};

typedef struct
{
  short top;
  short left;
  int display;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4) {p2,p3,p4},
#include "CDial.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CDialView : public CView
{
public:

  friend class CDial;

  CDialView(int index);
	~CDialView();

  void SetFrame(CFrame *frame, CPoint ofs);

  static void stNotifyPstCb( float *val, CParam *inParam, void **inInfo );
  void dragval(CDrawContext *dstcon, CPoint &where);
  virtual void draw(CDrawContext *);
  virtual void mouse(CDrawContext *, CPoint &);
  virtual long notify(CView *sender, const char *message);

private:

  CFrame  *mFrame;
  CParam  *mParam;
  CParam::td_notify mParamNtf;
  CRect   mSize;

  CParam  mRot;

  CBitmap *mMaskBmp;
  CBitmap *mDialBmp;

  CDisplay *mDisplay;
  bool     mDisplayMouse;
};


///////////////////////////////////////////////////////////////////////////////
//

CDialView::CDialView(int index) : CView (size)
{
  // init some stuff
  if(index<0 || index>=kNumDials)
  {
    index = 0;
  }
  mFrame = 0;
  mParam = 0;

  // get bitmap for mask
  mMaskBmp = new CBitmap(IDB_DIALMASK);
  mMaskBmp->setTransparentColor(kTransparent);
  int w = mMaskBmp->getWidth();
  int h = mMaskBmp->getHeight();
  mSize(0, 0, w, h);
  mSize.offset(stData[index].left-w/2 ,stData[index].top-h/2);
  size = mSize;

  // get bitmap for dials
  mDialBmp = new CBitmap(IDB_DIALS);
  mDialBmp->setTransparentColor(kTransparent);

  // get the according display
  mDisplay = new CDisplay(stData[index].display);
  mDisplayMouse = false;

  mRot.mMax = 89.;
  float r = ((float)rand() / (float)RAND_MAX) * mRot.mMax;
  mRot.SetVal(r);

}


///////////////////////////////////////////////////////////////////////////////
//

CDialView::~CDialView()
{
  if(mFrame) mFrame->removeView(this);
  mMaskBmp->forget(); mMaskBmp = 0;
  mDialBmp->forget(); mDialBmp = 0;
  delete mDisplay;

  // if we have a param we need to remove our notify-fn
  if(mParam)
  {
    mParam->RmvNotify(&mParamNtf);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDialView::SetFrame(CFrame *frame, CPoint ofs)
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

void CDialView::stNotifyPstCb( float *val, CParam *param, void **inf )
{
  CDialView *pview = (CDialView *)inf[0];
  if(pview)
  {
    pview->setDirty();
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDialView::dragval(CDrawContext *dstcon, CPoint &where)
{
  CPoint ref = where;
  int d,snap = 2;

	while(1)
	{
		long button = dstcon->getMouseButtons();
		if (!(button & kLButton))
    {
			break;
    }

		dstcon->getMouseLocation(where);
    d = 1 ? ref.y-where.y : where.x-ref.x;
    if(snap)
    {
      if(d<-snap || d>snap)
      {
        if(!mDisplayMouse) ref = where;
        snap = 0;
      }
    }
    else
    {
      if(mDisplayMouse)
      {
        d = d>0 ? 1 : d<0 ? -1 : 0;
        snap=5;
      }
      if(mParam) mParam->StepVal(d, NFLG_ALL);

      if(!mDisplayMouse) mRot.StepVal(d, NFLG_ALL|NFLG_CLIP);
      setDirty();
      ref = where;
    }

		mFrame->doIdleStuff();
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void CDialView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  if(mParam) mDisplay->SetInt((int)mParam->GetVal(),mParam->IsBipolar());
  setDirty(false);

  x = size.left;
  y = size.top;
  long dsplw = mMaskBmp->getWidth();
  long dsplh = mMaskBmp->getHeight();

  cr = CRect(x,y, x+dsplw, y+dsplh);
  cp = CPoint(0,(int)mRot.GetVal()*dsplh);

  mDialBmp->drawTransparent(dstcon, cr, cp);


#ifdef SHOW_POS
  mMaskBmp->drawTransparent(dstcon, cr, cp);
#endif
}


///////////////////////////////////////////////////////////////////////////////
//

void CDialView::mouse(CDrawContext *dstcon, CPoint &where)
{
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton))
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
    dragval(dstcon,where);
  }
  else
  {
    // this event is from our own area, so get the hitmap and see whats to do
    long dsplw = mMaskBmp->getWidth();
    long dsplh = mMaskBmp->getHeight();
    CPoint cp = CPoint(0,0);
    CRect  cr = CRect(0,0,dsplw,dsplh);
    COffscreenContext *hitmap = new COffscreenContext(mFrame,dsplw,dsplh);
    mMaskBmp->draw(hitmap, cr, cp);
    //mMaskBmp->drawAlphaBlend(dstcon, size, cp);
    where.offset(-size.left, -size.top);
    CColor cl = hitmap->getPoint(where);
    delete hitmap;

    if(cl==kWhiteCColor)
    {
      dragval(dstcon,where);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

long CDialView::notify(CView *sender, const char *message)
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

CDial::CDial(int index)
{
  // allocate a view
  mHandle = new CDialView(index);
}


///////////////////////////////////////////////////////////////////////////////
//

CDial::~CDial()
{
  // destroy view if allocated
  CDialView *pview = (CDialView *)mHandle;

  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDial::SetFrame(CFrame *frame, CPoint ofs)
{
  CDialView *pview = (CDialView *)mHandle;

  if(pview)
  {
    pview->SetFrame(frame,ofs);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDial::SetParam( CParam *inParam )
{
  CDialView *pview = (CDialView *)mHandle;

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
      pview->mParamNtf.inf[0] = pview;
      pview->mParamNtf.PstCbFn = pview->stNotifyPstCb;
      pview->mParam->AddNotify(&(pview->mParamNtf), true, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDial.cpp,v $
// Revision 1.4  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.3  2004/10/18 06:41:33  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.2  2004/08/25 03:49:19  joffe
// more checking/security
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
