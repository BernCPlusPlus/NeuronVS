///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDisplay.cpp,v $
// $Revision: 1.11 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#define  xPAINTFONT

#include <stdio.h>
#include <string.h>

#include "CDisplay.h"

#include "resource.h"


///////////////////////////////////////////////////////////////////////////////
// own constants and defines

static CColor kTransparent = {128,128,128,0};

#define NUM_CHARS  18   // maximum number of chars that can be displayed


typedef struct
{
  CBitmap *font;
  int     *refcount;

} td_fontrsc;

static td_fontrsc *stFonts = 0;
static bool stConverted = false;


// create own font-info table

typedef struct
{
  long  resid;      // resource-ID
  short charwidth;  // width of one char
  short charofs;    // left offset where to begin painting of a char
  short paintwidth; // width to paint

} tdfont;

const tdfont stFont[kNumFtTypes] =
{
  {IDB_FONTBIG,    16, 3, 8},
  {IDB_FONTSMALL,  16, 5, 5},
};

//const int kNumFonts = sizeof(stFont)/sizeof(stFont[0]);

// luminance clipping array

static unsigned char stClip[3*256];
static bool stClipInit = false;


// create own table of initialization data

typedef struct
{
  short top;
  short left;
  short height;
  short width;
  char  chars;
  short fontnum;
  short x_align;
  short y_align;
  short edit;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) {p2,p3,p4,p5,p6,p7,p8,p9,p10},
#include "CDisplay.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class CDisplayView : public CTextEdit, CControlListener
{
public:

  friend class CDisplay;

  CDisplayView(int index);
  ~CDisplayView();

  virtual void draw(CDrawContext *);
  void drawofl(void);
  virtual void mouse(CDrawContext *, CPoint &);

private:
  void valueChanged(CDrawContext *pContext, CControl *pControl);

  CFrame  *mFrame;
  CRect   mSize;
  char    mText[NUM_CHARS+1];
  CView   *mParentView;
  int     mFontNum;
  CBitmap *mFontBmp;
  CBitmap *mDsplBmp;
  bool    m1stSight;
  bool    mDrawText;
  CView   *mView;
  int     mEdit;
  int     mCharWidth;
  int     mCharOfs;
  int     mPaintWidth;
  int     mCharsfit;
  int     mXAlign;
  int     mYAlign;
};


///////////////////////////////////////////////////////////////////////////////
//

CDisplayView::CDisplayView(int index) : CTextEdit(size,0,0)
{
  listener = this;

  if(!stFonts)
  {
    stFonts = new td_fontrsc[kNumFtTypes];

    for(int i=0; i<kNumFtTypes; i++)
    {
      stFonts[i].font = new CBitmap(stFont[i].resid);
      stFonts[i].font->setTransparentColor(kTransparent);
      stFonts[i].refcount = 0;
    }
  }

  // init some working stuff
  index = (index>=0 && index<kNumDisplays) ? index:0;
  mSize(0, 0, stData[index].width,stData[index].height);
  mSize.offset(stData[index].left, stData[index].top);
  size = mSize;
  memset(mText, 0, sizeof(mText));
  mParentView = 0;
  mFrame = 0;
  m1stSight = true;
  mDrawText = false;
  mEdit = stData[index].edit;

  // get bitmap for charset
  int fn = stData[index].fontnum;
  fn = (fn>=0 && fn<kNumFtTypes) ? fn:0;
  mFontNum = fn;
  mFontBmp = stFonts[fn].font;
  stFonts[mFontNum].refcount++;

  mCharWidth  = stFont[fn].charwidth;
  mCharOfs    = stFont[fn].charofs;
  mPaintWidth = stFont[fn].paintwidth;

  mCharsfit = stData[index].chars;
  mXAlign = stData[index].x_align;
  mYAlign = stData[index].y_align;

  CFrame *tempframe = new CFrame(size,"temp",this);
  int wdth = mPaintWidth*(mCharsfit-1) + mCharWidth-mCharOfs-1;
  mDsplBmp = new CBitmap(*tempframe, wdth, mFontBmp->getHeight());
}


///////////////////////////////////////////////////////////////////////////////
//

CDisplayView::~CDisplayView()
{
  if(mFrame) mFrame->removeView(this);
  stFonts[mFontNum].refcount--;
  mDsplBmp->forget(); mDsplBmp = 0;
}


///////////////////////////////////////////////////////////////////////////////
//

void CDisplayView::draw(CDrawContext *dstcon)
{
  CPoint cp;
  CRect  cr;
  int x,y;

  setDirty(false);

  if(!mDrawText)
  {
    x = size.left + mXAlign;
    y = size.top + mYAlign;
    long dsplw = mDsplBmp->getWidth();
    long dsplh = mDsplBmp->getHeight();

    cr = CRect(x,y, x+dsplw, y+dsplh);
    cp = CPoint(0, 0);

    mDsplBmp->draw(dstcon, cr, cp);
 	}
  else
  {
    drawText (dstcon, text);
    mDrawText = false;
  }

#ifdef PAINTFONT

  x = stFonts[0].font->getWidth();
  y = stFonts[0].font->getHeight();

  cp = CPoint(0,0);
  cr = CRect(4,4,x/2+4,y+4);
  stFonts[0].font->draw(dstcon,cr,cp);
  cp = CPoint(x/2,0);
  cr = CRect(4,y+8,x/2+4,y+y+8);
  stFonts[0].font->draw(dstcon,cr,cp);

  x = stFonts[1].font->getWidth();
  y = stFonts[1].font->getHeight();

  cp = CPoint(0,0);
  cr = CRect(4,64,x/2+4,y+64);
  stFonts[1].font->draw(dstcon,cr,cp);
  cp = CPoint(x/2,0);
  cr = CRect(4,y+68,x/2+4,y+y+68);
  stFonts[1].font->draw(dstcon,cr,cp);

#endif
}


///////////////////////////////////////////////////////////////////////////////
//

void CDisplayView::drawofl(void)
{
  CFrame *parentframe = getParent();
  if(!parentframe) return;

  CDrawContext *srccon;
  long dsplw,dsplh;

#if 1     // quantise near-grey to grey for transparent-draw
          // could be removed if q'ed bitmap is compiled to resource
  if(stConverted==false)
  {
    stConverted = true;

    srccon = new CDrawContext(parentframe,0);
    COffscreenContext *charcon;
    CColor pcl;
    int w,h;

    for(int nf=0; nf<kNumFtTypes; nf++)
    {
      dsplw = stFonts[nf].font->getWidth();
      dsplh = stFonts[nf].font->getHeight();
      charcon = new COffscreenContext(srccon,stFonts[nf].font,true);
      CPoint cp = CPoint(0,0);
      CRect  cr = CRect(0,0, dsplw,dsplh);
      stFonts[nf].font->draw(charcon, cr, cp );
      for(w=0; w<dsplw; w++)
      {
        for(h=0; h<dsplh; h++)
        {
          #define RNG 14

          pcl = charcon->getPoint(CPoint(w,h));
          if( pcl.red==128 && pcl.green==128 && pcl.blue==128 ) continue;
          if(pcl.red<(128-RNG)   || pcl.red>128+RNG)   continue;
          if(pcl.green<(128-RNG) || pcl.green>128+RNG) continue;
          if(pcl.blue<(128-RNG)  || pcl.blue>128+RNG)  continue;
          pcl.red=pcl.green=pcl.blue = 128;
          charcon->drawPoint(CPoint(w,h), pcl);
        }
      }
      delete charcon;
    }
    delete srccon;
  }
#endif

#if 0   // 0=PixelDrawing, else transparent drawing

  COffscreenContext *charcon;
  CPoint cp;
  CRect  cr;
  char c;
  dsplw = mDsplBmp->getWidth();
  dsplh = mDsplBmp->getHeight();
  CBitmap *bgnd = parentframe->getBackground();
  
  // get fresh background image
  cp = CPoint(size.left+mXAlign,size.top+mYAlign);
  cr = CRect(0,0,dsplw,dsplh);
  srccon = new CDrawContext(parentframe,0);
  COffscreenContext *dspcon = new COffscreenContext(srccon,mDsplBmp,true);
  bgnd->draw(dspcon, cr, cp);

  // get fresh font image
  cp = CPoint(0,0);
  cr = CRect(0,0, mFontBmp->getWidth(),mFontBmp->getHeight());
  charcon = new COffscreenContext(parentframe,mFontBmp->getWidth(),mFontBmp->getHeight());

  CColor scl,dcl;
  mFontBmp->draw(charcon, cr, cp );

  for(int i=0; i<mCharsfit && (c = mText[i]); i++)
  {
    int h,w,wd = i*mPaintWidth;
    int ws = (c - 33) * mCharWidth; // left position in font

    if(ws < 0)
    {
      continue;
    }

    for(w=0,ws+=mCharOfs; w<(mCharWidth-mCharOfs); w++,ws++,wd++)
    {
      for(h=0; h<dsplh; h++)
      {
        scl = charcon->getPoint(CPoint(ws,h));
        if( scl.red==128 && scl.green==128 && scl.blue==128 ) continue;
        dcl = dspcon->getPoint(CPoint(wd,h));
        dcl.red   = stClip[scl.red + (scl.red>>1) + dcl.red];
        dcl.green = stClip[scl.green + (scl.green>>1) + dcl.green];
        dcl.blue  = stClip[scl.blue + (scl.blue>>1) + dcl.blue];
        dspcon->drawPoint(CPoint(wd,h), dcl);
      }
    }
  }

  delete srccon;
  delete dspcon;
  delete charcon;

#else

  CPoint cp;
  CRect  cr;
  char c;
  dsplw = mDsplBmp->getWidth();
  dsplh = mDsplBmp->getHeight();

  // get fresh background image
  CBitmap *bgnd = parentframe->getBackground();
  cp = CPoint(size.left+mXAlign,size.top+mYAlign);
  cr = CRect(0,0,dsplw,dsplh);
  srccon = new CDrawContext(parentframe,0);
  COffscreenContext *dspcon = new COffscreenContext(srccon,mDsplBmp,true);
  bgnd->draw(dspcon, cr, cp);

  for(int i=0; i<mCharsfit && (c = mText[i]); i++)
  {
    int ws = (c - 33) * mCharWidth; // left position in font

    if(ws < 0)
    {
      continue;
    }

    CPoint dp = CPoint(ws+mCharOfs,0);
    CRect  dr = CRect(i*mPaintWidth,0, i*mPaintWidth+mCharWidth,dsplh);
    mFontBmp->drawTransparent(dspcon, dr, dp);
  }

  delete srccon;
  delete dspcon;

#endif

  m1stSight = false;
  setDirty(true);
}


///////////////////////////////////////////////////////////////////////////////
//

static unsigned long stTicks;

void CDisplayView::mouse(CDrawContext *dstcon, CPoint &where)
{
  unsigned long delta=250, ticks = getParent()->getTicks();
  bool dblclick = false;
	long button = dstcon->getMouseButtons();

  if (!(button & kLButton))
  {
		return;
  }

  dblclick = (ticks-stTicks)<delta;
  stTicks = ticks;

  if(dblclick)
  {
    if(mEdit)
    {
      getParent()->setEditView(this);
      setBackColor(kGreyCColor);
      setFontColor(kWhiteCColor);
      setText(mText);
      takeFocus(dstcon);
      mDrawText = true;
    }
  }
  else
  {
    if(mParentView)
    {
      mParentView->notify(mView,(const char *)VNTF_MOUSE);
      mParentView->mouse(dstcon,where);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDisplayView::valueChanged(CDrawContext *pContext, CControl *pControl)
{
  if(mParentView)
  {
    mParentView->notify(this,text);
    mFrame->setDirty();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CDisplay::CDisplay(int index)
{
  // init clip-array if still not done
  if(stClipInit==false)
  {
    for(int i=0; i<(int)sizeof(stClip); i++)
    {
      stClip[i] = (i<192) ? 0 : (i>(192+255)) ? 255 : (i-192);
    }
    stClipInit = true;
  }

  // allocate a view
  mHandle = new CDisplayView(index);

  CDisplayView *pview = (CDisplayView *)mHandle;
  if(pview)
  {
    pview->mView = (CView *)this;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

CDisplay::~CDisplay()
{
  // destroy view if allocated
  CDisplayView *pview = (CDisplayView *)mHandle;
  if(pview)
  {
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDisplay::SetFrame(CFrame *frame, CPoint ofs, CView *parent)
{
  CDisplayView *pview = (CDisplayView *)mHandle;

  if(pview)
  {
    pview->mParentView = parent;
    if(frame)
    {
      pview->size = pview->mSize;
      pview->size.offset(-ofs.x, -ofs.y);
      // add this view to the frame
      frame->addView(pview);
      pview->setDirty();
      if(pview->m1stSight)
      {
        pview->drawofl();
      }
    }
    else
    {
      // remove this view from the current frame
	    if(pview->getParent()) pview->getParent()->removeView(pview);
    }
    pview->mFrame = frame;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CDisplay::SetText(const char *text)
{
  CDisplayView *pview = (CDisplayView *)mHandle;

  if(pview)
  {
    strncpy(pview->mText, text, NUM_CHARS);
    pview->m1stSight = true;
    if(pview->mFrame) pview->drawofl();
  }
}

///////////////////////////////////////////////////////////////////////////////
//

void CDisplay::SetInt(int val, bool bipolar)
{
  char buf[32];
  const char *fmt = bipolar ? "%+02.2i" : "%03i";

  sprintf(buf,fmt,val);
  SetText(buf);
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDisplay.cpp,v $
// Revision 1.11  2004/12/02 13:30:02  joffe
// bugfix: editor crash
//
// Revision 1.10  2004/11/22 19:02:33  joffe
// bugfix: display-update
//
// Revision 1.9  2004/11/19 11:03:37  joffe
// stickdraw speedup
//
// Revision 1.8  2004/11/17 16:22:44  joffe
// statics moved out of function-bodies
//
// Revision 1.7  2004/11/11 03:12:08  joffe
// minor bugfixes
//
// Revision 1.6  2004/10/19 03:50:36  joffe
// dblclick edit mac adaptions
//
// Revision 1.5  2004/10/18 06:41:33  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.4  2004/10/05 18:21:40  joffe
// destructor improvements
//
// Revision 1.3  2004/08/25 03:49:47  joffe
// more checking/security
//
// Revision 1.2  2004/08/04 00:32:45  joffe
// some switch-btmaps now smaller, new backrounds, remote displays added,
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
