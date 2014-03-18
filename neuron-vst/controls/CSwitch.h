///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CSwitch.h,v $
// $Revision: 1.5 $
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

#ifndef CSWITCH_H

enum
{
  kSwTypeSmall,   // small button for pages (normal & red)
  kSwTypeBig,     // bigger version (normal & red)
  kSwTypeStd,     // standard button (none)
  kSwTypeLvl,     // level button (1-3)
  kSwTypeRec,     // record button (normal, on, blink)
  kSwTypeArw,     // arrow-type for eq-selections (normal & orange)
  kSwTypeModule,  // module on/offs (normal & enlightet)

  kNumSwTypes
};

#endif  // XXXX_H


#ifdef CM   // ControlMacro defined

//                             | Position  |                | with |
//   ID                        |Top    Left|  Switch-Type   | Snap |

//
// General
//

CM(kSwitchMpSndUp,               17,   255,  kSwTypeSmall,       0 )
CM(kSwitchMpSndDn,               32,   255,  kSwTypeSmall,       0 )

CM(kSwitchMpSndLoad,             20,   427,  kSwTypeStd,         0 )
CM(kSwitchMpSndSave,             20,   470,  kSwTypeStd,         0 )
CM(kSwitchMpSndSaveAs,           20,   513,  kSwTypeStd,         0 )


CM(kSwitchMpResys,               69,   360,  kSwTypeSmall,       0 )
CM(kSwitchMpSilver,              69,   393,  kSwTypeSmall,       0 )
CM(kSwitchMpRemote,              69,   426,  kSwTypeSmall,       0 )

CM(kSwitchMpAbout,               69,   393,  kSwTypeSmall,       0 )
CM(kSwitchMpAboutOff,          -999,  -999,  kSwTypeSmall,       0 )

//
// Resynator 1
//

CM(kSwitchR1Switch,              60,    29,  kSwTypeModule,      0 )

CM(kSwitchR1ModelSelect,         93,   293,  kSwTypeStd,         0 )

CM(kSwitchR1Record,             197,   166,  kSwTypeRec,         0 )
CM(kSwitchR1ParamLevel,         259,    74,  kSwTypeLvl,         0 )
CM(kSwitchR1Type,               284,    74,  kSwTypeStd,         0 )
CM(kSwitchR1CtxStickPb,         258,   260,  kSwTypeStd,         0 )
CM(kSwitchR1CtxContour,         284,   260,  kSwTypeStd,         0 )

CM(kSwitchR1OctavM2,            380,   140,  kSwTypeSmall,       0 )
CM(kSwitchR1OctavM1,            380,   162,  kSwTypeSmall,       0 )
CM(kSwitchR1OctavP0,            380,   184,  kSwTypeSmall,       0 )
CM(kSwitchR1OctavP1,            380,   206,  kSwTypeSmall,       0 )

CM(kSwitchR1CtxSelectXY,        411,   166,  kSwTypeStd,         0 )

//
// Resynator 2
//

CM(kSwitchR2Switch,              60,   686,  kSwTypeModule,      0 )

CM(kSwitchR2ModelSelect,         93,   477,  kSwTypeStd,         0 )

CM(kSwitchR2Record,             197,   605,  kSwTypeRec,         0 )
CM(kSwitchR2ParamLevel,         259,   513,  kSwTypeLvl,         0 )
CM(kSwitchR2Type,               284,   513,  kSwTypeStd,         0 )
CM(kSwitchR2CtxStickPb,         258,   699,  kSwTypeStd,         0 )
CM(kSwitchR2CtxContour,         284,   699,  kSwTypeStd,         0 )

CM(kSwitchR2OctavM2,            380,   579,  kSwTypeSmall,       0 )
CM(kSwitchR2OctavM1,            380,   601,  kSwTypeSmall,       0 )
CM(kSwitchR2OctavP0,            380,   623,  kSwTypeSmall,       0 )
CM(kSwitchR2OctavP1,            380,   645,  kSwTypeSmall,       0 )

CM(kSwitchR2CtxSelectXY,        411,   605,  kSwTypeStd,         0 )

//
// Blender

//
CM(kSwitchBlenderType,          196,   385,  kSwTypeStd,         0 )


//
// Shaper 1/2
//

CM(kSwitchShaper12CtxMode,      612,   257,  kSwTypeStd,         0 )

//
// MOD/LFO
//

CM(kSwitchLfoSwitch,             95,    89,  kSwTypeModule,      0 )

CM(kSwitchLfoWfTri,             213,    61,  kSwTypeBig,         0 )
CM(kSwitchLfoWfSine,            213,    89,  kSwTypeBig,         0 )
CM(kSwitchLfoWfSawUp,           213,   117,  kSwTypeBig,         0 )
CM(kSwitchLfoWfSawDown,         213,   145,  kSwTypeBig,         0 )
CM(kSwitchLfoWfSquare,          241,    61,  kSwTypeBig,         0 )
CM(kSwitchLfoWfPosTri,          241,    89,  kSwTypeBig,         0 )
CM(kSwitchLfoWfPosSine,         241,   117,  kSwTypeBig,         0 )
CM(kSwitchLfoWfPosSquare,       241,   145,  kSwTypeBig,         0 )
CM(kSwitchLfoWfStepTri,         269,    61,  kSwTypeBig,         0 )
CM(kSwitchLfoWfStepSawUp,       269,    89,  kSwTypeBig,         0 )
CM(kSwitchLfoWfStepSawDown,     269,   117,  kSwTypeBig,         0 )
CM(kSwitchLfoWfRandom,          269,   145,  kSwTypeBig,         0 )

//
// Silver
//
CM(kSwitchSilverSwitch,          95,   373,  kSwTypeModule,      0 )

CM(kSwitchSilverRecord,         115,   386,  kSwTypeRec,         0 )
CM(kSwitchSilverParamLevel,     196,   294,  kSwTypeLvl,         0 )
CM(kSwitchSilverCtxStickPb,     182,   480,  kSwTypeStd,         0 )
CM(kSwitchSilverCtxContour,     208,   480,  kSwTypeStd,         0 )

CM(kSwitchFilterType,           339,   385,  kSwTypeStd,         0 )

//
// Freq FX
//

CM(kSwitchFfxSwitch,            295,   231,  kSwTypeModule,      0 )
CM(kSwitchFfxTypeEQComp,        321,    43,  kSwTypeBig,         0 )
CM(kSwitchFfxTypeDistortion,    321,    88,  kSwTypeBig,         0 )
CM(kSwitchFfxTypeRingMod,       321,   133,  kSwTypeBig,         0 )
CM(kSwitchFfxTypeDecimator,     321,   178,  kSwTypeBig,         0 )
CM(kSwitchFfxTypeSpWarp,        321,   223,  kSwTypeBig,         0 )

// --- EQ/Compressor
CM(kSwitchFfxEQSwitch,          116,    18,  kSwTypeModule,      0 )
CM(kSwitchFfxEQLowSwitch,        74,    28,  kSwTypeSmall,       0 )
CM(kSwitchFfxEQBand1Switch,      74,    28,  kSwTypeSmall,       0 )
CM(kSwitchFfxEQBand2Switch,      74,    28,  kSwTypeSmall,       0 )
CM(kSwitchFfxEQHighSwitch,       74,    28,  kSwTypeSmall,       0 )
CM(kSwitchFfxCRSwitch,           74,    28,  kSwTypeSmall,       0 )
CM(kSwitchFfxEQLowSub   ,        43,    37,  kSwTypeArw,         0 )
CM(kSwitchFfxEQBand1Sub,         43,    77,  kSwTypeArw,         0 )
CM(kSwitchFfxEQBand2Sub,         43,   117,  kSwTypeArw,         0 )
CM(kSwitchFfxEQHighSub,          43,   157,  kSwTypeArw,         0 )
CM(kSwitchFfxCRSub,              43,   197,  kSwTypeArw,         0 )

// --- Distortion
CM(kSwitchFfxDSClipChop,         37,    23,  kSwTypeBig,         0 )
CM(kSwitchFfxDSClipLin,          37,    58,  kSwTypeBig,         0 )
CM(kSwitchFfxDSClipRipple,       37,    92,  kSwTypeBig,         0 )
CM(kSwitchFfxDSClipSoftKnee,     37,   127,  kSwTypeBig,         0 )
CM(kSwitchFfxDSClipSigmoid,      37,   162,  kSwTypeBig,         0 )
CM(kSwitchFfxDSClipExp,          37,   197,  kSwTypeBig,         0 )

// --- Ring Modulator
CM(kSwitchFfxRMSub1,              7,    79,  kSwTypeSmall,       0 )
CM(kSwitchFfxRMSub2,              7,   147,  kSwTypeSmall,       0 )

CM(kSwitchFfxRMWfTri,            28,    48,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfSine,           28,    78,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfSawUp,          28,   108,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfSawDown,        28,   138,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfSquare,         28,   168,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfPosTri,         28,   198,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfPosSine,        52,    48,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfPosSquare,      52,    78,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfStepTri,        52,   108,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfStepSawUp,      52,   138,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfStepSawDown,    52,   168,  kSwTypeBig,         0 )
CM(kSwitchFfxRMWfRandom,         52,   198,  kSwTypeBig,         0 )


//
// Time FX
//

CM(kSwitchTfxSwitch,            295,   499,  kSwTypeModule,      0 )

CM(kSwitchTfxTypeStereoSpr,     321,   556,  kSwTypeBig,         0 )
CM(kSwitchTfxTypeLRDelay,       321,   601,  kSwTypeBig,         0 )
CM(kSwitchTfxTypeFlanger,       321,   646,  kSwTypeBig,         0 )
CM(kSwitchTfxTypePhaser,        321,   691,  kSwTypeBig,         0 )
CM(kSwitchTfxTypeChorus,        321,   736,  kSwTypeBig,         0 )

// --- Flanger
CM(kSwitchTfxFLSub1,              7,    79,  kSwTypeSmall,       0 )
CM(kSwitchTfxFLSub2,              7,   147,  kSwTypeSmall,       0 )

CM(kSwitchTfxFLWfTri,            28,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfSine,           28,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfSawUp,          28,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfSawDown,        28,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfSquare,         28,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfPosTri,         28,   198,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfPosSine,        52,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfPosSquare,      52,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfStepTri,        52,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfStepSawUp,      52,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfStepSawDown,    52,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxFLWfRandom,         52,   198,  kSwTypeBig,         0 )

// --- Phaser
CM(kSwitchTfxPHSub1,              7,    79,  kSwTypeSmall,       0 )
CM(kSwitchTfxPHSub2,              7,   147,  kSwTypeSmall,       0 )

CM(kSwitchTfxPHWfTri,            28,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfSine,           28,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfSawUp,          28,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfSawDown,        28,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfSquare,         28,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfPosTri,         28,   198,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfPosSine,        52,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfPosSquare,      52,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfStepTri,        52,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfStepSawUp,      52,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfStepSawDown,    52,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxPHWfRandom,         52,   198,  kSwTypeBig,         0 )

// --- Chorus
CM(kSwitchTfxCHSub1,              7,    79,  kSwTypeSmall,       0 )
CM(kSwitchTfxCHSub2,              7,   147,  kSwTypeSmall,       0 )

CM(kSwitchTfxCHWfTri,            28,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfSine,           28,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfSawUp,          28,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfSawDown,        28,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfSquare,         28,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfPosTri,         28,   198,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfPosSine,        52,    48,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfPosSquare,      52,    78,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfStepTri,        52,   108,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfStepSawUp,      52,   138,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfStepSawDown,    52,   168,  kSwTypeBig,         0 )
CM(kSwitchTfxCHWfRandom,         52,   198,  kSwTypeBig,         0 )

//
// Slicer
//

CM(kSwitchSlicerSwitch,          95,   664,  kSwTypeModule,      0 )

CM(kSwitchSlicerType,           137,   615,  kSwTypeStd,         0 )

CM(kSwitchSlicerWfTri,          213,   640,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfSine,         213,   668,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfSawUp,        213,   696,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfSawDown,      213,   724,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfSquare,       241,   640,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfPosTri,       241,   668,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfPosSine,      241,   696,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfPosSquare,    241,   724,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfStepTri,      269,   640,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfStepSawUp,    269,   668,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfStepSawDown,  269,   696,  kSwTypeBig,         0 )
CM(kSwitchSlicerWfRandom,       269,   724,  kSwTypeBig,         0 )

//
// Shaper 3
//

CM(kSwitchShaper3Mode,          613,   264,  kSwTypeStd,         0 )

//
// Remote
//

CM(kSwitchKnob1Select,          296,    25,  kSwTypeStd,         0 )
CM(kSwitchKnob2Select,          217,    66,  kSwTypeStd,         0 )
CM(kSwitchKnob3Select,          217,   703,  kSwTypeStd,         0 )
CM(kSwitchKnob4Select,          296,   746,  kSwTypeStd,         0 )

CM(kSwitchDestAftertouch,       566,    63,  kSwTypeStd,         0 )
CM(kSwitchDestModulation,       566,   192,  kSwTypeStd,         0 )
CM(kSwitchDestBreath,           566,   321,  kSwTypeStd,         0 )
CM(kSwitchDestCC03,             566,   450,  kSwTypeStd,         0 )
CM(kSwitchDestFoot,             566,   579,  kSwTypeStd,         0 )
CM(kSwitchDestExpression,       566,   708,  kSwTypeStd,         0 )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CSWITCH_H
#define CSWITCH_H

#include "vstgui.h"
#include "CParam.h"

#define SWMD_OFFLIKE    0
#define SWMD_INCREMENT  1
#define SWMD_CONSTANT   2


class CSwitch
{
public:

  CSwitch(int inEnumedId, CBitmap *inBackground);
  ~CSwitch();

  // SetFrame sets/attaches the switch to a given Frame. 0 as inFrame
  // disables/detaches the switch, but keeps all other settings
  void SetFrame( CFrame *inFrame, CPoint inOffset );

  // SetParam sets the parameter(s) that will be modified by this switch.
  // The parameter is shown via its LEDs (if LED available). 0 as inParam
  // unsets the param.
  void SetParam( CParam *inParam );

  // SetMode sets operational mode. available are incremental
  // and constant mode. see SWMD_xxx defines. mVal gives the
  // increment or setval value for a pressed button
  void SetMode( int inMode, float inMval );

  // GetPosition returns the top/left/width/height rect of the
  // switch
  void GetPosition( CRect *rect );

private:

  void *mHandle;
};

// enum all elements

enum
{
#define CM(p1,p2,p3,p4,p5) p1,
#include __FILE__

  kNumSwitches
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CSwitch.h,v $
// Revision 1.5  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.4  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.3  2004/08/26 00:50:38  joffe
// buttonmode added
//
// Revision 1.2  2004/08/04 00:32:45  joffe
// some switch-btmaps now smaller, new backrounds, remote displays added,
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
