///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDial.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that supports scrollers for VstGui
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

//                    |Position|                   |
//   ID               |Top Left|  Display-ID       |

CM(kDialR1Volume,      101, 133,  kDisplayR1Volume )
CM(kDialR2Volume,      101, 664,  kDisplayR2Volume )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CDIAL_H
#define CDIAL_H

#include "vstgui.h"
#include "CParam.h"
#include "CDisplay.h"


class CDial
{
public:

  CDial(int inEnumedId);
  ~CDial();

  // SetFrame sets/attaches the scroller to a given Frame. 0 as inFrame
  // disables/detaches the scroller, but keeps all other settings
  void SetFrame( CFrame *inFrame, CPoint ofs );

  // SetParam sets the parameter that will be modified by this scroller.
  // The parameter is shown via its LEDBar. 0 as inParam unsets the param
  void SetParam( CParam *inParam );

private:

  void *mHandle;

};

// enum all elements

enum
{
#define CM(p1,p2,p3,p4) p1,
#include __FILE__

  kNumDials
};

#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDial.h,v $
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
