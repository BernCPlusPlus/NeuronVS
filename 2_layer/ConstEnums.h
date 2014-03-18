///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ConstEnums.h,v $
// $Revision: 1.4 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This defines loads of constants to make table-definitions more readable
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CONSTENUMS_H
#define CONSTENUMS_H


enum // stick mode
{
  sm_jump=0,
  sm_snap,
  sm_relative
};

enum // velocity curves
{
  vc_log2=0, // Log2 first in the list. Makes sense, when you look at the curves.
  vc_log1,
  vc_linear,
  vc_exp1,
  vc_exp2,
  vc_fix_32,
  vc_fix_64,
  vc_fix_96,
  vc_fix_127,
  vc_num
};

enum // stick record start
{
  srs_stick=0,
  srs_key
};

enum // resy parameter reset mode
{
  rprm_no=0,
  rprm_ask,
  rprm_yes
};

enum // shut down mode
{
  sdm_ask=0,
  sdm_quick
};

enum // resynator types
{
  rt_sphere = 0,
  rt_scape
};

enum // stick playback
{
  stp_off = 0, // only availabe for surround stick playback
  stp_oneShot,
  stp_repeat
};

enum // shaper 1/2 status
{
  s12_resy=0, // was "free" before OS 2.0
  s12_amp,
  s12_free,   // was "resy" before OS 2.0
  s2_resy,
  s2_amp,
  s2_free
};

enum // shaper 3 status
{
  s3_mfxMix=0,
  s3_silver
};

enum // free continuous controller options
{
  // Never change this order here, as these values are stored with the sound!
  // To change the order the destinations appear in the list, change the order
  // of the calls to ???() in ??? (TODO).
  cc_none = 3000,

  cc_LFODepth,
  cc_LFORate,
  cc_LFODelay,

  cc_BlenderAmount,

  cc_SlicerDepth,
  cc_SlicerRate,

  cc_FilterFreq,
  cc_FilterReso,

  cc_R1L1Scape1,
  cc_R1L1Scape2,
  cc_R1L1Sphere1,
  cc_R1L1Sphere2,
  cc_R1L2Scape1,
  cc_R1L2Scape2,
  cc_R1L2Sphere1,
  cc_R1L2Sphere2,
  cc_R1L3Scape1,
  cc_R1L3Scape2,
  cc_R1L3Sphere1,
  cc_R1L3Sphere2,

  cc_R2L1Scape1,
  cc_R2L1Scape2,
  cc_R2L1Sphere1,
  cc_R2L1Sphere2,
  cc_R2L2Scape1,
  cc_R2L2Scape2,
  cc_R2L2Sphere1,
  cc_R2L2Sphere2,
  cc_R2L3Scape1,
  cc_R2L3Scape2,
  cc_R2L3Sphere1,
  cc_R2L3Sphere2,

  // Freq FX
  // --- Distortion
  cc_DS_InGain,
  cc_DS_Prefilter,
  cc_DS_OutGain,
  // --- Ring Modulator
  cc_RM_Mix,
  cc_RM_Speed,
  cc_RM_Depth,
  cc_RM_ModFreq,
  cc_RM_XoverDelay,
  cc_RM_XoverTime,
  cc_RM_XDlFeedback,
  // --- Decimator
  cc_DC_Mix,
  cc_DC_SHFactor,
  cc_DC_PreFilterCutoff,
  // ---Sp-Warp
  cc_SW_Mix,
  cc_SW_Frequency,
  cc_SW_Tilt,
  cc_SW_Damping,
  cc_SW_Speed,
  cc_SW_Depth,

  // Time FX
  // --- Stereo Spread
  cc_SS_ChanDelay,
  cc_SS_Feedback,
  // --- L/R Delay
  cc_LRD_Mix,
  cc_LRD_Time,
  cc_LRD_Feedback,
  // --- Flanger
  cc_FL_Mix,
  cc_FL_Depth,
  cc_FL_Speed,
  cc_FL_Feedback,
  cc_FL_StereoPhase,
  // --- Phaser
  cc_PH_Mix,
  cc_PH_Depth,
  cc_PH_Speed,
  cc_PH_Feedback,
  cc_PH_StereoPhase,
  // --- Chorus
  cc_CH_Mix,
  cc_CH_Depth,
  cc_CH_Speed,
  cc_CH_Feedback,
  cc_CH_StereoPhase,
  cc_CH_Predelay,

  //
  // Shapers
  //

  cc_R1ResEnvA,
  cc_R1ResEnvD,
  cc_R1ResEnvS,
  cc_R1ResEnvR,

  cc_R1AmpEnvA,
  cc_R1AmpEnvD,
  cc_R1AmpEnvS,
  cc_R1AmpEnvR,

  cc_R1FreeEnvA,
  cc_R1FreeEnvD,
  cc_R1FreeEnvS,
  cc_R1FreeEnvR,
  cc_R1FreeEnvDepth,

  cc_R2ResEnvA,
  cc_R2ResEnvD,
  cc_R2ResEnvS,
  cc_R2ResEnvR,

  cc_R2AmpEnvA,
  cc_R2AmpEnvD,
  cc_R2AmpEnvS,
  cc_R2AmpEnvR,

  cc_R2FreeEnvA,
  cc_R2FreeEnvD,
  cc_R2FreeEnvS,
  cc_R2FreeEnvR,
  cc_R2FreeEnvDepth,

  cc_FreeEnvLevel1,
  cc_FreeEnvTime1,
  cc_FreeEnvLevel2,
  cc_FreeEnvTime2,
  cc_FreeEnvLevel3,
  cc_FreeEnvTime3,
  cc_FreeEnvLevel4,
  cc_FreeEnvTime4,
  cc_TLFreeEnvDepth,

  cc_FilterEnvA,
  cc_FilterEnvD,
  cc_FilterEnvS,
  cc_FilterEnvR,
  cc_FilterEnvDepth,

  cc_SoundPan,

  cc_EQ_LowShelfGain,
  cc_EQ_LowShelfFreq,
  cc_EQ_LowShelfSlope,
  cc_EQ_Band1Gain,
  cc_EQ_Band1Freq,
  cc_EQ_Band1Q,
  cc_EQ_Band2Gain,
  cc_EQ_Band2Freq,
  cc_EQ_Band2Q,
  cc_EQ_HighShelfGain,
  cc_EQ_HighShelfFreq,
  cc_EQ_HighShelfSlope,
  cc_CR_Threshold,
  cc_CR_OutGain,
  cc_CR_Responsiveness,

  cc_R1Volume,
  cc_R2Volume,


  cc_num


  /* The destinations below are not available yet.

  cc_R1L1Scape1LfoDepth,
  cc_R1L1Scape2LfoDepth,
  cc_R1L1Sphere1LfoDepth,
  cc_R1L1Sphere2LfoDepth,
  cc_R1L2Scape1LfoDepth,
  cc_R1L2Scape2LfoDepth,
  cc_R1L2Sphere1LfoDepth,
  cc_R1L2Sphere2LfoDepth,
  cc_R1L3Scape1LfoDepth,
  cc_R1L3Scape2LfoDepth,
  cc_R1L3Sphere1LfoDepth,
  cc_R1L3Sphere2LfoDepth,

  cc_R1PitchLfoDepth,
  cc_R1AmpLfoDepth,


  cc_R1L1Scape1EnvDepth,
  cc_R1L1Scape2EnvDepth,
  cc_R1L1Sphere1EnvDepth,
  cc_R1L1Sphere2EnvDepth,
  cc_R1L2Scape1EnvDepth,
  cc_R1L2Scape2EnvDepth,
  cc_R1L2Sphere1EnvDepth,
  cc_R1L2Sphere2EnvDepth,
  cc_R1L3Scape1EnvDepth,
  cc_R1L3Scape2EnvDepth,
  cc_R1L3Sphere1EnvDepth,
  cc_R1L3Sphere2EnvDepth,



  cc_R2L1Scape1LfoDepth,
  cc_R2L1Scape2LfoDepth,
  cc_R2L1Sphere1LfoDepth,
  cc_R2L1Sphere2LfoDepth,
  cc_R2L2Scape1LfoDepth,
  cc_R2L2Scape2LfoDepth,
  cc_R2L2Sphere1LfoDepth,
  cc_R2L2Sphere2LfoDepth,
  cc_R2L3Scape1LfoDepth,
  cc_R2L3Scape2LfoDepth,
  cc_R2L3Sphere1LfoDepth,
  cc_R2L3Sphere2LfoDepth,

  cc_R2L1Scape1EnvDepth,
  cc_R2L1Scape2EnvDepth,
  cc_R2L1Sphere1EnvDepth,
  cc_R2L1Sphere2EnvDepth,
  cc_R2L2Scape1EnvDepth,
  cc_R2L2Scape2EnvDepth,
  cc_R2L2Sphere1EnvDepth,
  cc_R2L2Sphere2EnvDepth,
  cc_R2L3Scape1EnvDepth,
  cc_R2L3Scape2EnvDepth,
  cc_R2L3Sphere1EnvDepth,
  cc_R2L3Sphere2EnvDepth,


  cc_R2PitchLfoDepth,
  cc_R2AmpLfoDepth,

*/

};


enum // controller-destinations for neuron-vs
{
  cvd_first=0,
  cvd_none = cvd_first-1,

  cvd_R1Volume,
  cvd_R1Detune,
  cvd_R1L1Scape1,
  cvd_R1L1Scape2,
  cvd_R1L1Sphere1,
  cvd_R1L1Sphere2,
  cvd_R1L2Scape1,
  cvd_R1L2Scape2,
  cvd_R1L2Sphere1,
  cvd_R1L2Sphere2,
  cvd_R1L3Scape1,
  cvd_R1L3Scape2,
  cvd_R1L3Sphere1,
  cvd_R1L3Sphere2,

  cvd_R2Volume,
  cvd_R2Detune,
  cvd_R2L1Scape1,
  cvd_R2L1Scape2,
  cvd_R2L1Sphere1,
  cvd_R2L1Sphere2,
  cvd_R2L2Scape1,
  cvd_R2L2Scape2,
  cvd_R2L2Sphere1,
  cvd_R2L2Sphere2,
  cvd_R2L3Scape1,
  cvd_R2L3Scape2,
  cvd_R2L3Sphere1,
  cvd_R2L3Sphere2,

  cvd_Res1EnvA,
  cvd_Res1EnvD,
  cvd_Res1EnvS,
  cvd_Res1EnvR,
  cvd_Amp1EnvA,
  cvd_Amp1EnvD,
  cvd_Amp1EnvS,
  cvd_Amp1EnvR,
  cvd_Free1EnvA,
  cvd_Free1EnvD,
  cvd_Free1EnvS,
  cvd_Free1EnvR,

  cvd_Res2EnvA,
  cvd_Res2EnvD,
  cvd_Res2EnvS,
  cvd_Res2EnvR,
  cvd_Amp2EnvA,
  cvd_Amp2EnvD,
  cvd_Amp2EnvS,
  cvd_Amp2EnvR,
  cvd_Free2EnvA,
  cvd_Free2EnvD,
  cvd_Free2EnvS,
  cvd_Free2EnvR,

  cvd_FilterEnvA,
  cvd_FilterEnvD,
  cvd_FilterEnvS,
  cvd_FilterEnvR,

  cvd_BlenderAmount,

  cvd_SlicerDepth,
  cvd_SlicerRate,

  cvd_LFODepth,
  cvd_LFORate,

  cvd_FilterFreq,
  cvd_FilterReso,

  cvd_num,
  cvd_last = cvd_num-1
};


enum // controller-sources for neuron-vs
{
  cvs_first=0,
  cvs_none = cvs_first-1,

  cvs_Aftertouch,
  cvs_Modulation,
  cvs_Breath,
  cvs_CC03,
  cvs_Foot,
  cvs_Expression,

  cvs_num,
  cvs_last = cvs_num-1
};


enum // options for free switch pedal
{
  fsw_none=0,
  fsw_lfoOnOff,
  fsw_r1OnOff,
  fsw_r1ParaLevel,
  fsw_r1Contour,
  fsw_r1Octave,
  fsw_r1ScapeSphere,
  fsw_r2OnOff,
  fsw_r2ParaLevel,
  fsw_r2Contour,
  fsw_r2Octave,
  fsw_r2ScapeSphere,
  fsw_shaper12Status,
  fsw_slicer,
  fsw_Up,
  fsw_Down,
  fsw_silverOnOff,
  fsw_silverParaLevel,
  fsw_silverContour,
  fsw_silverSurround,
  fsw_silverFilter,
  fsw_silverFreqFX,
  fsw_silverTimeFX,
  fsw_shaper3Status,
  fsw_mfxOnOff,
  fsw_mfxDelay,
  fsw_mfxReverb,
  fsw_num
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ConstEnums.h,v $
// Revision 1.4  2004/11/11 03:19:33  joffe
// shaper-resy select added
//
// Revision 1.3  2004/11/02 13:08:17  joffe
// modulation-matrix added
//
// Revision 1.2  2004/10/29 01:55:13  joffe
// controller-destinations added
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
