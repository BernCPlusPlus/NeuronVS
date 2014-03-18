///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CScroller.h,v $
// $Revision: 1.2 $
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

#ifndef CSCROLLER_H

enum
{
  kScTpVS,    // vertical small scroller
  kScTpHB,    // horizontal big scroller

  kNumScTypes
};

#endif  // XXXX_H


#ifdef CM   // ControlMacro defined

//                                 |Position|          |                |
//   ID                            |Top Left|  Type    |   Display-ID   |

//
// Resynator 1
//

CM(kScrollerR1AmpLfoDepth,          148,  25,  kScTpVS,  kDisplayR1AmpLfoDepth )
CM(kScrollerR1AmpKeyTrack,          148,  76,  kScTpVS,  kDisplayR1AmpKeyTrack )
CM(kScrollerR1VolumeVelocityDepth,  148, 127,  kScTpVS,  kDisplayR1VolumeVelocityDepth )
CM(kScrollerR1ModelSizeKeyTrack,    148, 178,  kScTpVS,  kDisplayR1ModelSizeKeyTrack )
CM(kScrollerR1ModelSizeOffset,      148, 229,  kScTpVS,  kDisplayR1ModelSizeOffset )
CM(kScrollerR1ModelVelocitySwitch,  148, 280,  kScTpVS,  kDisplayR1ModelVelocitySwitch )

CM(kScrollerR1Semi,                 377,  34,  kScTpVS,  kDisplayR1Semi )
CM(kScrollerR1Cents,                377,  85,  kScTpVS,  kDisplayR1Cents )
CM(kScrollerR1PitchLfoDepth,        377, 234,  kScTpVS,  kDisplayR1PitchLfoDepth )
CM(kScrollerR1PitchKeyTrack,        377, 285,  kScTpVS,  kDisplayR1PitchKeyTrack )

CM(kScrollerR1FreeADSR1PitchDepth,  455, 243,  kScTpVS,  kDisplayR1FreeADSR1PitchDepth )
CM(kScrollerR1FreeADSR2PitchDepth,  455, 294,  kScTpVS,  kDisplayR1FreeADSR2PitchDepth )

CM(kScrollerR1CtxLfoDepth,            9,   4,  kScTpVS,  kDisplayR1CtxLfoDepth )
CM(kScrollerR1CtxKeyTrack,            9,  55,  kScTpVS,  kDisplayR1CtxKeyTrack )
CM(kScrollerR1CtxVelDepth,            9, 106,  kScTpVS,  kDisplayR1CtxVelocityDepth )
CM(kScrollerR1CtxEnvDepth,            9, 157,  kScTpVS,  kDisplayR1CtxEnvDepth )


//
// Resynator 2
//

CM(kScrollerR2AmpLfoDepth,          148, 478,  kScTpVS,  kDisplayR2AmpLfoDepth )
CM(kScrollerR2AmpKeyTrack,          148, 529,  kScTpVS,  kDisplayR2AmpKeyTrack )
CM(kScrollerR2VolumeVelocityDepth,  148, 580,  kScTpVS,  kDisplayR2VolumeVelocityDepth )
CM(kScrollerR2ModelSizeKeyTrack,    148, 631,  kScTpVS,  kDisplayR2ModelSizeKeyTrack )
CM(kScrollerR2ModelSizeOffset,      148, 682,  kScTpVS,  kDisplayR2ModelSizeOffset )
CM(kScrollerR2ModelVelocitySwitch,  148, 733,  kScTpVS,  kDisplayR2ModelVelocitySwitch )

CM(kScrollerR2Semi,                 377, 473,  kScTpVS,  kDisplayR2Semi )
CM(kScrollerR2Cents,                377, 524,  kScTpVS,  kDisplayR2Cents )
CM(kScrollerR2PitchLfoDepth,        377, 673,  kScTpVS,  kDisplayR2PitchLfoDepth )
CM(kScrollerR2PitchKeyTrack,        377, 724,  kScTpVS,  kDisplayR2PitchKeyTrack )

CM(kScrollerR2FreeADSR1PitchDepth,  455, 682,  kScTpVS,  kDisplayR2FreeADSR1PitchDepth )
CM(kScrollerR2FreeADSR2PitchDepth,  455, 733,  kScTpVS,  kDisplayR2FreeADSR2PitchDepth )

CM(kScrollerR2CtxLfoDepth,            9,   4,  kScTpVS,  kDisplayR2CtxLfoDepth )
CM(kScrollerR2CtxKeyTrack,            9,  55,  kScTpVS,  kDisplayR2CtxKeyTrack )
CM(kScrollerR2CtxVelDepth,            9, 106,  kScTpVS,  kDisplayR2CtxVelocityDepth )
CM(kScrollerR2CtxEnvDepth,            9, 157,  kScTpVS,  kDisplayR2CtxEnvDepth )

CM(kScrollerShaper12CtxA,           606, 358,  kScTpVS,  kDisplayShaper12CtxA )
CM(kScrollerShaper12CtxD,           606, 409,  kScTpVS,  kDisplayShaper12CtxD )
CM(kScrollerShaper12CtxS,           606, 460,  kScTpVS,  kDisplayShaper12CtxS )
CM(kScrollerShaper12CtxR,           606, 511,  kScTpVS,  kDisplayShaper12CtxR )

//
// Blender
//
CM(kScrollerBlenderAmount,          267, 366,  kScTpHB,  kDisplayBlenderAmount )
CM(kScrollerBlenderLfoDepth,        357, 377,  kScTpVS,  kDisplayBlenderLfoDepth )
CM(kScrollerBlenderFreeADSR1Depth,  411, 357,  kScTpVS,  kDisplayBlenderFreeADSR1Depth )
CM(kScrollerBlenderFreeADSR2Depth,  411, 438,  kScTpVS,  kDisplayBlenderFreeADSR2Depth )

//
// Shaper 1/2
//
CM(kScrollerShaper1ParamVeloDepth,  522, 151,  kScTpVS,  kDisplayShaper1ParamVeloDepth )
CM(kScrollerShaper1FreeVeloDepth,   606, 151,  kScTpVS,  kDisplayShaper1FreeVeloDepth )
CM(kScrollerShaper1FreeDepth,       606, 202,  kScTpVS,  kDisplayShaper1FreeDepth )

CM(kScrollerShaper2ParamVeloDepth,  522, 646,  kScTpVS,  kDisplayShaper2ParamVeloDepth )
CM(kScrollerShaper2FreeVeloDepth,   606, 646,  kScTpVS,  kDisplayShaper2FreeVeloDepth )
CM(kScrollerShaper2FreeDepth,       606, 595,  kScTpVS,  kDisplayShaper2FreeDepth )

//
// Mod/LFO
//
CM(kScrollerLfoDepth,               131,  38,  kScTpVS,  kDisplayLfoDepth )
CM(kScrollerLfoRate,                131,  89,  kScTpVS,  kDisplayLfoRate )
CM(kScrollerLfoDelay,               131, 140,  kScTpVS,  kDisplayLfoDelay )

// 
// Silver Filter
//
CM(kScrollerFilterCutoff,           378, 352,  kScTpVS,  kDisplayFilterCutoff )
CM(kScrollerFilterResonance,        378, 403,  kScTpVS,  kDisplayFilterResonance )
CM(kScrollerFilterLfoDepth,         436, 329,  kScTpVS,  kDisplayFilterLfoDepth )
CM(kScrollerFilterKeyTrack,         436, 380,  kScTpVS,  kDisplayFilterKeyTrack )
CM(kScrollerFilterVeloDepth,        436, 431,  kScTpVS,  kDisplayFilterVeloDepth )

//
// Freq FX
//

// --- EQ/Compressor

CM(kScrollerFfxEQLowGain,            68,  66,  kScTpVS,  kDisplayFfxEQLowGain )
CM(kScrollerFfxEQLowFreq,            68, 117,  kScTpVS,  kDisplayFfxEQLowFreq )
CM(kScrollerFfxEQLowSlope,           68, 168,  kScTpVS,  kDisplayFfxEQLowSlope )
CM(kScrollerFfxEQBand1Gain,          68,  66,  kScTpVS,  kDisplayFfxEQBand1Gain )
CM(kScrollerFfxEQBand1Freq,          68, 117,  kScTpVS,  kDisplayFfxEQBand1Freq )
CM(kScrollerFfxEQBand1Q,             68, 168,  kScTpVS,  kDisplayFfxEQBand1Q )
CM(kScrollerFfxEQBand2Gain,          68,  66,  kScTpVS,  kDisplayFfxEQBand2Gain )
CM(kScrollerFfxEQBand2Freq,          68, 117,  kScTpVS,  kDisplayFfxEQBand2Freq )
CM(kScrollerFfxEQBand2Q,             68, 168,  kScTpVS,  kDisplayFfxEQBand2Q )
CM(kScrollerFfxEQHighGain,           68,  66,  kScTpVS,  kDisplayFfxEQHighGain )
CM(kScrollerFfxEQHighFreq,           68, 117,  kScTpVS,  kDisplayFfxEQHighFreq )
CM(kScrollerFfxEQHighSlope,          68, 168,  kScTpVS,  kDisplayFfxEQHighSlope )
CM(kScrollerFfxCRThreshold,          68,  66,  kScTpVS,  kDisplayFfxCRThreshold )
CM(kScrollerFfxCROutGain,            68, 117,  kScTpVS,  kDisplayFfxCROutGain )
CM(kScrollerFfxCRReponsiveness,      68, 168,  kScTpVS,  kDisplayFfxCRReponsiveness )

// --- Distortion
CM(kScrollerFfxDSInDrive,            85,  67,  kScTpVS,  kDisplayFfxDSInDrive )
CM(kScrollerFfxDSPreFilter,          85, 118,  kScTpVS,  kDisplayFfxDSPreFilter )
CM(kScrollerFfxDSOutVolume,          85, 169,  kScTpVS,  kDisplayFfxDSOutVolume )

// --- Ring Modulator
CM(kScrollerFfxRMMix,                85,  24,  kScTpVS,  kDisplayFfxRMMix )
CM(kScrollerFfxRMModFreq,            85,  75,  kScTpVS,  kDisplayFfxRMModFreq )
CM(kScrollerFfxRMSpeed,              85, 126,  kScTpVS,  kDisplayFfxRMSpeed )
CM(kScrollerFfxRMDepth,              85, 177,  kScTpVS,  kDisplayFfxRMDepth )
CM(kScrollerFfxRMXoverDelay,         85,  49,  kScTpVS,  kDisplayFfxRMXoverDelay )
CM(kScrollerFfxRMXoverTime,          85, 100,  kScTpVS,  kDisplayFfxRMXoverTime )
CM(kScrollerFfxRMXoverFeedbk,        85, 151,  kScTpVS,  kDisplayFfxRMXoverFeedbk )

// --- Decimator
CM(kScrollerFfxDCMix,                61,  49,  kScTpVS,  kDisplayFfxDCMix )
CM(kScrollerFfxDCSHFactor,           61, 100,  kScTpVS,  kDisplayFfxDCSHFactor )
CM(kScrollerFfxDCPreFilter,          61, 151,  kScTpVS,  kDisplayFfxDCPreFilter )

// --- Sp_warp
CM(kScrollerFfxSWMix,                32,  50,  kScTpVS,  kDisplayFfxSWMix )
CM(kScrollerFfxSWFrequency,          32, 101,  kScTpVS,  kDisplayFfxSWFrequency )
CM(kScrollerFfxSWTilt,               32, 152,  kScTpVS,  kDisplayFfxSWTilt )
CM(kScrollerFfxSWDamping,            85,  50,  kScTpVS,  kDisplayFfxSWDamping )
CM(kScrollerFfxSWSpeed,              85, 101,  kScTpVS,  kDisplayFfxSWSpeed )
CM(kScrollerFfxSWDepth,              85, 152,  kScTpVS,  kDisplayFfxSWDepth )


//
// Time FX
//

// --- Stereo Spread
CM(kScrollerTfxSSChanDelay,          61,  76,  kScTpVS,  kDisplayTfxSSChanDelay )
CM(kScrollerTfxSSFeedback,           61, 127,  kScTpVS,  kDisplayTfxSSFeedback )

// --- L/R Delay
CM(kScrollerTfxLRDMix,               61,  49,  kScTpVS,  kDisplayTfxLRDMix )
CM(kScrollerTfxLRDTime,              61, 100,  kScTpVS,  kDisplayTfxLRDTime )
CM(kScrollerTfxLRDFeedback,          61, 151,  kScTpVS,  kDisplayTfxLRDFeedback )

// --- Flanger
CM(kScrollerTfxFLMix,                85,  24,  kScTpVS,  kDisplayTfxFLMix )
CM(kScrollerTfxFLFeedback,           85,  75,  kScTpVS,  kDisplayTfxFLFeedback )
CM(kScrollerTfxFLSpeed,              85, 126,  kScTpVS,  kDisplayTfxFLSpeed )
CM(kScrollerTfxFLDepth,              85, 177,  kScTpVS,  kDisplayTfxFLDepth )
CM(kScrollerTfxFLStereoPhase,        85,  96,  kScTpVS,  kDisplayTfxFLStereoPhase )

// --- Phaser
CM(kScrollerTfxPHMix,                85,  24,  kScTpVS,  kDisplayTfxPHMix )
CM(kScrollerTfxPHFeedback,           85,  75,  kScTpVS,  kDisplayTfxPHFeedback )
CM(kScrollerTfxPHSpeed,              85, 126,  kScTpVS,  kDisplayTfxPHSpeed )
CM(kScrollerTfxPHDepth,              85, 177,  kScTpVS,  kDisplayTfxPHDepth )
CM(kScrollerTfxPHStereoPhase,        85,  96,  kScTpVS,  kDisplayTfxPHStereoPhase )

// --- Chorus
CM(kScrollerTfxCHMix,                85,  24,  kScTpVS,  kDisplayTfxCHMix )
CM(kScrollerTfxCHFeedback,           85,  75,  kScTpVS,  kDisplayTfxCHFeedback )
CM(kScrollerTfxCHSpeed,              85, 126,  kScTpVS,  kDisplayTfxCHSpeed )
CM(kScrollerTfxCHDepth,              85, 177,  kScTpVS,  kDisplayTfxCHDepth )
CM(kScrollerTfxCHStereoPhase,        85,  73,  kScTpVS,  kDisplayTfxCHStereoPhase )
CM(kScrollerTfxCHPreDelay,           85, 124,  kScTpVS,  kDisplayTfxCHPreDelay )

//
// Slicer
//
CM(kScrollerSlicerDepth,            131, 671,  kScTpVS,  kDisplaySlicerDepth )
CM(kScrollerSlicerRate,             131, 722,  kScTpVS,  kDisplaySlicerRate )

//
// Shaper 3
//

CM(kScrollerShaper3Depth,           544,  74,  kScTpVS,  kDisplayShaper3Depth )
CM(kScrollerShaper3VeloDepth,       544, 723,  kScTpVS,  kDisplayShaper3VeloDepth )

CM(kScrollerShaper3A,               607, 407,  kScTpVS,  kDisplayShaper3A )
CM(kScrollerShaper3D,               607, 458,  kScTpVS,  kDisplayShaper3D )
CM(kScrollerShaper3S,               607, 509,  kScTpVS,  kDisplayShaper3S )
CM(kScrollerShaper3R,               607, 560,  kScTpVS,  kDisplayShaper3R )

//
// Remote
//

CM(kScrollerVoiceLimit,              89,  55,  kScTpVS,  kDisplayVoiceLimit )
CM(kScrollerDepthAftertouch,        597,  55,  kScTpVS,  kDisplayDepthAftertouch )
CM(kScrollerDepthModulation,        597, 184,  kScTpVS,  kDisplayDepthModulation )
CM(kScrollerDepthBreath,            597, 313,  kScTpVS,  kDisplayDepthBreath )
CM(kScrollerDepthCC03,              597, 442,  kScTpVS,  kDisplayDepthCC03 )
CM(kScrollerDepthFoot,              597, 571,  kScTpVS,  kDisplayDepthFoot )
CM(kScrollerDepthExpression,        597, 700,  kScTpVS,  kDisplayDepthExpression )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CSCROLLER_H
#define CSCROLLER_H

#include "vstgui.h"
#include "CParam.h"
#include "CDisplay.h"


class CScroller
{
public:

  CScroller(int inEnumedId);
  ~CScroller();

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
#define CM(p1,p2,p3,p4,p5) p1,
#include __FILE__

  kNumScrollers
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CScroller.h,v $
// Revision 1.2  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
