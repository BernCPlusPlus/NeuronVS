///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SoundParams.h,v $
// $Revision: 1.9 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef P   // parameter-macro defined
// name                         min       max      default    quant

// Soundformat version
P(SoundVersionMajor,             0,     999999,      2,         1)
P(SoundVersionMinor,             0,     999999,      0,         1)
P(SoundVersionBuild,             0,     999999,      0,         1)


//
// Sound Level General
//

P(SoundPan,                     -64,       63,       0,         1)
P(SoundPanKeyTrack,             -64,       63,       0,         1)

P(SoundNumVoices,                 1,       32,       4,         1)

P(SoundNameC00,                  32,      122,      'I',        1)
P(SoundNameC01,                  32,      122,      'n',        1)
P(SoundNameC02,                  32,      122,      'i',        1)
P(SoundNameC03,                  32,      122,      't',        1)
P(SoundNameC04,                  32,      122,      'S',        1)
P(SoundNameC05,                  32,      122,      'o',        1)
P(SoundNameC06,                  32,      122,      'u',        1)
P(SoundNameC07,                  32,      122,      'n',        1)
P(SoundNameC08,                  32,      122,      'd',        1)
P(SoundNameC09,                  32,      122,      ' ',        1)
P(SoundNameC10,                  32,      122,      ' ',        1)
P(SoundNameC11,                  32,      122,      ' ',        1)
P(SoundNameC12,                  32,      122,      ' ',        1)
P(SoundNameC13,                  32,      122,      ' ',        1)
P(SoundNameC14,                  32,      122,      ' ',        1)
P(SoundNameC15,                  32,      122,      ' ',        1)



/////////////////////////////////////////////////////////////////////////////
//
// -- Resynator 1
//
/////////////////////////////////////////////////////////////////////////////

// name                         min       max      default    quant

// -- Resynator 1 Model Index (Need to load model after copying, if the index changes)
// TODO: define model index max
// NOTE: German spelling "Modell" as in sound files. 
P(R1ModellIndex,                  0,      511,       511,       1)

// -- Resynator 1 General
P(R1Switch,                       0,        1,         1,       1)
P(R1Type,                     rt_sphere, rt_scape,  rt_scape,   1)
P(R1ParamLevel,                   0,        2,         0,       1) // 0 = Level 1 etc.
P(R1SelectStickPar,               0,        1,         0,       1) // 0 = Parameter 1/3, 1 = Parameter 2/4.

P(R1Volume,                       0,      127,       100,       1)
P(R1AmpLfoDepth,                -64,       63,         0,       1)
P(R1AmpKeyTrack,                -64,       63,         0,       1)
P(R1VolumeVelocityDepth,        -64,       63,        63,       1)

P(R1ModelSizeKeyTrack,          -64,       63,         0,       1)
P(R1ModelSizeOffset,            -64,       63,         0,       1)

P(R1Octave,                       0,        3,         2,       1) // 0 = -2, 1 = -1, 2 = 0, 3 = +1
P(R1Semi,                       -24,       24,         0,       1)
P(R1Cents,                      -99,       99,         0,       1)
P(R1PitchLfoDepth,              -64,       63,         0,       1)
P(R1PitchKeyTrack,              -64,       63,        63,       1)
P(R1FreeADSR1PitchDepth,        -64,       63,         0,       1)
P(R1FreeADSR2PitchDepth,        -64,       63,         0,       1)
P(R1Free4L4TPitchDepth,           0,      127,         0,       1)

P(R1ModelVelocitySwitch,          1,      127,        64,       1)



// -- Resynator 1 Model Parameters Level 1

P(R1L1Sphere1Value,               0,      127,        64,       1)
P(R1L1Sphere2Value,               0,      127,        64,       1)
P(R1L1ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R1L1Sphere1KeyTrack,          -64,       63,         0,       1)
P(R1L1Sphere2KeyTrack,          -64,       63,         0,       1)
P(R1L1Sphere1LfoDepth,          -64,       63,         0,       1)
P(R1L1Sphere2LfoDepth,          -64,       63,         0,       1)
P(R1L1Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R1L1Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R1L1SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R1L1Scape1Value,                0,      127,        64,       1)
P(R1L1Scape2Value,                0,      127,        64,       1)
P(R1L1ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R1L1Scape1KeyTrack,           -64,       63,         0,       1)
P(R1L1Scape2KeyTrack,           -64,       63,         0,       1)
P(R1L1Scape1LfoDepth,           -64,       63,         0,       1)
P(R1L1Scape2LfoDepth,           -64,       63,         0,       1)
P(R1L1Scape1VelocityDepth,      -64,       63,         0,       1)
P(R1L1Scape2VelocityDepth,      -64,       63,         0,       1)
P(R1L1ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)


// -- Resynator 1 Model Parameters Level 2

P(R1L2Sphere1Value,               0,      127,        64,       1)
P(R1L2Sphere2Value,               0,      127,        64,       1)
P(R1L2ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R1L2Sphere1KeyTrack,          -64,       63,         0,       1)
P(R1L2Sphere2KeyTrack,          -64,       63,         0,       1)
P(R1L2Sphere1LfoDepth,          -64,       63,         0,       1)
P(R1L2Sphere2LfoDepth,          -64,       63,         0,       1)
P(R1L2Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R1L2Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R1L2SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R1L2Scape1Value,                0,      127,        64,       1)
P(R1L2Scape2Value,                0,      127,        64,       1)
P(R1L2ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R1L2Scape1KeyTrack,           -64,       63,         0,       1)
P(R1L2Scape2KeyTrack,           -64,       63,         0,       1)
P(R1L2Scape1LfoDepth,           -64,       63,         0,       1)
P(R1L2Scape2LfoDepth,           -64,       63,         0,       1)
P(R1L2Scape1VelocityDepth,      -64,       63,         0,       1)
P(R1L2Scape2VelocityDepth,      -64,       63,         0,       1)
P(R1L2ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)


// -- Resynator 1 Model Parameters Level 3

P(R1L3Sphere1Value,               0,      127,        64,       1)
P(R1L3Sphere2Value,               0,      127,        64,       1)
P(R1L3ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R1L3Sphere1KeyTrack,          -64,       63,         0,       1)
P(R1L3Sphere2KeyTrack,          -64,       63,         0,       1)
P(R1L3Sphere1LfoDepth,          -64,       63,         0,       1)
P(R1L3Sphere2LfoDepth,          -64,       63,         0,       1)
P(R1L3Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R1L3Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R1L3SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R1L3Scape1Value,                0,      127,        64,       1)
P(R1L3Scape2Value,                0,      127,        64,       1)
P(R1L3ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R1L3Scape1KeyTrack,           -64,       63,         0,       1)
P(R1L3Scape2KeyTrack,           -64,       63,         0,       1)
P(R1L3Scape1LfoDepth,           -64,       63,         0,       1)
P(R1L3Scape2LfoDepth,           -64,       63,         0,       1)
P(R1L3Scape1VelocityDepth,      -64,       63,         0,       1)
P(R1L3Scape2VelocityDepth,      -64,       63,         0,       1)
P(R1L3ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)


/////////////////////////////////////////////////////////////////////////////
//
// -- Resynator 2
//
/////////////////////////////////////////////////////////////////////////////

// name                         min       max      default    quant

// -- Resynator 2 Model Index (Need to load model after copying, if the index changes)
// TODO: define model index max
// NOTE: German spelling "Modell" as in sound files.
P(R2ModellIndex,                  0,      511,       511,       1)

// -- Resynator 2 General
P(R2Switch,                       0,        1,         0,       1)
P(R2Type,                     rt_sphere, rt_scape,  rt_scape,   1)
P(R2ParamLevel,                   0,        2,         0,       1) // 0 = Level 1 etc.
P(R2SelectStickPar,               0,        1,         0,       1) // 0 = Parameter 1/3, 1 = Parameter 2/4.

P(R2Volume,                       0,      127,       100,       1)
P(R2AmpLfoDepth,                -64,       63,         0,       1)
P(R2AmpKeyTrack,                -64,       63,         0,       1)
P(R2VolumeVelocityDepth,        -64,       63,        63,       1)

P(R2ModelSizeKeyTrack,          -64,       63,         0,       1)
P(R2ModelSizeOffset,            -64,       63,         0,       1)

P(R2Octave,                       0,        3,         2,       1) // 0 = -2, 1 = -1, 2 = 0, 3 = +1
P(R2Semi,                       -24,       24,         0,       1)
P(R2Cents,                      -99,       99,         0,       1)
P(R2PitchLfoDepth,              -64,       63,         0,       1)
P(R2PitchKeyTrack,              -64,       63,        63,       1)
P(R2FreeADSR1PitchDepth,        -64,       63,         0,       1)
P(R2FreeADSR2PitchDepth,        -64,       63,         0,       1)
P(R2Free4L4TPitchDepth,           0,      127,         0,       1)

P(R2ModelVelocitySwitch,          1,      127,        64,       1)



// -- Resynator 2 Model Parameters Level 1

P(R2L1Sphere1Value,               0,      127,        64,       1)
P(R2L1Sphere2Value,               0,      127,        64,       1)
P(R2L1ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R2L1Sphere1KeyTrack,          -64,       63,         0,       1)
P(R2L1Sphere2KeyTrack,          -64,       63,         0,       1)
P(R2L1Sphere1LfoDepth,          -64,       63,         0,       1)
P(R2L1Sphere2LfoDepth,          -64,       63,         0,       1)
P(R2L1Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R2L1Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R2L1SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R2L1Scape1Value,                0,      127,        64,       1)
P(R2L1Scape2Value,                0,      127,        64,       1)
P(R2L1ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R2L1Scape1KeyTrack,           -64,       63,         0,       1)
P(R2L1Scape2KeyTrack,           -64,       63,         0,       1)
P(R2L1Scape1LfoDepth,           -64,       63,         0,       1)
P(R2L1Scape2LfoDepth,           -64,       63,         0,       1)
P(R2L1Scape1VelocityDepth,      -64,       63,         0,       1)
P(R2L1Scape2VelocityDepth,      -64,       63,         0,       1)
P(R2L1ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)


// -- Resynator 2 Model Parameters Level 2

P(R2L2Sphere1Value,               0,      127,        64,       1)
P(R2L2Sphere2Value,               0,      127,        64,       1)
P(R2L2ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R2L2Sphere1KeyTrack,          -64,       63,         0,       1)
P(R2L2Sphere2KeyTrack,          -64,       63,         0,       1)
P(R2L2Sphere1LfoDepth,          -64,       63,         0,       1)
P(R2L2Sphere2LfoDepth,          -64,       63,         0,       1)
P(R2L2Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R2L2Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R2L2SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R2L2Scape1Value,                0,      127,        64,       1)
P(R2L2Scape2Value,                0,      127,        64,       1)
P(R2L2ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R2L2Scape1KeyTrack,           -64,       63,         0,       1)
P(R2L2Scape2KeyTrack,           -64,       63,         0,       1)
P(R2L2Scape1LfoDepth,           -64,       63,         0,       1)
P(R2L2Scape2LfoDepth,           -64,       63,         0,       1)
P(R2L2Scape1VelocityDepth,      -64,       63,         0,       1)
P(R2L2Scape2VelocityDepth,      -64,       63,         0,       1)
P(R2L2ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)


// -- Resynator 2 Model Parameters Level 3

P(R2L3Sphere1Value,               0,      127,        64,       1)
P(R2L3Sphere2Value,               0,      127,        64,       1)
P(R2L3ContourSphere,          ct_off,   ct_stick,   ct_off,     1)
P(R2L3Sphere1KeyTrack,          -64,       63,         0,       1)
P(R2L3Sphere2KeyTrack,          -64,       63,         0,       1)
P(R2L3Sphere1LfoDepth,          -64,       63,         0,       1)
P(R2L3Sphere2LfoDepth,          -64,       63,         0,       1)
P(R2L3Sphere1VelocityDepth,     -64,       63,         0,       1)
P(R2L3Sphere2VelocityDepth,     -64,       63,         0,       1)
P(R2L3SphereStickPlayback, stp_oneShot, stp_repeat, stp_off,    1)

P(R2L3Scape1Value,                0,      127,        64,       1)
P(R2L3Scape2Value,                0,      127,        64,       1)
P(R2L3ContourScape,           ct_off,   ct_stick,   ct_off,     1)
P(R2L3Scape1KeyTrack,           -64,       63,         0,       1)
P(R2L3Scape2KeyTrack,           -64,       63,         0,       1)
P(R2L3Scape1LfoDepth,           -64,       63,         0,       1)
P(R2L3Scape2LfoDepth,           -64,       63,         0,       1)
P(R2L3Scape1VelocityDepth,      -64,       63,         0,       1)
P(R2L3Scape2VelocityDepth,      -64,       63,         0,       1)
P(R2L3ScapeStickPlayback,  stp_oneShot, stp_repeat, stp_off,    1)



///////////////////////////////////////////////////////////////////////////////////////////////////////

// name                         min       max      default    quant


//
// Shaper 1 Par. Levels
//
P(R1ResEnvA,                     0,       127,       0,         1)
P(R1ResEnvD,                     0,       127,       0,         1)
P(R1ResEnvS,                     0,       127,     127,         1)
P(R1ResEnvR,                     0,       127,       0,         1)
P(R1ResEnvMode,         env_normal, env_repeat, env_normal,     1)

P(R1ParaEnvVelocityDepth,      -64,        63,       0,         1)

P(R1L1Scape1EnvDepth,          -64,        63,       0,         1)
P(R1L1Scape2EnvDepth,          -64,        63,       0,         1)
P(R1L1Sphere1EnvDepth,         -64,        63,       0,         1)
P(R1L1Sphere2EnvDepth,         -64,        63,       0,         1)
P(R1L2Scape1EnvDepth,          -64,        63,       0,         1)
P(R1L2Scape2EnvDepth,          -64,        63,       0,         1)
P(R1L2Sphere1EnvDepth,         -64,        63,       0,         1)
P(R1L2Sphere2EnvDepth,         -64,        63,       0,         1)
P(R1L3Scape1EnvDepth,          -64,        63,       0,         1)
P(R1L3Scape2EnvDepth,          -64,        63,       0,         1)
P(R1L3Sphere1EnvDepth,         -64,        63,       0,         1)
P(R1L3Sphere2EnvDepth,         -64,        63,       0,         1)

//
// Shaper 1 Amp
//
P(R1AmpEnvA,                     0,       127,       0,         1)
P(R1AmpEnvD,                     0,       127,       0,         1)
P(R1AmpEnvS,                     0,       127,     127,         1)
P(R1AmpEnvR,                     0,       127,       0,         1)
P(R1AmpEnvMode,         env_normal, env_repeat, env_normal,     1)


//
// Shaper 1 Free ADSR
//
P(R1FreeEnvA,                    0,       127,       0,         1)
P(R1FreeEnvD,                    0,       127,       0,         1)
P(R1FreeEnvS,                    0,       127,     127,         1)
P(R1FreeEnvR,                    0,       127,       0,         1)
P(R1FreeEnvMode,        env_normal, env_repeat, env_normal,     1)
P(R1FreeEnvDepth,                0,       127,     127,         1)
P(FreeADSR1VelocityDepth,      -64,        63,       0,         1)

//
// Shaper 2 Par. Levels
//
P(R2ResEnvA,                     0,       127,       0,         1)
P(R2ResEnvD,                     0,       127,       0,         1)
P(R2ResEnvS,                     0,       127,     127,         1)
P(R2ResEnvR,                     0,       127,       0,         1)
P(R2ResEnvMode,         env_normal, env_repeat, env_normal,     1)

P(R2ParaEnvVelocityDepth,      -64,        63,       0,         1)

P(R2L1Scape1EnvDepth,          -64,        63,       0,         1)
P(R2L1Scape2EnvDepth,          -64,        63,       0,         1)
P(R2L1Sphere1EnvDepth,         -64,        63,       0,         1)
P(R2L1Sphere2EnvDepth,         -64,        63,       0,         1)
P(R2L2Scape1EnvDepth,          -64,        63,       0,         1)
P(R2L2Scape2EnvDepth,          -64,        63,       0,         1)
P(R2L2Sphere1EnvDepth,         -64,        63,       0,         1)
P(R2L2Sphere2EnvDepth,         -64,        63,       0,         1)
P(R2L3Scape1EnvDepth,          -64,        63,       0,         1)
P(R2L3Scape2EnvDepth,          -64,        63,       0,         1)
P(R2L3Sphere1EnvDepth,         -64,        63,       0,         1)
P(R2L3Sphere2EnvDepth,         -64,        63,       0,         1)

//
// Shaper 2 Amp
//
P(R2AmpEnvA,                     0,       127,       0,         1)
P(R2AmpEnvD,                     0,       127,       0,         1)
P(R2AmpEnvS,                     0,       127,     127,         1)
P(R2AmpEnvR,                     0,       127,       0,         1)
P(R2AmpEnvMode,         env_normal, env_repeat, env_normal,     1)


//
// Shaper 2 Free ADSR
//
P(R2FreeEnvA,                    0,       127,       0,         1)
P(R2FreeEnvD,                    0,       127,       0,         1)
P(R2FreeEnvS,                    0,       127,     127,         1)
P(R2FreeEnvR,                    0,       127,       0,         1)
P(R2FreeEnvMode,        env_normal, env_repeat, env_normal,     1)
P(R2FreeEnvDepth,                0,       127,     127,         1)
P(FreeADSR2VelocityDepth,      -64,        63,       0,         1)


//
// Shaper 1/2 Free 4 Level / 4 Time
//
P(FreeEnvLevel1,               -64,        63,       0,         1)
P(FreeEnvLevel2,               -64,        63,       0,         1)
P(FreeEnvLevel3,               -64,        63,       0,         1)
P(FreeEnvLevel4,               -64,        63,       0,         1)
P(FreeEnvTime1,                  0,       127,       0,         1)
P(FreeEnvTime2,                  0,       127,       0,         1)
P(FreeEnvTime3,                  0,       127,       0,         1)
P(FreeEnvTime4,                  0,       127,       0,         1)
P(TLFreeEnvMode,        env_normal, env_repeat, env_normal,     1)
P(TLFreeEnvDepth,                0,       127,     127,         1)
P(Free4Level4TimeVelocityDepth, -64,        63,       0,         1)


//
// Shaper 1/2 General
//
P(Shaper12Status,         s12_resy,  s12_free,   s12_amp,       1)
P(FreeEnvType,           fet_2adsr,  fet_4l4t, fet_2adsr,       1)

// Shaper 1/2 NeuronVS
P(ShaperResySelect,       s12_resy,  s2_free,    s12_amp,       1)


// name                         min       max      default    quant

//
// -- Mod/LFO
//
P(LFOSwitch,                     0,         1,       0,         1)
P(LFODepth,                      0,       127,       0,         1)
P(LFORate,                       0,      1000,       0,         1) // to 20 Hz, steps of 0.02
P(LFODelay,                    -64,        63,       0,         1)
P(LFOWaveForm,              wf_tri,  wf_num-1,  wf_tri,         1)

//
// -- Blender
//
P(BlenderType,              bt_mix,  bt_num-1,  bt_mix,         1)
P(BlenderAmount,               -64,        63,       0,         1)
P(BlenderLfoDepth,             -64,        63,       0,         1)
P(BlenderFreeADSR1Depth,       -64,        63,       0,         1)
P(BlenderFreeADSR2Depth,       -64,        63,       0,         1)
P(BlenderFree4L4TDepth,          0,       127,       0,         1)

//
// -- Slicer
//
P(SlicerSwitchType,         sl_off,     sl_3d,  sl_off,         1)
P(SlicerDepth,                   0,       127,       0,         1)
P(SlicerRate,                    0,       200,       0,         1) // to 20 Hz in 0.1 steps
P(SlicerWaveForm,           wf_tri,  wf_num-1,  wf_tri,         1)

  // TODO? Add these again when the engine can deal with them. Ever?
  //AddItem(SlicerFreeADSR1Depth,		nd_FreeADSRTargetDepth_default,		"ADSR 1 Depth",		"SlicerFreeADSR1Depth", 		nd_FreeADSRTargetDepth_min,		nd_FreeADSRTargetDepth_max,		nd_FreeADSRTargetDepth_flip,		nd_FreeADSRTargetDepth_type);
  //AddItem(SlicerFreeADSR2Depth,		nd_FreeADSRTargetDepth_default,		"ADSR 2 Depth",		"SlicerFreeADSR2Depth", 		nd_FreeADSRTargetDepth_min,		nd_FreeADSRTargetDepth_max,		nd_FreeADSRTargetDepth_flip,		nd_FreeADSRTargetDepth_type);
  //AddItem(SlicerFree4L4TDepth,		nd_Free4L4TEnvTargetDepth_default,		"4L/4T Depth",		"SlicerFree4L4TDepth", 		nd_Free4L4TEnvDepth_min,		nd_Free4L4TEnvDepth_max,		nd_Free4L4TEnvDepth_flip,		nd_Free4L4TEnvDepth_type);


// name                         min       max      default    quant

//
// -- Silver General
//
P(SilverSwitch,                   0,        1,       0,         1)
// TODO: add another level for surround?
P(SilverParamLevel,               0,        2,       0,         1)

//
// -- Silver Filter
//
P(FilterType,             ft_24dbLP, ft_num-1, ft_24dbLP,       1)
P(FilterFreq,                     0,      127,     127,         1)
P(FilterReso,                     0,      127,       0,         1)
P(FilterLfoDepth,               -64,       63,       0,         1)
P(FilterKeyTrack,               -64,       63,       0,         1)
P(FilterCutoffVelocityDepth,    -64,       63,       0,         1)
P(SilverL1Contour,           ct_off, ct_stick, ct_shaper,       1)
P(SilverL1StickPlayback, stp_oneShot, stp_repeat, stp_off,      1)


//
// Silver Freq FX
//
P(FreqFXSwitch,                   0,        1,       0,         1)
P(CurFreqFX,             ffx_EQComp, ffx_num-1, ffx_EQComp,     1)
P(SilverL2Contour,           ct_off, ct_stick, ct_shaper,       1)
P(SilverL2StickPlayback, stp_oneShot, stp_repeat, stp_off,      1)

// --- EQ/Compressor
P(EQ_Switch,                      0,        1,       0,         1)
P(EQ_LowShelfSwitch,              0,        1,       0,         1)
P(EQ_LowShelfGain,              -48,      +48,       0,         1) // steps of 0.5 dB
P(EQ_LowShelfFreq,                0,      127,      75,         1) // 75 = 1 kHz
P(EQ_LowShelfSlope,               1,      100,       0,         1) // steps of 0.1
P(EQ_Band1Switch,                 0,        1,       0,         1)
P(EQ_Band1Gain,                 -48,      +48,       0,         1) // steps of 0.5 dB
P(EQ_Band1Freq,                   0,      127,      75,         1) // 75 = 1 kHz
P(EQ_Band1Q,                      1,      100,       0,         1) // steps of 0.1
P(EQ_Band2Switch,                 0,        1,       0,         1)
P(EQ_Band2Gain,                 -48,      +48,       0,         1) // steps of 0.5 dB
P(EQ_Band2Freq,                   0,      127,      75,         1) // 75 = 1 kHz
P(EQ_Band2Q,                      1,      100,       0,         1) // steps of 0.1
P(EQ_HighShelfSwitch,             0,        1,       0,         1)
P(EQ_HighShelfGain,             -48,      +48,       0,         1) // steps of 0.5 dB
P(EQ_HighShelfFreq,               0,      127,      75,         1) // 75 = 1 kHz
P(EQ_HighShelfSlope,              1,      100,       0,         1) // steps of 0.1

P(CR_Switch,                      0,        1,       0,         1)
P(CR_Threshold,                 -48,        0,       0,         1)
P(CR_OutGain,                     0,      120,       0,         1) // steps of 0.1 dB
P(CR_Responsiveness,              0,      127,       0,         1)


// --- Distortion
P(DS_InGain,                      0,      127,      64,         1)
P(DS_PreFilter,                   0,      127,       0,         1)
P(DS_ClipCurveType,         dc_Chop, dc_num-1, dc_Chop,         1)
P(DS_OutGain,                     0,      127,      64,         1)

// --- Ring Modulator
P(RM_Mix,                         0,      127,       0,         1)
P(RM_Speed,                       0,      200,       0,         1) // steps of 0.1 Hz
P(RM_Depth,                       0,      127,       0,         1)
P(RM_WaveForm,               wf_tri, wf_num-1,  wf_tri,         1)
P(RM_ModFreq,                     0,      127,       0,         1)
P(RM_XoverDelay,                  0,      127,       0,         1)
P(RM_XoverTime,                   0,     1000,       0,         1)
P(RM_XoverDelayFeedback,        -64,       63,       0,         1)

// --- Sp_warp
P(SW_Mix,                         0,      127,       0,         1)
P(SW_Frequency,                   0,      127,       0,         1)
P(SW_Tilt,                        0,      127,       0,         1)
P(SW_Damping,                     0,      127,       0,         1)
P(SW_Speed,                       0,      200,       0,         1) // steps of 0.1 Hz
P(SW_Depth,                       0,      127,       0,         1)

// --- Decimator
P(DC_Mix,                         0,      127,       0,         1)
P(DC_SHFactor,                    0,      127,       0,         1)
P(DC_PreFilterCutoff,             0,      127,       0,         1)



// name                         min       max      default    quant


//
// Silver Time FX
//
P(TimeFXSwitch,                   0,        1,       0,         1)
P(CurTimeFX,     tfx_StereoSpread, tfx_num-1, tfx_StereoSpread, 1)
P(SilverL3Contour,           ct_off, ct_stick, ct_shaper,       1)
P(SilverL3StickPlayback, stp_oneShot, stp_repeat, stp_off,      1)

// --- Stereo Spread
P(SS_ChanDelay,                 -64,       63,       0,         1)
P(SS_Feedback,                  -64,       63,       0,         1)

// --- L/R Delay
P(LRD_Mix,                        0,      127,       0,         1)
P(LRD_Time,                       0,     1000,       0,         1)
P(LRD_Feedback,                 -64,       63,       0,         1)

// --- Flanger
P(FL_Mix,                         0,      127,       0,         1)
P(FL_Depth,                       0,      127,       0,         1)
P(FL_Speed,                       0,      200,       0,         1) // steps of 0.1 Hz
P(FL_WaveForm,               wf_tri, wf_num-1,  wf_tri,         1)
P(FL_Feedback,                  -64,       63,       0,         1)
P(FL_StereoPhase,               -64,       63,       0,         1)


// --- Phaser
P(PH_Mix,                         0,      127,       0,         1)
P(PH_Depth,                       0,      127,       0,         1)
P(PH_Speed,                       0,      200,       0,         1) // steps of 0.1 Hz
P(PH_WaveForm,               wf_tri, wf_num-1,  wf_tri,         1)
P(PH_Feedback,                  -64,       63,       0,         1)
P(PH_StereoPhase,               -64,       63,       0,         1)

// --- Chorus
P(CH_Mix,                         0,      127,       0,         1)
P(CH_Depth,                       0,      127,       0,         1)
P(CH_Speed,                       0,      200,       0,         1) // steps of 0.1 Hz
P(CH_WaveForm,               wf_tri, wf_num-1,  wf_tri,         1)
P(CH_Feedback,                  -64,       63,       0,         1)
P(CH_StereoPhase,               -64,       63,       0,         1)
P(CH_PreDelay,                    0,      127,       0,         1)


//
// Shaper 3
//
P(FilterEnvA,                    0,       127,       0,         1)
P(FilterEnvD,                    0,       127,       0,         1)
// TODO: Default sustain to 127?
P(FilterEnvS,                    0,       127,       0,         1)
P(FilterEnvR,                    0,       127,       0,         1)
P(FilterEnvMode,        env_normal, env_repeat, env_normal,     1)
P(FilterEnvDepth,              -64,        63,       0,         1)
P(FilterEnvVelocityDepth,      -64,        63,       0,         1)

// Shaper 3 Misc
P(Shaper3Status,         s3_mfxMix, s3_silver, s3_silver,       1)


//
// Free Controllers
//


// name                         min       max      default    quant

// -- Aftertouch
P(AftertouchDest1,          cc_none, cc_num-1,   cc_none,      1)
P(AftertouchDest2,          cc_none, cc_num-1,   cc_none,      1)
P(AftertouchDest3,          cc_none, cc_num-1,   cc_none,      1)
P(AftertouchDest4,          cc_none, cc_num-1,   cc_none,      1)
P(AftertouchDestDepth1,         -64,       63,        63,      1)
P(AftertouchDestDepth2,         -64,       63,        63,      1)
P(AftertouchDestDepth3,         -64,       63,        63,      1)
P(AftertouchDestDepth4,         -64,       63,        63,      1)

// -- Controller 1 Up
P(Controller1UpDest1,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1UpDest2,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1UpDest3,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1UpDest4,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1UpDestDepth1,      -64,       63,        63,      1)
P(Controller1UpDestDepth2,      -64,       63,        63,      1)
P(Controller1UpDestDepth3,      -64,       63,        63,      1)
P(Controller1UpDestDepth4,      -64,       63,        63,      1)

// -- Controller 1 Down
P(Controller1DnDest1,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1DnDest2,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1DnDest3,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1DnDest4,       cc_none, cc_num-1,   cc_none,      1)
P(Controller1DnDestDepth1,      -64,       63,        63,      1)
P(Controller1DnDestDepth2,      -64,       63,        63,      1)
P(Controller1DnDestDepth3,      -64,       63,        63,      1)
P(Controller1DnDestDepth4,      -64,       63,        63,      1)

// -- Controller 2
P(Controller2Dest1,         cc_none, cc_num-1,   cc_none,      1)
P(Controller2Dest2,         cc_none, cc_num-1,   cc_none,      1)
P(Controller2Dest3,         cc_none, cc_num-1,   cc_none,      1)
P(Controller2Dest4,         cc_none, cc_num-1,   cc_none,      1)
P(Controller2DestDepth1,        -64,       63,        63,      1)
P(Controller2DestDepth2,        -64,       63,        63,      1)
P(Controller2DestDepth3,        -64,       63,        63,      1)
P(Controller2DestDepth4,        -64,       63,        63,      1)

// -- Controller 3
P(Controller3Dest1,         cc_none, cc_num-1,   cc_none,      1)
P(Controller3Dest2,         cc_none, cc_num-1,   cc_none,      1)
P(Controller3Dest3,         cc_none, cc_num-1,   cc_none,      1)
P(Controller3Dest4,         cc_none, cc_num-1,   cc_none,      1)
P(Controller3DestDepth1,        -64,       63,        63,      1)
P(Controller3DestDepth2,        -64,       63,        63,      1)
P(Controller3DestDepth3,        -64,       63,        63,      1)
P(Controller3DestDepth4,        -64,       63,        63,      1)

  // -- Controller 4
P(Controller4Dest1,         cc_none, cc_num-1,   cc_none,      1)
P(Controller4Dest2,         cc_none, cc_num-1,   cc_none,      1)
P(Controller4Dest3,         cc_none, cc_num-1,   cc_none,      1)
P(Controller4Dest4,         cc_none, cc_num-1,   cc_none,      1)
P(Controller4DestDepth1,        -64,       63,        63,      1)
P(Controller4DestDepth2,        -64,       63,        63,      1)
P(Controller4DestDepth3,        -64,       63,        63,      1)
P(Controller4DestDepth4,        -64,       63,        63,      1)


// -- Controllers "Other"

P(FootSwitchDest,          fsw_none, fsw_num-1, fsw_none,      1)
P(PitchBendRange,                 0,       12,         2,      1) // semis


// -- Controllers NeuronVS

P(AftertouchDest,         cvd_first, cvd_last, cvd_FilterFreq,    1)
P(AftertouchDepth,              -64,       63,         0,         1)
P(ModulationDest,         cvd_first, cvd_last, cvd_LFODepth,      1)
P(ModulationDepth,              -64,       63,         0,         1)
P(BreathDest,             cvd_first, cvd_last, cvd_BlenderAmount, 1)
P(BreathDepth,                  -64,       63,         0,         1)
P(CC03Dest,               cvd_first, cvd_last, cvd_SlicerDepth,   1)
P(CC03Depth,                    -64,       63,         0,         1)
P(FootDest,               cvd_first, cvd_last, cvd_R2Volume,      1)
P(FootDepth,                    -64,       63,         0,         1)
P(ExpressionDest,         cvd_first, cvd_last, cvd_R1Volume,      1)
P(ExpressionDepth,              -64,       63,         0,         1)

P(Knob1R1Select,          cvd_first, cvd_last, cvd_FilterFreq,    1)
P(Knob2R1Select,          cvd_first, cvd_last, cvd_BlenderAmount, 1)
P(Knob3R1Select,          cvd_first, cvd_last, cvd_Amp1EnvA,      1)
P(Knob4R1Select,          cvd_first, cvd_last, cvd_FilterReso,    1)

//have to put this here, otherwise PC-crashes. this has nothing
//todo with init-order etc. try to place an additional parm before
//ExpressionDepth and see whether prolem persist/search why
P(SlicerSwitchBackup,       sl_off,     sl_3d,  sl_off,         1)

//
// -- Sound-Level Master FX
//
P(SoundMFXSwitch,                 0,        1,         0,      1)

P(SoundMFXDelaySwitch,            0,        1,         0,      1)
P(SoundMFXDelayMix,               0,      127,         0,      1)
P(SoundMFXDelayLTime,             0,     1000,         0,      1)
P(SoundMFXDelayRTime,             0,     1000,         0,      1)
P(SoundMFXDelayFeedback,        -64,       63,         0,      1)
P(SoundMFXDelayFdbkDamp,          0,      127,         0,      1)

P(SoundMFXReverbSwitch,           0,        1,         0,      1)
P(SoundMFXReverbMix,              0,      127,         0,      1)
P(SoundMFXReverbRoom,  rv_SmallRoom, rv_num-1, rv_SmallRoom,   1)
P(SoundMFXRevDecayTime,           0,      127,         0,      1)
P(SoundMFXRevDiffusion,           0,      127,         0,      1)
P(SoundMFXRevHFDamp,              0,      127,         0,      1)
P(SoundMFXRevDetune,              0,      127,         0,      1)
P(SoundMFXRevSpeed,               0,      200,         0,      1) // steps of 0.1 Hz

#undef P
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef SOUNDPARAMS_H
#define SOUNDPARAMS_H

#include "CParamDB.h"
#include "NASengine.h"

enum
{
#define P(name, min, max, default, quant) name,
#include __FILE__

  kNumSoundParams
};


#define NUM_SOUND_PROGS 1000


class SoundParams : public CParamDB
{
  public: 

  SoundParams();

  bool Load(int index);
  bool Save(int index);

};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: SoundParams.h,v $
// Revision 1.9  2004/11/24 11:11:14  joffe
// strange crash on PC now gone - need to examine this
//
// Revision 1.8  2004/11/23 08:07:55  joffe
// added backup-parameter for slicer switch/type
//
// Revision 1.7  2004/11/11 04:03:51  joffe
// few new defaults/shaper-resy select added
//
// Revision 1.6  2004/11/03 00:59:32  joffe
// knobselect added
//
// Revision 1.5  2004/11/02 13:08:17  joffe
// modulation-matrix added
//
// Revision 1.4  2004/10/29 01:55:13  joffe
// controller-destinations added
//
// Revision 1.3  2004/10/28 09:28:07  joffe
// voice-limitation added
//
// Revision 1.2  2004/08/26 01:06:25  joffe
// minor fixes/improvements
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
