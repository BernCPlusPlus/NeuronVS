///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CShaper.cpp,v $
// $Revision: 1.6 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "CShaper.h"
#include "resource.h"


// create own table of initialization data

typedef struct
{
  short top;
  short left;
  short prvwtop;
  short prvwleft;

} data;

const data stData[] =
{
#define CM(p1,p2,p3,p4,p5) {p2,p3,p4,p5},
#include "CShaper.h"
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

class   CPreview : public CView
{
public:
  CPreview(const CRect &size) : CView (size){};

  virtual void draw(CDrawContext *);
  virtual void mouse(CDrawContext *, CPoint &);

  CBitmap *mPrvwBmp;
  CBitmap *mPrvwBuf;
  bool    mShowPrv;
  CParam  *mHitParam;
  void    *mParent;
};


///////////////////////////////////////////////////////////////////////////////
//

class CShaperView : public CView
{
public:

  friend class CShaper;
  friend class CPreview;

  CShaperView(int index);
  ~CShaperView();

  void SetFrame(CFrame *frame, CPoint ofs);

  static void stNtfShprCb( float *val, CParam *inParam, void **inInfo );
  static void stHitPstCb( float *val, CParam *inParam, void **inInfo );
  virtual void draw(CDrawContext *);
  virtual void mouse(CDrawContext *, CPoint &);
  virtual long notify(CView *sender, const char *message);
  void dragval(CDrawContext *dstcon, CParam *param, CPoint &where, bool horz);

private:
  CFrame  *mFrame;

  CPreview *mPreview;
  CParam   *mShprA;
  CParam   *mShprD;
  CParam   *mShprS;
  CParam   *mShprR;
  CParam::td_notify mNtfShpr;
  CParam::td_notify mHitNtf;
  CRect   mSize;
  float   mHitVal;

  CBitmap *mBmpSrc;
  CBitmap *mBmpDst;
  CBitmap *mBmpHandle;
};


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CShaperView::CShaperView(int index) : CView(size)
{
  mSize(0,0, 458,71);
  mSize.offset(stData[index].left, stData[index].top);
  size = mSize;

  CFrame *tempframe = new CFrame(size,"temp",this);

  mFrame = 0;
  mPreview = 0;
  mShprA = 0;
  mShprD = 0;
  mShprS = 0;
  mShprR = 0;

  // init some working stuff
  index = (index>=0 && index<kNumShapers) ? index:0;
  if(stData[index].prvwtop>=0)
  {
    CBitmap *prvw = new CBitmap(IDB_SHAPERPRVW);
    int w = prvw->getWidth();
    int h = prvw->getHeight();
    CRect cr = CRect(0,0,w,h);
    cr.offset(stData[index].prvwleft,stData[index].prvwtop);
    mPreview = new CPreview(cr);
    mPreview->mPrvwBmp = prvw;
    mPreview->mPrvwBuf = new CBitmap(*tempframe, w, h);
    mPreview->mShowPrv = false;
    mPreview->mParent = this;
  }
  
  mHitVal = -1.;

  mBmpSrc = new CBitmap(*tempframe, 458, 71);
  mBmpDst = new CBitmap(*tempframe, 458, 71);
  mBmpHandle = new CBitmap(IDB_SHAPERHNDL);
}


///////////////////////////////////////////////////////////////////////////////
//

CShaperView::~CShaperView()
{
  if(mFrame) mFrame->removeView(this);

  mBmpHandle->forget();
  mBmpDst->forget();
  mBmpSrc->forget();

  if(mPreview)
  {
    if(mFrame) mFrame->removeView(mPreview);
    mPreview->mPrvwBmp->forget();
    mPreview->mPrvwBuf->forget();
    delete mPreview;
    mPreview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::stNtfShprCb( float *val, CParam *param, void **inf )
{
  CShaperView *pview = (CShaperView *)inf[0];
  if(pview)
  {
    pview->setDirty();
    if(pview->mPreview) pview->mPreview->setDirty();
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::stHitPstCb( float *pval, CParam *param, void **ppinf )
{
  CShaperView *pview = (CShaperView *)ppinf[0];
  float inval = pval[1];
  float oval = pval[0];

  if(pview->mFrame)
  {
    if( oval==pview->mHitVal)
    {
      pview->mFrame->removeView(pview);
    }
    else if(inval==pview->mHitVal)
    {
      pview->mFrame->addView(pview);
      pview->setDirty();
    }
  }
  pview->mPreview->mShowPrv = inval==pview->mHitVal;
  pview->mPreview->setDirty();
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::draw(CDrawContext *dstcon)
{
  CFrame *parentframe = getParent();
  COffscreenContext *ramcon;
  CPoint cp;
  CRect cr;
  getViewSize(cr);

  int i;
  long w = mBmpDst->getWidth();
  long h = mBmpDst->getHeight();
  CRect crram = CRect(0,0,w,h);
  CDrawContext *srccon = new CDrawContext(parentframe,0);

  ramcon = new COffscreenContext(srccon,mBmpSrc,true);
  getParent()->getBackground()->draw(ramcon, crram, cp(cr.left,cr.top));
  
  CPoint env[5],drw[5];
  CColor col;
  #define SCF 0.98f
  int a = mShprA ? (int)(mShprA->GetVal()*SCF) : 0;
  int d = mShprD ? (int)(mShprD->GetVal()*SCF) : 0;
  int s = mShprS ? (int)(mShprS->GetVal()*0.49f) : 0;
  int r = mShprR ? (int)(mShprR->GetVal()*SCF) : 0;
  #undef SCF

  env[0]( 6,       70);
  env[1](14+a,     4);
  env[2](22+a+d,   66-s);
  env[3](71+a+d,   66-s);
  env[4](79+a+d+r, 66);

  #define SHDW_H 6
  #define SHDW_V 5

  for(i=0; i<5; i++) drw[i](env[i].h+SHDW_H, env[i].v+SHDW_V);
  col(64,64,64,0);
  ramcon->setFrameColor(col);
  ramcon->setLineWidth(3);
#if MAC
  CPoint dtmp[5];
  for(int i=0; i<5; i++) dtmp[i](drw[i].h-1, drw[i].v-1);
  ramcon->polyLine(dtmp,5);
#else
  ramcon->polyLine(drw,5);
#endif
  col(96,96,96,0);
  ramcon->setLineWidth(2);
  ramcon->moveTo( CPoint(drw[1].h,0) );
  ramcon->lineTo( CPoint(drw[1].h,71) );
  ramcon->moveTo( CPoint(drw[2].h,0) );
  ramcon->lineTo( CPoint(drw[2].h,71) );
  ramcon->moveTo( CPoint(drw[3].h,0) );
  ramcon->lineTo( CPoint(drw[3].h,71) );
  ramcon->moveTo( CPoint(drw[4].h,0) );
  ramcon->lineTo( CPoint(drw[4].h,71) );
  col(0,0,0,0);
  ramcon->setFrameColor(col);
  ramcon->setLineWidth(1);
  ramcon->polyLine(drw,5);
  col(255,255,255,0);
  ramcon->setFrameColor(col);
  ramcon->setLineWidth(3);
#if MAC
  for(int i=0; i<5; i++) dtmp[i](env[i].h-1, env[i].v-1);
  ramcon->polyLine(dtmp,5);
#else
  ramcon->polyLine(env,5);
#endif

  delete ramcon;

  ramcon = new COffscreenContext(srccon,mBmpDst,true);
  getParent()->getBackground()->draw(ramcon, crram, cp(cr.left,cr.top));
  mBmpSrc->drawAlphaBlend(ramcon, crram, CPoint(0,0), 40);
  delete ramcon;

  ramcon = new COffscreenContext(srccon,mBmpSrc,true);
  getParent()->getBackground()->draw(ramcon, crram, cp(cr.left,cr.top));

  col(200,200,200,0);
  ramcon->setFrameColor(col);
  ramcon->setLineWidth(3);
#if MAC
  for(int i=0; i<5; i++) dtmp[i](env[i].h-1, env[i].v-1);
  ramcon->polyLine(dtmp,5);
#else
  ramcon->polyLine(env,5);
#endif
  col(255,255,255,0);
  ramcon->setFrameColor(col);
  ramcon->setLineWidth(1);
  ramcon->polyLine(env,5);
  ramcon->moveTo( CPoint(env[1].h,0) );
  ramcon->lineTo( CPoint(env[1].h,71) );
  ramcon->moveTo( CPoint(env[2].h,0) );
  ramcon->lineTo( CPoint(env[2].h,71) );
  ramcon->moveTo( CPoint(env[3].h,0) );
  ramcon->lineTo( CPoint(env[3].h,71) );
  ramcon->moveTo( CPoint(env[4].h,0) );
  ramcon->lineTo( CPoint(env[4].h,71) );
  delete ramcon;
  
  CRect tmpr;
  ramcon = new COffscreenContext(srccon,mBmpDst,true);
  mBmpSrc->drawAlphaBlend(ramcon, crram, CPoint(0,0), 128);
  mBmpHandle->draw(ramcon,tmpr(env[1].h-3,env[1].v-3,env[1].h+4,env[1].v+4));
  mBmpHandle->draw(ramcon,tmpr(env[2].h-3,env[2].v-3,env[2].h+4,env[2].v+4));
  mBmpHandle->draw(ramcon,tmpr(env[3].h-3,env[3].v-3,env[3].h+4,env[3].v+4));
  mBmpHandle->draw(ramcon,tmpr(env[4].h-3,env[4].v-3,env[4].h+4,env[4].v+4));

  delete ramcon;
  delete srccon;

  mBmpDst->draw(dstcon, cr);    
/*
  crram(0,0,500,100);
  mBmpSrc->draw(dstcon, crram);    
  crram(0,80,500,180);
  mBmpDst->draw(dstcon, crram);    
*/    
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

void CPreview::draw(CDrawContext *dstcon)
{
  CFrame *parentframe = getParent();
  CShaperView *pview = (CShaperView *)mParent;

  pview->setDirty();

  if(mPrvwBmp && parentframe)
  {
    CPoint cp;
    CRect cr;
    getViewSize(cr);
    long w = mPrvwBuf->getWidth();
    long h = mPrvwBuf->getHeight();
    CRect crram = CRect(0,0,w,h);
    CDrawContext *srccon = new CDrawContext(parentframe,0);
    COffscreenContext *ramcon = new COffscreenContext(srccon,mPrvwBuf,true);
    CColor col;

    if(mShowPrv)
    {
      mPrvwBmp->draw(ramcon, crram);    
    }
    else
    {
      getParent()->getBackground()->draw(ramcon, crram, cp(cr.left,cr.top));    
    }

    CPoint env[5];
    int a,d,s,r;

    #define SCF 0.134f
    a = pview->mShprA ? (int)(pview->mShprA->GetVal()*SCF) : 0;
    d = pview->mShprD ? (int)(pview->mShprD->GetVal()*SCF) : 0;
    s = pview->mShprS ? (int)(pview->mShprS->GetVal()*.15f) : 0;
    r = pview->mShprR ? (int)(pview->mShprR->GetVal()*SCF) : 0;
    #undef SCF

    env[0]( 1,       21);
    env[1]( 1+a,     1);
    env[2]( 2+a+d,   20-s);
    env[3](13+a+d,   20-s);
    env[4](14+a+d+r, 21);

    col(176,176,176,0);
    ramcon->setFrameColor(col);
    ramcon->setLineWidth(3);
#if MAC
    CPoint drw[5];
    for(int i=0; i<5; i++) drw[i](env[i].h-1, env[i].v-1);
    ramcon->polyLine(drw,5);
#else
    ramcon->polyLine(env,5);
#endif
    col(225,225,225,0);
    ramcon->setFrameColor(col);
    ramcon->setLineWidth(1);
    ramcon->polyLine(env,5);

    delete ramcon;
    delete srccon;

    if(mShowPrv)
    {
      mPrvwBmp->draw(dstcon, cr);    
    }
    else
    {
      getParent()->getBackground()->draw(dstcon, cr, cp(cr.left,cr.top));    
    }
    mPrvwBuf->drawAlphaBlend(dstcon, cr, CPoint(0,0), 192);    
    //mPrvwBuf->draw(dstcon, crram);    
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CPreview::mouse(CDrawContext *dstcon, CPoint &where)
{
  long button = dstcon->getMouseButtons();
  CShaperView *pview = (CShaperView *)mParent;

  if (!(button & kLButton))
  {
    return;
  }

  mHitParam->SetVal(pview->mHitVal,NFLG_ALL);
  while(1)
  {
    button = dstcon->getMouseButtons();

    if(!(button & kLButton))
    {
      break;
    }
    getParent()->doIdleStuff();
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::SetFrame(CFrame *frame, CPoint ofs)
{
  if(frame)
  {
    size = mSize;
    size.offset(-ofs.x, -ofs.y);

    // add this view to the frame
    if(mPreview)
    {
      CRect cr;
      mPreview->getViewSize(cr);
      cr.offset(-ofs.x, -ofs.y);
      mPreview->setViewSize(cr);
      frame->addView(mPreview);
      if(mPreview->mHitParam)
      {
        if(mPreview->mHitParam->GetVal() == mHitVal)
        {
          frame->addView(this);
        }
      }
    }
    else
    {
      frame->addView(this);
    }
  }
  else
  {
    // remove this view from the current frame
    if(mFrame)
    {
      mFrame->removeView(this);
      if(mPreview)
      {
        mFrame->removeView(mPreview);
      }
    }
  }
  mFrame = frame;
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::dragval(CDrawContext *dstcon, CParam *param, CPoint &where, bool horz)
{
  CPoint ref = where;
  float old = param->GetVal();
  int d;

	while(1)
	{
		long button = dstcon->getMouseButtons();
		if (!(button & kLButton))
    {
			break;
    }

		dstcon->getMouseLocation(where);
    d = horz ? where.x-ref.x : ref.y-where.y;
    param->SetVal(old+d, NFLG_ALL);

		mFrame->doIdleStuff();
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaperView::mouse(CDrawContext *dstcon, CPoint &where)
{
  long button = dstcon->getMouseButtons();

  if (!(button & kLButton))
  {
    return;
  }

  int x = where.x - mSize.x;
  int y = where.y - mSize.y;

  #define SCF 0.98f
  int a = mShprA ? (int)(mShprA->GetVal()*SCF) : 0;
  int d = mShprD ? (int)(mShprD->GetVal()*SCF) : 0;
  int s = mShprS ? (int)(mShprS->GetVal()*0.49f) : 0;
  int r = mShprR ? (int)(mShprR->GetVal()*SCF) : 0;
  #undef SCF

  if(     x>=(14+a-3) && x<=(14+a+3) && y>=(4-3) && y<=(4+3) )
    dragval(dstcon,mShprA, where, true);
  else if(x>=(22+a+d-3) && x<=(22+a+d+3) && y>=(66-s-3) && y<=(66-s+3))
    dragval(dstcon,mShprD, where, true);
  else if(x>=(71+a+d-3) && x<=(71+a+d+3) && y>=(66-s-3) && y<=(66-s+3))
    dragval(dstcon,mShprS, where, false);
  else if(x>=(79+a+d+r-3) && x<=(79+a+d+r+3) && y>=(66-3) && y<=(66+3))
    dragval(dstcon,mShprR, where, true);

  while(1)
  {
    button = dstcon->getMouseButtons();

    if(!(button & kLButton))
    {
      break;
    }
    getParent()->doIdleStuff();
  }

}


///////////////////////////////////////////////////////////////////////////////
//

long CShaperView::notify(CView *sender, const char *message)
{
  return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//

CShaper::CShaper(int index)
{
  // allocate a view
  mHandle = new CShaperView(index);
}


///////////////////////////////////////////////////////////////////////////////
//

CShaper::~CShaper()
{
  // destroy view if allocated
  CShaperView *pview = (CShaperView *)mHandle;
  if(pview)
  {
    if(pview->mPreview->mHitParam) pview->mPreview->mHitParam->RmvNotify(&(pview->mHitNtf));
    delete pview;
    pview = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetFrame(CFrame *frame, CPoint ofs)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    pview->SetFrame(frame,ofs);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetParamA(CParam *val)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mShprA)
    {
      pview->mShprA->RmvNotify(&(pview->mNtfShpr));
    }
    pview->mShprA = val;
    if(val)
    {
      pview->mShprA = val;
      pview->mNtfShpr.inf[0] = pview;
      pview->mNtfShpr.PstCbFn = pview->stNtfShprCb;
      pview->mShprA->AddNotify(&(pview->mNtfShpr), true, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetParamD(CParam *val)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mShprD)
    {
      pview->mShprD->RmvNotify(&(pview->mNtfShpr));
    }
    pview->mShprD = val;
    if(val)
    {
      pview->mShprD = val;
      pview->mNtfShpr.inf[0] = pview;
      pview->mNtfShpr.PstCbFn = pview->stNtfShprCb;
      pview->mShprD->AddNotify(&(pview->mNtfShpr), true, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetParamS(CParam *val)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mShprS)
    {
      pview->mShprS->RmvNotify(&(pview->mNtfShpr));
    }
    pview->mShprS = val;
    if(val)
    {
      pview->mShprS = val;
      pview->mNtfShpr.inf[0] = pview;
      pview->mNtfShpr.PstCbFn = pview->stNtfShprCb;
      pview->mShprS->AddNotify(&(pview->mNtfShpr), true, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetParamR(CParam *val)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mShprR)
    {
      pview->mShprR->RmvNotify(&(pview->mNtfShpr));
    }
    pview->mShprR = val;
    if(val)
    {
      pview->mShprR = val;
      pview->mNtfShpr.inf[0] = pview;
      pview->mNtfShpr.PstCbFn = pview->stNtfShprCb;
      pview->mShprR->AddNotify(&(pview->mNtfShpr), true, NFLG_SELF|NFLG_FORCE);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetHitParam(CParam *hit)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mPreview) 
    {
      pview->mPreview->mHitParam = hit;
      if(hit)
      {
        pview->mHitNtf.inf[0] = pview;
        pview->mHitNtf.PstCbFn = pview->stHitPstCb;
        pview->mPreview->mHitParam->AddNotify(&(pview->mHitNtf),true);
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void CShaper::SetHitVal(float val)
{
  CShaperView *pview = (CShaperView *)mHandle;

  if(pview)
  {
    if(pview->mPreview) pview->mHitVal = val;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CShaper.cpp,v $
// Revision 1.6  2004/11/22 05:07:43  joffe
// mac adaptions
//
// Revision 1.5  2004/11/21 22:46:41  joffe
// shaper-edit implemented
//
// Revision 1.4  2004/11/20 09:14:48  joffe
// mac adaptions
//
// Revision 1.3  2004/11/20 08:22:35  joffe
// first implementation of shaper-previews
//
// Revision 1.2  2004/08/25 03:54:04  joffe
// more checking/security
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
