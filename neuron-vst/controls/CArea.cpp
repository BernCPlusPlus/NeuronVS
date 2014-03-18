///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CArea.cpp,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "CArea.h"

#include <stdio.h>

// create own table of initialization data


typedef struct
{
  int top;
  int left;
  int width;
  int height;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4,p5) {p2,p3,p4,p5},
#include "CArea.h"
};


CArea::CArea(int index) : CView(size)
{
  mMouseClick = 0;
  mFrame = 0;

  index = (index>=0 && index<kNumAreas) ? index:0;

  size
  (
    stData[index].left, stData[index].top,
    stData[index].left+stData[index].width,
    stData[index].top+stData[index].height
  );
}


CArea::~CArea()
{
}


void CArea::SetFrame(CFrame *frame, CPoint ofs)
{
  if(frame)
  {
    frame->addView(this);
  }
  else if(mFrame)
  {
    mFrame->removeView(this);
  }
  mFrame = frame;
}


void CArea::SetMouseClickCb(void (*callback)(void *), void *parent)
{
  mMouseClick = callback;
  mMouseClickParent = parent;
}


void CArea::mouse(CDrawContext *dstcon, CPoint &where)
{
//  unsigned long delta=250, ticks = getParent()->getTicks();
//  statics unsigned long stTicks;
//  bool dblclick = false;
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton))
  {
		return;
  }

/*
#if WINDOWS
	delta = GetDoubleClickTime ();
#elif MAC
	delta = GetDblTime ();
#endif
*/

//  dblclick = (ticks-stTicks)<delta;
//  stTicks = ticks;
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
// $Log: CArea.cpp,v $
// Revision 1.3  2004/11/17 16:22:44  joffe
// statics moved out of function-bodies
//
// Revision 1.2  2004/11/16 18:13:15  joffe
// bugfix: mframe initialized
//
// Revision 1.1  2004/11/06 05:53:15  joffe
// about-page added
//
///////////////////////////////////////////////////////////////////////////////
