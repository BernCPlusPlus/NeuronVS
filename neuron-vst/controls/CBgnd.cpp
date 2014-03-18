///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CBgnd.cpp,v $
// $Revision: 1.5 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "CBgnd.h"

#include "resource.h"


bool gCBgndBlockDirty = false;


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

// create own table of initialization data

typedef struct
{
  int resid;
  int top;
  int left;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4) {p2,p3,p4},
#include "CBgnd.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CBgndView : public CView
{
public:

  friend class CBgnd;

  CBgndView(int inEnumedId, CBitmap **oBgnd, CPoint &oOfs );
  ~CBgndView();

  virtual void draw(CDrawContext *);
	virtual void setDirty(const bool val);
	virtual void mouse(CDrawContext *, CPoint &);

private:
  CFrame  *mFrame;
  CRect   mSize;
  CBitmap *mBgndBmp;
  void    (*mMouseClick)(void *parent);
  void    *mMouseClickParent;
};


///////////////////////////////////////////////////////////////////////////////
//

CBgndView::CBgndView(int index, CBitmap **oBgnd, CPoint &oOfs ) : CView(size)
{
  // init some working stuff
  index = (index>=0 && index<kNumBgnds) ? index:0;
  mBgndBmp = new CBitmap(stData[index].resid);
  mSize(0, 0, mBgndBmp->getWidth(), mBgndBmp->getHeight());
  mSize.offset(stData[index].left, stData[index].top);
  size = mSize;
  *oBgnd = mBgndBmp;
  oOfs = CPoint(-stData[index].left, -stData[index].top);
  mFrame = 0;
  mMouseClick = 0;

}


///////////////////////////////////////////////////////////////////////////////
//

CBgndView::~CBgndView()
{
  if(mFrame) mFrame->removeView(this);
  mBgndBmp->forget(); mBgndBmp = 0;
}


///////////////////////////////////////////////////////////////////////////////
//

void CBgndView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  x = size.left;
  y = size.top;
  long dsplw = mBgndBmp->getWidth();
  long dsplh = mBgndBmp->getHeight();

  cr = CRect(x,y, x+dsplw, y+dsplh);
  cp = CPoint(0, 0);

  setDirty(false);
  mBgndBmp->draw(dstcon, cr, cp);
}


///////////////////////////////////////////////////////////////////////////////
//

void CBgndView::setDirty(const bool val)
{
  if(gCBgndBlockDirty==false) bDirty = val;
}


///////////////////////////////////////////////////////////////////////////////
//

static unsigned long stTicks;

void CBgndView::mouse(CDrawContext *dstcon, CPoint &where)
{
  unsigned long delta=250, ticks = getParent()->getTicks();
  bool dblclick = false;
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton))
  {
		return;
  }

#if WINDOWS
	delta = GetDoubleClickTime ();
#elif MAC
	delta = GetDblTime ();
#endif

  dblclick = (ticks-stTicks)<delta;
  stTicks = ticks;
  if(mMouseClick) mMouseClick(mMouseClickParent);

  while(1)
  {
    long button = dstcon->getMouseButtons();

    if(!(button & kLButton) || !mFrame)
    {
      break;
    }
    mFrame->doIdleStuff();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CBgnd::CBgnd(int index, CBitmap **oBgnd, CPoint &oOfs )
{
  // allocate a view
  mHandle = new CBgndView(index,oBgnd,oOfs);
}


///////////////////////////////////////////////////////////////////////////////
//

CBgnd::~CBgnd()
{
  // destroy view if allocated
  CBgndView *pview = (CBgndView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CBgnd::SetFrame(CFrame *frame)
{
  CBgndView *pview = (CBgndView *)mHandle;

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

void CBgnd::SetDirty(bool dirty)
{
  CBgndView *pview = (CBgndView *)mHandle;

  if(pview && pview->mFrame)
  {
    pview->setDirty(dirty);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CBgnd::SetMouseClickCb(void (*callback)(void *), void *parent)
{
  CBgndView *pview = (CBgndView *)mHandle;

  if(pview)
  {
    pview->mMouseClick = callback;
    pview->mMouseClickParent = parent;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CBgnd.cpp,v $
// Revision 1.5  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.4  2004/11/17 16:22:44  joffe
// statics moved out of function-bodies
//
// Revision 1.3  2004/08/25 03:48:55  joffe
// more checking/security
//
// Revision 1.2  2004/08/14 06:06:21  joffe
// backround-bitmap mouseclick-callback added
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
