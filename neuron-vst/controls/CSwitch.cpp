///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CSwitch.cpp,v $
// $Revision: 1.8 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#define SHOW_POSx    // shows a black frame to adjust *.def and hmleft/hmtop

#include <stdio.h>
#include <string.h>

#include "CSwitch.h"
#include "CLed.h"

#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

typedef struct
{
  int idb;
  int width,height;
  int hmleft,hmtop;
  char *cols;

} info;

const info stInfo[kNumSwTypes] =
{
  {IDB_SWSMALL,   17,12,   1, 1,  "01"},  // small button for pages
  {IDB_SWBIG,     22,21,   2, 2,  "01"},  // bigger version
  {IDB_SWSTD,     36,23,   3, 3,  "0"},   // standard button
  {IDB_SWSTD,     36,23,   3, 3,  "023"}, // level button 
  {IDB_SWSTD,     36,23,   3, 3,  "01"},  // record button 
  {IDB_SWARROW,   33,22,  16,14,  "01"},  // arrow-type for eq-sel
  {IDB_SWMODULE,  19,12,   1, 2,  "01"},  // module on/offs
};

typedef struct
{
  short top;
  short left;
  int type;
  int snap;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4,p5) {p2,p3,p4,p5},
#include "CSwitch.h"
};


// led-groups

const short stG10[] = {3, kLedR1L1,kLedR1L2,kLedR1L3, 0};
const short stG11[] = {2, kLedR1TypeSphere,kLedR1TypeScape, 0};
const short stG12[] = {3, -1,kLedR1AnimOneShot,kLedR1AnimRepeat, 0};
const short stG13[] = {3, -1,kLedR1ContourShaper,kLedR1ContourStick, 0};
const short stG14[] = {2, kLedR1SelectCtx1,kLedR1SelectCtx2, 2, kLedR1SelectCtx3,kLedR1SelectCtx4, 0};

const short stG20[] = {3, kLedR2L1,kLedR2L2,kLedR2L3, 0};
const short stG21[] = {2, kLedR2TypeSphere,kLedR2TypeScape, 0};
const short stG22[] = {3, -1,kLedR2AnimOneShot,kLedR2AnimRepeat, 0};
const short stG23[] = {3, -1,kLedR2ContourShaper,kLedR2ContourStick, 0};
const short stG24[] = {2, kLedR2SelectCtx1,kLedR2SelectCtx2, 2, kLedR2SelectCtx3,kLedR2SelectCtx4, 0};

const short stG40[] = {3, kLedSilverL1,kLedSilverL2,kLedSilverL3, 0};
const short stG41[] = {3, -1,kLedSilverAnimOneShot,kLedSilverAnimRepeat, 0};
const short stG42[] = {3, -1,kLedSilverContourShaper,kLedSilverContourStick, 0};

const short stG30[] = {2, kLedShaper12ModeNormal,kLedShaper12ModeRepeat, 0};
const short stG50[] = {2, kLedShaper3ModeNormal,kLedShaper3ModeRepeat, 0};
const short stG60[] = {2, kLedSlicerTypeVertical,kLedSlicerType3D, 0};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CSwitchView : public CView
{
public:

  friend class CSwitch;

  CSwitchView(int index, CBitmap *bgnd);
	~CSwitchView();

  void SetFrame(CFrame *frame, CPoint ofs);

  static void stNotifyPstCb( float *val, CParam *inParam, void **inInfo );

  virtual void draw(CDrawContext *);
	virtual void mouse(CDrawContext *, CPoint &);

private:

  CParam *mParam;
  CParam::td_notify mParamNtf;

  CFrame  *mFrame;
  CRect   mSize;

  CBitmap *mBmpres;       // the bitmap for the switch (first tile is hitmap)
  CBitmap *mSwitches;     // the finally rendered switches
  int     mNumSwitches;   // number of switch-bmps
  int     mWidth,mHeight; // dimension of one button
  bool    mIsPressed;     // guess

  char    *mCols;
  int     mColslen;
  int     mCol;
  int     mMode;
  float   mMval;
//  bool    mWithSnap;

  const short *mLedList;
  CLed    **mLeds;
  int     mNumLeds;
};


///////////////////////////////////////////////////////////////////////////////
//

CSwitchView::CSwitchView(int index, CBitmap *bgnd) : CView (size)
{
  // init some stuff
  if(index<0 || index>=kNumSwitches)
  {
    index = 0;
  }
  mParam = 0;
  mFrame = 0;
  mMode = SWMD_INCREMENT;
  mMval = 1.;
  
  // get bitmap for hitmap and adjust target location
  mBmpres = new CBitmap(stInfo[stData[index].type].idb);
  mWidth = stInfo[stData[index].type].width;
  mHeight = stInfo[stData[index].type].height;
  mNumSwitches = mBmpres->getWidth() / mWidth - 1;
  int hmleft = stInfo[stData[index].type].hmleft;
  int hmtop = stInfo[stData[index].type].hmtop;
  mSize(0, 0, mWidth, mHeight);
  mSize.offset(stData[index].left - hmleft, stData[index].top - hmtop);
  size = mSize;

  mIsPressed = false;
  mCols = stInfo[stData[index].type].cols;
  mColslen = strlen(mCols);
  mCol = mCols[0] - '0';

  // setup the bitmap and paint switches
  CFrame *tempframe = new CFrame(size,"temp",this);
  mSwitches = new CBitmap(*tempframe, mWidth*mNumSwitches, mHeight*2);

  if(bgnd)
  {
    int i,x,y,zr,zg,zb;
    CColor scl,dcl,mcl;
    CRect cr;
    CDrawContext      *srccon = new CDrawContext(tempframe,0);
    COffscreenContext *dstcon = new COffscreenContext(srccon,mSwitches,true);
    COffscreenContext *mskcon = new COffscreenContext(srccon,mBmpres,true);

    for(i=0; i<mNumSwitches; i++)
    {
      // for unpressed
      cr = CRect(mWidth*i,0,mWidth*i+mWidth,mHeight);
      bgnd->draw(dstcon,cr,CPoint(size.left,size.top));

      // for pressed
      cr = CRect(mWidth*i,mHeight,mWidth*i+mWidth,mHeight*2);
      bgnd->draw(dstcon,cr,CPoint(size.left,size.top));
      // get dc-offset (point 0,0)
      scl = mskcon->getPoint(CPoint(mWidth,0));
      zr = scl.red;
      zg = scl.green;
      zb = scl.blue;
      for(x=0; x<mWidth; x++)
      {
        for(y=0; y<mHeight; y++)
        {
          int p;
          scl = dstcon->getPoint(CPoint(x+mWidth*i,y+mHeight));
          mcl = mskcon->getPoint(CPoint(x+mWidth,y));
          p = (mcl.red + scl.red)-zr;
          dcl.red = p<0 ? 0 : p>255 ? 255 : p;
          p = (mcl.green + scl.green)-zg;
          dcl.green = p<0 ? 0 : p>255 ? 255 : p;
          p = (mcl.blue + scl.blue)-zb;
          dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
          dstcon->drawPoint(CPoint(x+mWidth*i,y+mHeight), dcl);
        }
      }

      // colorized, get dc-offset (point 0,0)
      scl = mskcon->getPoint(CPoint(mWidth*(i+1),0));
      zr = scl.red;
      zg = scl.green;
      zb = scl.blue;
      for(int n=0; i && n<2; n++)
      {
        for(x=0; x<mWidth; x++)
        {
          for(y=0; y<mHeight; y++)
          {
            int p;
            scl = dstcon->getPoint(CPoint(x+mWidth*i,y+mHeight*n));
            mcl = mskcon->getPoint(CPoint(x+mWidth*(i+1),y));
            p = (mcl.red + scl.red)-zr;
            dcl.red = p<0 ? 0 : p>255 ? 255 : p;
            p = (mcl.green + scl.green)-zg;
            dcl.green = p<0 ? 0 : p>255 ? 255 : p;
            p = (mcl.blue + scl.blue)-zb;
            dcl.blue = p<0 ? 0 : p>255 ? 255 : p;
            dstcon->drawPoint(CPoint(x+mWidth*i,y+mHeight*n), dcl);
          }
        }
      }
    }
    delete srccon;
    delete dstcon;
    delete mskcon;
  }

//  this 'crashes' vst/pc
//  delete tempframe;
//
  // set switch-specific led stuff
  switch(index)
  {
  case kSwitchR1ParamLevel:     mLedList = stG10; break;
  case kSwitchR1Type:           mLedList = stG11; break;
  case kSwitchR1CtxStickPb:     mLedList = stG12; break;
  case kSwitchR1CtxContour:     mLedList = stG13; break;
  case kSwitchR1CtxSelectXY:    mLedList = stG14; break;
  case kSwitchR2ParamLevel:     mLedList = stG20; break;
  case kSwitchR2Type:           mLedList = stG21; break;
  case kSwitchR2CtxStickPb:     mLedList = stG22; break;
  case kSwitchR2CtxContour:     mLedList = stG23; break;
  case kSwitchR2CtxSelectXY:    mLedList = stG24; break;
  case kSwitchShaper12CtxMode:  mLedList = stG30; break;

  case kSwitchSilverParamLevel: mLedList = stG40; break;
  case kSwitchSilverCtxStickPb: mLedList = stG41; break;
  case kSwitchSilverCtxContour: mLedList = stG42; break;
  case kSwitchShaper3Mode:      mLedList = stG50; break;
  case kSwitchSlicerType:       mLedList = stG60; break;

  default:                    mLedList = 0;
  }

  mNumLeds = 0;
  mLeds = 0;
  if(mLedList)
  {
    // setup all other led-stuff
    int pos, num, ledid;

    // count the number of leds we must use with this switch
    pos = 0;
    while( (num = mLedList[pos]) > 0 )
    {
      // num is the number of led-ids, set next pos and loop
      for(pos++; num>0; num--)
      {
        ledid = mLedList[pos++];
        if( ledid >= 0)
        {
          mNumLeds++;
        }
      }
    }

    // allocate buffer of needed leds
    if(mNumLeds)
    {
      mLeds = new CLed *[mNumLeds];
    }
    // and set up the leds
    if(mLeds)
    {
      int idx = 0;

      pos = 0;
      while( (num = mLedList[pos]) > 0 )
      {
        // num is the number of led-ids, set next pos and loop
        for(pos++; num>0; num--)
        {
          ledid = mLedList[pos++];
          if( ledid >= 0)
          {
            mLeds[idx] = new CLed(ledid);
            idx++;
          }
        }
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

CSwitchView::~CSwitchView()
{
  if(mFrame) SetFrame(0,0);
  if(mBmpres) mBmpres->forget();
  if(mSwitches) mSwitches->forget();

  // if we have a param we need to remove our notify-fn
  if(mParam)
  {
    mParam->RmvNotify(&mParamNtf);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitchView::SetFrame(CFrame *frame, CPoint ofs)
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
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitchView::stNotifyPstCb( float *pval, CParam *param, void **ppinf )
{
  CSwitchView *pview = (CSwitchView *)ppinf[0];
  float inval = pval[1];
  int col;

  if(pview)
  {
    switch(pview->mMode)
    {
    default:
    case SWMD_OFFLIKE:
      col = 0;
      break;
    case SWMD_INCREMENT:
      col = ((int)inval < pview->mNumSwitches) ? (int)inval : pview->mNumSwitches-1;
      break;
    case SWMD_CONSTANT:
      col = (inval == pview->mMval) ? 1 : 0;
      break;
    }
    if(col>=pview->mColslen) col = pview->mColslen-1;
    pview->mCol = pview->mCols[col] - '0';
    pview->setDirty();
  }

  if(pview)
  {
    int numleds = pview->mNumLeds;
    int target = (int)inval;
    int scan,ledid;
    int num;
    int pos = 0, ledidx=0;;

    while( numleds && (num = pview->mLedList[pos]) > 0 )
    {
      // num is the number of led-ids, set next pos and loop
      scan = 0;
      for(pos++; num>0 && ledidx<numleds; num--)
      {
        ledid = pview->mLedList[pos++];
        if(ledid >= 0)
        {
          pview->mLeds[ledidx++]->SetLed(scan==target);
        }
        scan++;
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitchView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  x = size.left;
  y = size.top;

	setDirty(false);

  cr = CRect(x,y, x+mWidth, y+mHeight);
  if(mIsPressed)
  {
    cp = CPoint(mWidth*mCol, mHeight);
    mSwitches->draw(dstcon, cr, cp);
  }
  else
  {
    cp = CPoint(mWidth*mCol, 0);
    mSwitches->draw(dstcon, cr, cp);
  }
#ifdef SHOW_POS
  cp = CPoint(0, 0);
  mBmpres->drawTransparent(dstcon, cr, cp);
#endif
}


///////////////////////////////////////////////////////////////////////////////
//

static unsigned long stTicks;

void CSwitchView::mouse(CDrawContext *dstcon, CPoint &where)
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

  // this event is from our own area, so get the hitmap and see whats to do
  long dsplw = mWidth;
  long dsplh = mHeight;
  CPoint cp = CPoint(0,0);
  CRect  cr = CRect(0,0,dsplw,dsplh);
  COffscreenContext *hitmap = new COffscreenContext(mFrame,dsplw,dsplh);
  mBmpres->draw(hitmap, cr, cp);
  where.offset(-size.left, -size.top);
  CColor cl = hitmap->getPoint(where);
  delete hitmap;

  if(cl==kWhiteCColor)
  {
/*
    if(mWithSnap)
    {
      // with snap
      if( (mIsPressed = !mIsPressed) && mParam )
      {
        mParam->StepVal(1,NFLG_ALL|NFLG_CLIP);
      }
      setDirty();
    }
*/
    switch(mMode)
    {
    default:
    case SWMD_INCREMENT:
      mIsPressed = true;
      if(mParam)
      {
        mParam->StepVal((int)mMval * (button&kControl ? button&kShift ? 100:10:1),NFLG_ALL|NFLG_CLIP|NFLG_FORCE);
      }
      break;
    case SWMD_CONSTANT:
      mIsPressed = true;
      if(mParam)
      {
        mParam->SetVal(mMval,NFLG_ALL|NFLG_CLIP);
      }
      break;
    }
    setDirty();
    while(1)
    {
      long button = dstcon->getMouseButtons();

      if(!(button & kLButton) || !mFrame)
      {
        mIsPressed = false;
        setDirty();
        break;
      }
      mFrame->doIdleStuff();
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CSwitch::CSwitch(int index, CBitmap *bgnd)
{
  // allocate a view
  mHandle = new CSwitchView(index,bgnd);
}


///////////////////////////////////////////////////////////////////////////////
//

CSwitch::~CSwitch()
{
  // destroy view if allocated
  CSwitchView *pview = (CSwitchView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitch::SetFrame(CFrame *frame, CPoint ofs)
{
  CSwitchView *pview = (CSwitchView *)mHandle;
  int i;

  if(pview /*&& pview->mFrame!=frame*/)
  {
    pview->SetFrame(frame,ofs);
    // and the leds also
    for(i=0; i<pview->mNumLeds; i++)
    {
      pview->mLeds[i]->SetFrame(frame);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitch::SetParam( CParam *inParam )
{
  CSwitchView *pview = (CSwitchView *)mHandle;

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
      pview->mParamNtf.min = pview->mParam->mMin;
      pview->mParamNtf.max = pview->mParam->mMax;
      pview->mParamNtf.inf[0] = pview;
      pview->mParamNtf.PstCbFn = pview->stNotifyPstCb;
      pview->mParam->AddNotify(&(pview->mParamNtf));
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitch::SetMode( int mode, float val )
{
  CSwitchView *pview = (CSwitchView *)mHandle;

  if(pview)
  {
    pview->mMode = mode;
    pview->mMval = val;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CSwitch::GetPosition( CRect *pos )
{
  CSwitchView *pview = (CSwitchView *)mHandle;

  if(pview)
  {
    *pos = pview->size;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CSwitch.cpp,v $
// Revision 1.8  2004/12/02 13:29:41  joffe
// bugfix: editor crash
//
// Revision 1.7  2004/11/17 16:22:44  joffe
// statics moved out of function-bodies
//
// Revision 1.6  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.5  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.4  2004/08/26 00:50:38  joffe
// buttonmode added
//
// Revision 1.3  2004/08/14 06:08:21  joffe
// cosmetics
//
// Revision 1.2  2004/08/04 00:32:45  joffe
// some switch-btmaps now smaller, new backrounds, remote displays added,
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
