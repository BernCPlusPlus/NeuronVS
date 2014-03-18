///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CShaper.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that draws backgrounds
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

//                  | Position  | Preview   |
//   ID             | Top  Left | Top  Left |

CM(kShaper1Resy,      518, 172,   525,  35 )
CM(kShaper1Amp,       518, 172,   567,  23 )
CM(kShaper1Free,      518, 172,   609,  35 )
CM(kShaper2Resy,      518, 172,   525, 701 )
CM(kShaper2Amp,       518, 172,   567, 713 )
CM(kShaper2Free,      518, 172,   609, 701 )
CM(kShaper3,          520, 172,    -1,  -1 )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CSHAPER_H
#define CSHAPER_H

#include "vstgui.h"
#include "CParam.h"


class CShaper
{
public:

  CShaper(int inEnumedId );
  ~CShaper();

  void SetFrame( CFrame *iFrame, CPoint iOfs );

  void SetParamA(CParam *inVal);
  void SetParamD(CParam *inVal);
  void SetParamS(CParam *inVal);
  void SetParamR(CParam *inVal);

  void SetHitParam(CParam *inHit);
  void SetHitVal(float inVal);

private:

  void *mHandle;

};

// enum all elements

enum
{
#define CM(p1,p2,p3,p4,p5) p1,
#include __FILE__

  kNumShapers
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CShaper.h,v $
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
