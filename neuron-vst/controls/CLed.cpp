///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CLed.cpp,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "CLed.h"

#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

static const CColor kTransparent = {0,255,0,0};  // private transparency

#define LED_WIDTH       15  // width of the LEDs
#define LED_HEIGHT       7  // height of one LED

#define HM_LEFT          2  // left offset from bitmap-left to target-left
#define HM_TOP           2  // top offset from bitmap-top to target-top


// create own table of initialization data

typedef struct
{
  short top;
  short left;

} data;

const data stData[] =
{
#define CM(p1,p2,p3) {p2,p3},
#include "CLed.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CLedView : public CView
{
public:

  friend class CLed;

  CLedView(int index);
	~CLedView();

  virtual void draw(CDrawContext *);

private:

  CParam *mParam;
  CParam::td_notify mParamNtf;

  CFrame  *mFrame;

  CBitmap *mLeds;
  bool    mIsOn;
};


///////////////////////////////////////////////////////////////////////////////
//

CLedView::CLedView(int index) : CView (size)
{
  // init some stuff
  if(index<0 || index>=kNumLeds)
  {
    index = 0;
  }
  mParam = 0;
  mFrame = 0;

  // get bitmap and defaults for Leds
  mLeds = new CBitmap(IDB_LEDSTD);
  mLeds->setTransparentColor(kTransparent);
  mIsOn = false;
  size(0, 0, LED_WIDTH, LED_HEIGHT);
  size.offset(stData[index].left - HM_LEFT, stData[index].top - HM_TOP);
}
 

///////////////////////////////////////////////////////////////////////////////
//

CLedView::~CLedView()
{
  if(mFrame) mFrame->removeView(this);
  mLeds->forget(); mLeds = 0;

  // if we have a param we need to remove our notify-fn
  if(mParam)
  {
    mParam->RmvNotify(&mParamNtf);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CLedView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  x = size.left;
  y = size.top;
	setDirty(false);

  cr = CRect(x,y, x+LED_WIDTH, y+LED_HEIGHT);
  if(mIsOn)
  {
    cp = CPoint(0, 0);
    mLeds->drawTransparent(dstcon, cr, cp);
  }
  else
  {
    cp = CPoint(x, y);
    getParent()->getBackground()->draw(dstcon,size,cp);
  }
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CLed::CLed(int index)
{
  // allocate a view
  mHandle = new CLedView(index);
}


///////////////////////////////////////////////////////////////////////////////
//

CLed::~CLed()
{
  // destroy view if allocated
  CLedView *pview = (CLedView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CLed::SetFrame(CFrame *frame)
{
  CLedView *pview = (CLedView *)mHandle;

  if(pview /*&& pview->mFrame!=frame*/)
  {
    if(frame)
    {
      // add this view to the frame
      frame->addView(pview);
    }
    else
    {
      // remove this view from the current frame
      if(pview->mFrame)
      {
        pview->mFrame->removeView(pview);
      }
    }
    pview->mFrame = frame;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CLed::SetLed( bool inOnOff )
{
  CLedView *pview = (CLedView *)mHandle;

  if(pview)
  {
    pview->mIsOn = inOnOff;
    pview->setDirty();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CLed.cpp,v $
// Revision 1.3  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.2  2004/08/25 03:50:17  joffe
// more checking/security
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
