///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDisplay.h,v $
// $Revision: 1.6 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that supports displays for VstGui
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifndef CDISPLAY_H

enum
{
  kFtBig,   // small button for pages (normal & red)
  kFtSmall, // bigger version (normal & red)

  kNumFtTypes
};

enum
{
  kEdNo,    // no editor
  kEdYes,   // editor enabled

  kNumEdTypes
};

#endif


#ifdef CM   // ControlMacro defined

//                                |       Position        |dig|      | align |       |
//   ID                           |Top  Left  Height Width|its| font |  X  Y | Editor|

CM(kDisplaySoundNumber,              18, 280,   18,    28,  3, kFtBig,  3, 3, kEdYes )
CM(kDisplaySoundName,                18, 312,   18,    70, 16, kFtSmall,4, 8, kEdYes )

CM(kDisplayVersion,                  18, 312,   18,    70, 11, kFtSmall,4, 8, kEdYes )

//
// Resynator 1
//

CM(kDisplayR1CtxVal1,               212,  30,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR1CtxName1,              212,  58,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR1CtxVal2,               212, 255,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR1CtxName2,              212, 283,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR1CtxVal3,               328, 255,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR1CtxName3,              328, 283,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR1CtxVal4,               328,  30,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR1CtxName4,              328,  58,   18,    49,  8, kFtSmall,2, 7, kEdNo  )

CM(kDisplayR1Volume,                 92,  77,   18,    33,  3, kFtBig,  4, 2, kEdYes )
CM(kDisplayR1ModelNumber,            92, 183,   18,    28,  3, kFtBig,  3, 2, kEdYes )
CM(kDisplayR1ModelName,              92, 211,   18,    70, 11, kFtSmall,4, 7, kEdNo  )

CM(kDisplayR1AmpLfoDepth,           153,  34,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1AmpKeyTrack,           153,  85,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1VolumeVelocityDepth,   153, 136,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1ModelSizeKeyTrack,     153, 187,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1ModelSizeOffset,       153, 238,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1ModelVelocitySwitch,   153, 289,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR1Semi,                  382,  43,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1Cents,                 382,  94,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1PitchLfoDepth,         382, 243,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1PitchKeyTrack,         382, 294,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR1FreeADSR1PitchDepth,   460, 252,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1FreeADSR2PitchDepth,   460, 303,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR1CtxLfoDepth,            14,  13,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1CtxKeyTrack,            14,  64,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1CtxVelocityDepth,       14, 115,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR1CtxEnvDepth,            14, 166,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Resynator 2
//

CM(kDisplayR2CtxVal1,               212, 469,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR2CtxName1,              212, 497,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR2CtxVal2,               212, 694,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR2CtxName2,              212, 722,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR2CtxVal3,               328, 694,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR2CtxName3,              328, 722,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplayR2CtxVal4,               328, 469,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplayR2CtxName4,              328, 497,   18,    49,  8, kFtSmall,2, 7, kEdNo  )

CM(kDisplayR2Volume,                 92, 689,   18,    33,  3, kFtBig,  4, 2, kEdYes )
CM(kDisplayR2ModelNumber,            92, 520,   18,    28,  3, kFtBig,  3, 2, kEdYes )
CM(kDisplayR2ModelName,              92, 548,   18,    70, 11, kFtSmall,4, 7, kEdNo )

CM(kDisplayR2AmpLfoDepth,           153, 487,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2AmpKeyTrack,           153, 538,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2VolumeVelocityDepth,   153, 589,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2ModelSizeKeyTrack,     153, 640,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2ModelSizeOffset,       153, 691,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2ModelVelocitySwitch,   153, 742,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR2Semi,                  382, 482,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2Cents,                 382, 533,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2PitchLfoDepth,         382, 682,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2PitchKeyTrack,         382, 733,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR2FreeADSR1PitchDepth,   460, 691,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2FreeADSR2PitchDepth,   460, 742,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayR2CtxLfoDepth,            14,  13,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2CtxKeyTrack,            14,  64,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2CtxVelocityDepth,       14, 115,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayR2CtxEnvDepth,            14, 166,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Blender
//
CM(kDisplayBlenderType,             169, 351,   18,    98, 16, kFtSmall,4, 4, kEdNo  )
CM(kDisplayBlenderAmount,           303, 386,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayBlenderLfoDepth,         362, 386,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayBlenderFreeADSR1Depth,   416, 366,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayBlenderFreeADSR2Depth,   416, 406,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Shaper 1/2
//
CM(kDisplayShaper1ParamVeloDepth,   527, 119,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper1FreeVeloDepth,    611, 119,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper1FreeDepth,        611, 170,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayShaper2ParamVeloDepth,   527, 655,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper2FreeVeloDepth,    611, 655,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper2FreeDepth,        611, 605,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayShaper12CtxA,            611, 367,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper12CtxD,            611, 418,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper12CtxS,            611, 469,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper12CtxR,            611, 520,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Mod/LFO
//
CM(kDisplayLfoDepth,                136,  47,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayLfoRate,                 136,  98,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayLfoDelay,                136, 149,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// 
// Silver
//
CM(kDisplaySilverCtxVal1,           136, 250,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplaySilverCtxName1,          136, 278,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplaySilverCtxVal2,           136, 475,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplaySilverCtxName2,          136, 503,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplaySilverCtxVal3,           252, 475,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplaySilverCtxName3,          252, 503,   18,    49,  8, kFtSmall,2, 7, kEdNo  )
CM(kDisplaySilverCtxVal4,           252, 250,   18,    28,  3, kFtBig,  2, 2, kEdNo  )
CM(kDisplaySilverCtxName4,          252, 278,   18,    49,  8, kFtSmall,2, 7, kEdNo  )

CM(kDisplayFilterType,              311, 351,   18,    98, 16, kFtSmall,4, 4, kEdNo  )
CM(kDisplayFilterCutoff,            383, 361,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFilterResonance,         383, 412,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFilterLfoDepth,          441, 338,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFilterKeyTrack,          441, 389,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFilterVeloDepth,         441, 440,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Slicer
//
CM(kDisplaySlicerDepth,             136, 680,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplaySlicerRate,              136, 731,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Shaper 3
//

CM(kDisplayShaper3A,                612, 416,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper3D,                612, 467,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper3S,                612, 518,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper3R,                612, 569,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayShaper3Depth,            549,  83,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayShaper3VeloDepth,        549, 691,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Freq FX
//

// --- EQ/Compressor

CM(kDisplayFfxEQLowGain,             73,  75,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQLowFreq,             73, 126,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQLowSlope,            73, 177,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand1Gain,           73,  75,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand1Freq,           73, 126,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand1Q,              73, 177,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand2Gain,           73,  75,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand2Freq,           73, 126,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQBand2Q,              73, 177,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQHighGain,            73,  75,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQHighFreq,            73, 126,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxEQHighSlope,           73, 177,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxCRThreshold,           73,  75,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxCROutGain,             73, 126,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxCRReponsiveness,       73, 177,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Distortion
CM(kDisplayFfxDSInDrive,             90,  76,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxDSPreFilter,           90, 127,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxDSOutVolume,           90, 178,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Ring Modulator
CM(kDisplayFfxRMMix,                 90,  33,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMModFreq,             90,  84,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMSpeed,               90, 135,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMDepth,               90, 186,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMXoverDelay,          90,  58,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMXoverTime,           90, 109,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxRMXoverFeedbk,         90, 160,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Decimator
CM(kDisplayFfxDCMix,                 66,  58,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxDCSHFactor,            66, 109,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxDCPreFilter,           66, 160,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Sp_warp
CM(kDisplayFfxSWMix,                 37,  59,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxSWFrequency,           37, 110,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxSWTilt,                37, 161,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxSWDamping,             90,  59,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxSWSpeed,               90, 110,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayFfxSWDepth,               90, 161,   18,    28,  3, kFtBig,  1, 1, kEdYes )


//
// Time FX
//

// --- Stereo Spread
CM(kDisplayTfxSSChanDelay,           66,  85,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxSSFeedback,            66, 136,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- L/R Delay
CM(kDisplayTfxLRDMix,                66,  58,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxLRDTime,               66, 109,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxLRDFeedback,           66, 160,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Flanger
CM(kDisplayTfxFLMix,                 90,  33,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxFLFeedback,            90,  84,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxFLSpeed,               90, 135,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxFLDepth,               90, 186,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxFLStereoPhase,         90, 105,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Phaser
CM(kDisplayTfxPHMix,                 90,  33,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxPHFeedback,            90,  84,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxPHSpeed,               90, 135,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxPHDepth,               90, 186,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxPHStereoPhase,         90, 105,   18,    28,  3, kFtBig,  1, 1, kEdYes )

// --- Chorus
CM(kDisplayTfxCHMix,                 90,  33,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxCHFeedback,            90,  84,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxCHSpeed,               90, 135,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxCHDepth,               90, 186,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxCHStereoPhase,         90,  82,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayTfxCHPreDelay,            90, 133,   18,    28,  3, kFtBig,  1, 1, kEdYes )

//
// Remote
//

CM(kDisplayVoiceLimit,               94,  23,   18,    28,  3, kFtBig,  1, 1, kEdYes )

CM(kDisplayKnob1Select,             295,  68,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayKnob2Select,             216, 109,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayKnob3Select,             216, 593,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayKnob4Select,             295, 636,   18,    98, 18, kFtSmall,2, 4, kEdNo  )

CM(kDisplayDestAftertouch,          539,  29,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayDestModulation,          539, 158,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayDestBreath,              539, 287,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayDestCC03,                539, 416,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayDestFoot,                539, 545,   18,    98, 18, kFtSmall,2, 4, kEdNo  )
CM(kDisplayDestExpression,          539, 674,   18,    98, 18, kFtSmall,2, 4, kEdNo  )

CM(kDisplayDepthAftertouch,         604,  64,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayDepthModulation,         604, 193,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayDepthBreath,             604, 322,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayDepthCC03,               604, 451,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayDepthFoot,               604, 580,   18,    28,  3, kFtBig,  1, 1, kEdYes )
CM(kDisplayDepthExpression,         604, 709,   18,    28,  3, kFtBig,  1, 1, kEdYes )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CDISPLAY_H
#define CDISPLAY_H

#include "vstgui.h"

#define VNTF_MOUSE    1   // next parents mouse() comes from a display

class CDisplay
{
public:

  CDisplay(int inEnumedId);
  ~CDisplay();

  // SetFrame sets/attaches the display to a given Frame. 0 as inFrame
  // disables/detaches the display, but keeps all other settings. The
  // inParentView may give a view where its mouse() and notify() members
  // will be called by the display. The views notify() will receive an
  // according (char *)VNTF_xxx
  void SetFrame( CFrame *inFrame, CPoint ofs, CView *inParentView = 0 );

  // SetXXX sets the display-content. The text will be copied,
  void SetText( const char *inText );   // display text
  void SetInt(int val, bool bipolar);   // display int

private:

  void *mHandle;

};

// enum all elements

enum
{
#define CM(p1,p2,p3,p4,p5,p6,p7,p8,p9, p10) p1,
#include __FILE__

  kNumDisplays
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDisplay.h,v $
// Revision 1.6  2004/11/11 03:12:08  joffe
// minor bugfixes
//
// Revision 1.5  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.4  2004/10/18 06:41:33  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.3  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.2  2004/08/04 00:32:45  joffe
// some switch-btmaps now smaller, new backrounds, remote displays added,
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
