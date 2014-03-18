///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CLed.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that supports switches/buttons for VstGui
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

//                              | Position  |
//   ID                         |Top    Left|

CM(kLedR1L1,                     272,    57 )
CM(kLedR1L2,                     264,    57 )
CM(kLedR1L3,                     258,    57 )
CM(kLedR1TypeSphere,             287,    57 )
CM(kLedR1TypeScape,              295,    57 )
CM(kLedR1AnimOneShot,            261,   295 )
CM(kLedR1AnimRepeat,             269,   295 )
CM(kLedR1ContourStick,           287,   295 )
CM(kLedR1ContourShaper,          295,   295 )
CM(kLedR1SelectCtx1,             405,   151 )
CM(kLedR1SelectCtx2,             405,   200 )
CM(kLedR1SelectCtx3,             429,   200 )
CM(kLedR1SelectCtx4,             429,   151 )

CM(kLedR2L1,                     272,   496 )
CM(kLedR2L2,                     264,   496 )
CM(kLedR2L3,                     258,   496 )
CM(kLedR2TypeSphere,             287,   496 )
CM(kLedR2TypeScape,              295,   496 )
CM(kLedR2AnimOneShot,            261,   734 )
CM(kLedR2AnimRepeat,             269,   734 )
CM(kLedR2ContourStick,           287,   734 )
CM(kLedR2ContourShaper,          295,   734 )
CM(kLedR2SelectCtx1,             405,   590 )
CM(kLedR2SelectCtx2,             405,   639 )
CM(kLedR2SelectCtx3,             429,   639 )
CM(kLedR2SelectCtx4,             429,   590 )

CM(kLedShaper12ModeNormal,       615,   296 )
CM(kLedShaper12ModeRepeat,       623,   296 )

CM(kLedSilverL1,                 210,   277 )
CM(kLedSilverL2,                 202,   277 )
CM(kLedSilverL3,                 194,   277 )
CM(kLedSilverAnimOneShot,        185,   515 )
CM(kLedSilverAnimRepeat,         193,   515 )
CM(kLedSilverContourStick,       211,   515 )
CM(kLedSilverContourShaper,      219,   515 )

CM(kLedSlicerType3D,             118,   624 )
CM(kLedSlicerTypeVertical,       126,   624 )

CM(kLedShaper3ModeNormal,        616,   303 )
CM(kLedShaper3ModeRepeat,        624,   303 )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CLED_H
#define CLED_H

#include "vstgui.h"
#include "CParam.h"


class CLed
{
public:

  CLed(int inEnumedId);
  ~CLed();

  // SetFrame sets/attaches the LED to a given Frame. 0 as inFrame
  // disables/detaches the LED, but keeps all other settings
  void SetFrame( CFrame *inFrame );

  // SetLed switches on or of the LED
  void SetLed( bool inOnOff );

private:

  void *mHandle;

};

// enum all elements

enum
{
#define CM(p1,p2,p3) p1,
#include __FILE__

  kNumLeds
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CLed.h,v $
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
