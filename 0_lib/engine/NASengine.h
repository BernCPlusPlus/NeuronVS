///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: NASengine.h,v $
// $Revision: 1.9 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

//    group                  name                           min            max

///////////////////////////////
//
// GLOBAL PARAMETERS
//
///////////////////////////////

#ifdef NAS_GP

NAS_GP(nasgpMisc,           nasMasterTune,                400.0,        480.0)

#undef NAS_GP
#endif


///////////////////////////////
//
// SOUND PARAMETERS
//
///////////////////////////////

#ifdef NAS_SP

NAS_SP(nasspMisc,           nasSoundPan,                   -1.0,          1.0)
NAS_SP(nasspMisc,           nasSoundPanKeyTrack,           -1.0,          1.0)
NAS_SP(nasspMisc,           nasPitchBendRange,              0.0,         12.0) // semis

// -----------
// RESYNATOR 1
// -----------

NAS_SP(nasspResy1,          nasR1Switch,                    0.0,          1.0)
NAS_SP(nasspResy1,          nasR1Volume,                    0.0,          1.0)
NAS_SP(nasspResy1,          nasR1AmpLfoDepth,              -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1AmpKeyTrack,              -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1VolumeVelocityDepth,      -1.0,          1.0)

NAS_SP(nasspResy1,          nasR1ModelSizeKeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1ModelSizeOffset,          -1.0,          1.0)

NAS_SP(nasspResy1,          nasR1Octave,                    0.0,          3.0) // 0.0 = -2 octaves
NAS_SP(nasspResy1,          nasR1Semi,                    -24.0,         24.0)
NAS_SP(nasspResy1,          nasR1Cents,                   -99.0,         99.0)
NAS_SP(nasspResy1,          nasR1PitchLfoDepth,            -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1PitchKeyTrack,            -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1FreeADSR1PitchDepth,      -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1FreeADSR2PitchDepth,      -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1Free4L4TPitchDepth,        0.0,          1.0)

NAS_SP(nasspResy1,          nasR1ModelVelocitySwitch,       1.0,        127.0)

// -- Resynator 1 Model Parameters Level 1

NAS_SP(nasspResy1,          nasR1L1Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy1,          nasR1L1Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L1ContourScape,         ct_off,     ct_stick)

// -- Resynator 1 Model Parameters Level 2

NAS_SP(nasspResy1,          nasR1L2Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy1,          nasR1L2Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L2ContourScape,         ct_off,     ct_stick)

// -- Resynator 1 Model Parameters Level 3

NAS_SP(nasspResy1,          nasR1L3Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy1,          nasR1L3Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy1,          nasR1L3ContourScape,         ct_off,     ct_stick)


// -----------
// RESYNATOR 2
// -----------

NAS_SP(nasspResy2,          nasR2Switch,                    0.0,          1.0)
NAS_SP(nasspResy2,          nasR2Volume,                    0.0,          1.0)
NAS_SP(nasspResy2,          nasR2AmpLfoDepth,              -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2AmpKeyTrack,              -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2VolumeVelocityDepth,      -1.0,          1.0)

NAS_SP(nasspResy2,          nasR2ModelSizeKeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2ModelSizeOffset,          -1.0,          1.0)

NAS_SP(nasspResy2,          nasR2Octave,                    0.0,          3.0) // 0.0 = -2 octaves
NAS_SP(nasspResy2,          nasR2Semi,                    -24.0,         24.0)
NAS_SP(nasspResy2,          nasR2Cents,                   -99.0,         99.0)
NAS_SP(nasspResy2,          nasR2PitchLfoDepth,            -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2PitchKeyTrack,            -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2FreeADSR1PitchDepth,      -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2FreeADSR2PitchDepth,      -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2Free4L4TPitchDepth,        0.0,          1.0)

NAS_SP(nasspResy2,          nasR2ModelVelocitySwitch,       1.0,        127.0)

// -- Resynator 2 Model Parameters Level 1

NAS_SP(nasspResy2,          nasR2L1Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy2,          nasR2L1Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L1ContourScape,         ct_off,     ct_stick)

// -- Resynator 2 Model Parameters Level 2

NAS_SP(nasspResy2,          nasR2L2Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy2,          nasR2L2Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L2ContourScape,         ct_off,     ct_stick)

// -- Resynator 2 Model Parameters Level 3

NAS_SP(nasspResy2,          nasR2L3Sphere1Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere2Value,            0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere1KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere2KeyTrack,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere1LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere2LfoDepth,        -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere1VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Sphere2VelocityDepth,   -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3ContourSphere,        ct_off,     ct_stick)

NAS_SP(nasspResy2,          nasR2L3Scape1Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape2Value,             0.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape1KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape2KeyTrack,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape1LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape2LfoDepth,         -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape1VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3Scape2VelocityDepth,    -1.0,          1.0)
NAS_SP(nasspResy2,          nasR2L3ContourScape,         ct_off,     ct_stick)


//
// Shaper 1 Par. Levels
//
NAS_SP(nasspShaper1,        nasR1ResEnvA,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1ResEnvD,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1ResEnvS,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1ResEnvR,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1ResEnvMode,         env_normal,   env_repeat)
NAS_SP(nasspShaper1,        nasR1ParaEnvVelocityDepth,     -1.0,          1.0)

NAS_SP(nasspShaper1,        nasR1L1Scape1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L1Scape2EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L1Sphere1EnvDepth,        -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L1Sphere2EnvDepth,        -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L2Scape1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L2Scape2EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L2Sphere1EnvDepth,        -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L2Sphere2EnvDepth,        -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L3Scape1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L3Scape2EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L3Sphere1EnvDepth,        -1.0,          1.0)
NAS_SP(nasspShaper1,        nasR1L3Sphere2EnvDepth,        -1.0,          1.0)


//
// Shaper 1 Amp
//
NAS_SP(nasspShaper1,        nasR1AmpEnvA,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1AmpEnvD,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1AmpEnvS,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1AmpEnvR,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1AmpEnvMode,         env_normal,   env_repeat)


//
// Shaper 1 Free ADSR
//
NAS_SP(nasspShaper1,        nasR1FreeEnvA,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1FreeEnvD,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1FreeEnvS,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1FreeEnvR,                   0.0,          1.0)
NAS_SP(nasspShaper1,        nasR1FreeEnvMode,         env_normal,   env_repeat)
NAS_SP(nasspShaper1,        nasR1FreeEnvDepth,               0.0,          1.0)
NAS_SP(nasspShaper1,        nasFreeADSR1VelocityDepth,      -1.0,          1.0)


//
// Shaper 2 Par. Levels
//
NAS_SP(nasspShaper2,        nasR2ResEnvA,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2ResEnvD,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2ResEnvS,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2ResEnvR,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2ResEnvMode,          env_normal,   env_repeat)
NAS_SP(nasspShaper2,        nasR2ParaEnvVelocityDepth,      -1.0,          1.0)

NAS_SP(nasspShaper2,        nasR2L1Scape1EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L1Scape2EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L1Sphere1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L1Sphere2EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L2Scape1EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L2Scape2EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L2Sphere1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L2Sphere2EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L3Scape1EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L3Scape2EnvDepth,          -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L3Sphere1EnvDepth,         -1.0,          1.0)
NAS_SP(nasspShaper2,        nasR2L3Sphere2EnvDepth,         -1.0,          1.0)


//
// Shaper 2 Amp
//
NAS_SP(nasspShaper2,        nasR2AmpEnvA,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2AmpEnvD,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2AmpEnvS,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2AmpEnvR,                    0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2AmpEnvMode,          env_normal,   env_repeat)


//
// Shaper 2 Free ADSR
//
NAS_SP(nasspShaper2,        nasR2FreeEnvA,                   0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2FreeEnvD,                   0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2FreeEnvS,                   0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2FreeEnvR,                   0.0,          1.0)
NAS_SP(nasspShaper2,        nasR2FreeEnvMode,         env_normal,   env_repeat)
NAS_SP(nasspShaper2,        nasR2FreeEnvDepth,               0.0,          1.0)
NAS_SP(nasspShaper2,        nasFreeADSR2VelocityDepth,      -1.0,          1.0)


//
// Shaper 1/2 Free 4 Level / 4 Time
//
NAS_SP(nasspShaper12,       nasFreeEnvLevel1,               -1.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvLevel2,               -1.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvLevel3,               -1.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvLevel4,               -1.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvTime1,                 0.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvTime2,                 0.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvTime3,                 0.0,          1.0)
NAS_SP(nasspShaper12,       nasFreeEnvTime4,                 0.0,          1.0)
NAS_SP(nasspShaper12,       nasTLFreeEnvMode,         env_normal,   env_repeat)
NAS_SP(nasspShaper12,       nasTLFreeEnvDepth,               0.0,          1.0)
NAS_SP(nasspShaper12,       nasFree4Level4TimeVelocityDepth, -1.0,          1.0)


//
// Shaper 1/2 General
//
NAS_SP(nasspShaper12,       nasFreeEnvType,            fet_2adsr,     fet_4l4t)


//
// -- Mod/LFO
//
NAS_SP(nasspLFO,            nasLFOSwitch,                    0.0,          1.0)
NAS_SP(nasspLFO,            nasLFODepth,                     0.0,          1.0)
NAS_SP(nasspLFO,            nasLFORate,                      0.0,          1.0) // to 20 Hz
NAS_SP(nasspLFO,            nasLFODelay,                    -1.0,          1.0)
NAS_SP(nasspLFO,            nasLFOWaveForm,               wf_tri,     wf_num-1)

//
// -- Blender
//
NAS_SP(nasspBlender,        nasBlenderType,               bt_mix,     bt_num-1)
NAS_SP(nasspBlender,        nasBlenderAmount,                0.0,          1.0)
NAS_SP(nasspBlender,        nasBlenderLfoDepth,             -1.0,          1.0)
NAS_SP(nasspBlender,        nasBlenderFreeADSR1Depth,       -1.0,          1.0)
NAS_SP(nasspBlender,        nasBlenderFreeADSR2Depth,       -1.0,          1.0)
NAS_SP(nasspBlender,        nasBlenderFree4L4TDepth,         0.0,          1.0)

//
// -- Slicer
//
NAS_SP(nasspSlicer,        nasSlicerSwitchType,           sl_off,        sl_3d)
NAS_SP(nasspSlicer,        nasSlicerDepth,                   0.0,          1.0)
NAS_SP(nasspSlicer,        nasSlicerRate,                    0.0,          1.0) // to 20 Hz
NAS_SP(nasspSlicer,        nasSlicerWaveForm,             wf_tri,     wf_num-1)


//
// -- Silver Filter
//
NAS_SP(nasspFilter,        nasFilterType,              ft_24dbLP,     ft_num-1)
NAS_SP(nasspFilter,        nasFilterFreq,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterReso,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterLfoDepth,               -1.0,          1.0)
NAS_SP(nasspFilter,        nasFilterKeyTrack,               -1.0,          1.0)
NAS_SP(nasspFilter,        nasFilterCutoffVelocityDepth,    -1.0,          1.0)
NAS_SP(nasspFilter,        nasFilterContour,              ct_off,     ct_stick)

//
// Shaper 3
//
NAS_SP(nasspFilter,        nasFilterEnvA,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterEnvD,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterEnvS,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterEnvR,                    0.0,          1.0)
NAS_SP(nasspFilter,        nasFilterEnvMode,          env_normal,   env_repeat)
NAS_SP(nasspFilter,        nasFilterEnvDepth,               -1.0,          1.0)
NAS_SP(nasspFilter,        nasFilterEnvVelocityDepth,       -1.0,          1.0)


//
// -- Silver General
//
NAS_SP(nasspSilver,        nasSilverSwitch,                  0.0,          1.0)

//
// Silver Freq FX
//
NAS_SP(nasspSilver,        nasFreqFXSwitch,                  0.0,          1.0)
NAS_SP(nasspSilver,        nasCurFreqFX,              ffx_EQComp,    ffx_num-1)
NAS_SP(nasspSilver,        nasFreqFXContour,              ct_off,     ct_stick)

// --- EQ/Compressor
NAS_SP(nasspSilver,        nasEQ_Switch,                     0.0,          1.0)
NAS_SP(nasspSilver,        nasEQ_LowShelfSwitch,             0.0,          1.0)
NAS_SP(nasspSilver,        nasEQ_LowShelfGain,              -1.0,          1.0) // -24dB to +24dB
NAS_SP(nasspSilver,        nasEQ_LowShelfFreq,               0.0,        127.0) // 75 = 1 kHz
NAS_SP(nasspSilver,        nasEQ_LowShelfSlope,             0.01,          1.0)
NAS_SP(nasspSilver,        nasEQ_Band1Switch,                0.0,          1.0)
NAS_SP(nasspSilver,        nasEQ_Band1Gain,                 -1.0,          1.0) // -24dB to +24dB
NAS_SP(nasspSilver,        nasEQ_Band1Freq,                  0.0,        127.0) // 75 = 1 kHz
NAS_SP(nasspSilver,        nasEQ_Band1Q,                    0.01,          1.0)
NAS_SP(nasspSilver,        nasEQ_Band2Switch,                0.0,          1.0)
NAS_SP(nasspSilver,        nasEQ_Band2Gain,                 -1.0,          1.0) // -24dB to +24dB
NAS_SP(nasspSilver,        nasEQ_Band2Freq,                  0.0,        127.0) // 75 = 1 kHz
NAS_SP(nasspSilver,        nasEQ_Band2Q,                    0.01,          1.0)
NAS_SP(nasspSilver,        nasEQ_HighShelfSwitch,            0.0,          1.0)
NAS_SP(nasspSilver,        nasEQ_HighShelfGain,             -1.0,          1.0) // -24dB to +24dB
NAS_SP(nasspSilver,        nasEQ_HighShelfFreq,              0.0,        127.0) // 75 = 1 kHz
NAS_SP(nasspSilver,        nasEQ_HighShelfSlope,            0.01,          1.0)

NAS_SP(nasspSilver,        nasCR_Switch,                     0.0,          1.0)
NAS_SP(nasspSilver,        nasCR_Threshold,                 -1.0,          0.0) // - 48dB to 0dB
NAS_SP(nasspSilver,        nasCR_OutGain,                    0.0,          1.0)
NAS_SP(nasspSilver,        nasCR_Responsiveness,             0.0,          1.0)



// --- Distortion
NAS_SP(nasspSilver,        nasDS_InGain,                     0.0,          1.0)
NAS_SP(nasspSilver,        nasDS_PreFilter,                  0.0,          1.0)
NAS_SP(nasspSilver,        nasDS_ClipCurveType,          dc_Chop,     dc_num-1)
NAS_SP(nasspSilver,        nasDS_OutGain,                    0.0,          1.0)

// --- Ring Modulator
NAS_SP(nasspSilver,        nasRM_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_Speed,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_Depth,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_WaveForm,                wf_tri,     wf_num-1)
NAS_SP(nasspSilver,        nasRM_ModFreq,                    0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_XoverDelay,                 0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_XoverTime,                  0.0,          1.0)
NAS_SP(nasspSilver,        nasRM_XoverDelayFeedback,        -1.0,          1.0)


// --- Sp_warp
NAS_SP(nasspSilver,        nasSW_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasSW_Frequency,                  0.0,          1.0)
NAS_SP(nasspSilver,        nasSW_Tilt,                       0.0,          1.0)
NAS_SP(nasspSilver,        nasSW_Damping,                    0.0,          1.0)
NAS_SP(nasspSilver,        nasSW_Speed,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasSW_Depth,                      0.0,          1.0)

// --- Decimator
NAS_SP(nasspSilver,        nasDC_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasDC_SHFactor,                   0.0,          1.0)
NAS_SP(nasspSilver,        nasDC_PreFilterCutoff,            0.0,          1.0)


//
// Silver Time FX
//
NAS_SP(nasspSilver,        nasTimeFXSwitch,                  0.0,          1.0)
NAS_SP(nasspSilver,        nasCurTimeFX,        tfx_StereoSpread,    tfx_num-1)
NAS_SP(nasspSilver,        nasTimeFXContour,              ct_off,     ct_stick)

// --- Stereo Spread
NAS_SP(nasspSilver,        nasSS_ChanDelay,                 -1.0,          1.0)
NAS_SP(nasspSilver,        nasSS_Feedback,                  -1.0,          1.0)

// --- L/R Delay
NAS_SP(nasspSilver,        nasLRD_Mix,                       0.0,          1.0)
NAS_SP(nasspSilver,        nasLRD_Time,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasLRD_Feedback,                 -1.0,          1.0)

// --- Flanger
NAS_SP(nasspSilver,        nasFL_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasFL_Depth,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasFL_Speed,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasFL_WaveForm,                wf_tri,     wf_num-1)
NAS_SP(nasspSilver,        nasFL_Feedback,                  -1.0,          1.0)
NAS_SP(nasspSilver,        nasFL_StereoPhase,               -1.0,          1.0)


// --- Phaser
NAS_SP(nasspSilver,        nasPH_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasPH_Depth,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasPH_Speed,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasPH_WaveForm,                wf_tri,     wf_num-1)
NAS_SP(nasspSilver,        nasPH_Feedback,                  -1.0,          1.0)
NAS_SP(nasspSilver,        nasPH_StereoPhase,               -1.0,          1.0)

// --- Chorus
NAS_SP(nasspSilver,        nasCH_Mix,                        0.0,          1.0)
NAS_SP(nasspSilver,        nasCH_Depth,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasCH_Speed,                      0.0,          1.0)
NAS_SP(nasspSilver,        nasCH_WaveForm,                wf_tri,     wf_num-1)
NAS_SP(nasspSilver,        nasCH_Feedback,                  -1.0,          1.0)
NAS_SP(nasspSilver,        nasCH_StereoPhase,               -1.0,          1.0)
NAS_SP(nasspSilver,        nasCH_PreDelay,                   0.0,          1.0)

#undef NAS_SP
#endif



///////////////////////////////
//
// MASTER EFFECTS
//
///////////////////////////////

#ifdef NAS_EP

NAS_EP(nasepMasterFX,      nasMFXSwitch,                   0.0,          1.0) 

NAS_EP(nasepDelay,         nasMFXDelaySwitch,              0.0,          1.0) 
NAS_EP(nasepDelay,         nasMFXDelayLTime,               0.0,          1.0) 
NAS_EP(nasepDelay,         nasMFXDelayRTime,               0.0,          1.0) 
NAS_EP(nasepDelay,         nasMFXDelayFeedback,           -1.0,          1.0) 
NAS_EP(nasepDelay,         nasMFXDelayFdbkDamp,            0.0,          1.0) 

NAS_EP(nasepReverb,        nasMFXReverbSwitch,             0.0,          1.0) 
NAS_EP(nasepReverb,        nasMFXReverbRoom,      rv_SmallRoom,     rv_num-1)
NAS_EP(nasepReverb,        nasMFXRevDecayTime,             0.0,          1.0) 
NAS_EP(nasepReverb,        nasMFXRevDiffusion,             0.0,          1.0) 
NAS_EP(nasepReverb,        nasMFXRevHFDamp,                0.0,          1.0) 
NAS_EP(nasepReverb,        nasMFXRevDetune,                0.0,          1.0) 
NAS_EP(nasepReverb,        nasMFXRevSpeed,                 0.0,          1.0) 

#undef NAS_EP
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef NASENGINE_H
#define NASENGINE_H

extern const short nas_NumSamples;      // number of processed samples
extern const short nas_NumOutChannels;  // number of outchannels in a frame
extern const short nas_NumInChannels;   // number of inchannels in a frame


///////////////////////////////////////////////////////////////////////////////
// place here global enums typedefs and all that 

enum // contour
{
  ct_off=0,
  ct_shaper,
  ct_stick
};

enum // envelope modes
{
  env_normal=0,
  env_repeat
};

enum // free envelope types
{
  fet_2adsr=0,
  fet_4l4t
};

enum // wave forms
{
  wf_tri=0,
  wf_sine,
  wf_saw_up,
  wf_saw_down,
  wf_square,
  wf_pos_tri,
  wf_pos_sine,
  wf_pos_square,
  wf_step_tri,
  wf_step_saw_up,
  wf_step_saw_down,
  wf_random,
  wf_num
};

enum // blender type
{
  bt_mix=0,
  bt_stereo,
  bt_mixssp,
  bt_chromo,
  bt_dual,
  bt_intermorph,
  bt_dtrans,
  bt_dcross,
  bt_vcross,
  bt_vchromo,
  bt_num
};

enum // slicer state
{
  sl_off=0,
  sl_vertical,
  sl_3d
};

enum // filter types
{
  ft_24dbLP=0, // own LED
  ft_12dbLP,   // own LED
  ft_6dbLP,    // special
  ft_6dbHP,    // special
  ft_Bandpass, // special
  ft_num
};

enum // freq fx types
{
  ffx_EQComp=0,
  ffx_Distortion,
  ffx_RingMod,
  ffx_Decimator,
  ffx_Sp_warp,
  ffx_num
};

enum // distortion curve types
{
  dc_Chop=0,
  dc_LinClip,
  dc_Ripple,
  dc_SoftKnee,
  dc_Sigmoid,
  dc_Exp,
  dc_num
};

enum // time fx types
{
  tfx_StereoSpread=0,
  tfx_LRDelay,
  tfx_Flanger,
  tfx_Phaser,
  tfx_Chorus,
  tfx_num
};

enum // reverb types
{
  rv_SmallRoom=0,
  rv_Plate,
  rv_MedRoom,
  rv_Hall1,
  rv_Hall2,
  rv_num
};

enum // global parameter groups
{
  nasgpMisc,
  nasgp_num
};

enum // sound parameter groups
{
  nasspAll=0,
  nasspMisc,
  nasspResy1,
  nasspResy2,
  nasspShaper1,
  nasspShaper2,
  nasspShaper12,
  nasspLFO,
  nasspBlender,
  nasspSlicer,
  nasspFilter,
  nasspSilver,
  nassp_num
};

enum // master fx parameter groups
{
  nasepMasterFX,
  nasepDelay,
  nasepReverb,
  nasep_num
};


enum
{
#define NAS_GP(group, name, min, max) name,
#include __FILE__
  kNumEngineGlobalParams
};

enum
{
#define NAS_SP(group, name, min, max) name,
#include __FILE__
  kNumEngineSoundParams
};

enum
{
#define NAS_EP(group, name, min, max) name,
#include __FILE__
  kNumEngineMFXParams
};


typedef void *nas_EngineRef;
typedef void *nas_NoteRef; 


#ifdef __cplusplus
extern "C" {
#endif
	// -----------------------------------------------------------------------------------------------------------------
	
	// Con-/Destructor
	nas_EngineRef NASEngineCreate(void);
	void NASEngineDestroy(nas_EngineRef instance);

	// Initializes the engine. Not required to be called by the UI unless
	// you want to force a complete reset
	void NASEngineInit(nas_EngineRef instance);

	// Creates the actual sound output. Number of frames is in  nas_NumSamples
	void NASEngineProcess(float *outL, float *outR, nas_EngineRef instance);
	
	// (re)starts the engine. Only needed after a call to Halt()
	void NASEngineRun(nas_EngineRef instance);
	
	// Discontinues all processing until the next call to Run()
	// Only needed if you wish to suspend processing for any reason, this  is the
	// safest way to achieve this.
	void NASEngineHalt(nas_EngineRef instance);

	// Sets the current pitchbend value for this engine, range -1...+1
	void NASEngineSetPitchBend(float pb, nas_EngineRef instance);
	
	// Initiates a note-on. noteNumber is MIDI note number, velocity is  1-127
	// If successful, it returns a valid pointer to a note context  structure that
	// holds the state variables of that note. Use this pointer as  argument when
	// requesting information about this note.
	nas_NoteRef NASEngineNoteOn(long noteNumber, long velocity, nas_EngineRef instance);

	// Puts the note into the release phase. It does not actually shut off  that note
	// at once, but rather simulates a key off event
	// Note that this event will not be processed if it is not issued by  the owning
	// engine instance.
	// IMPORTANT: since this note might still be active, its note context  is not
	// discarded until the note has reached the end of its playback time!
	bool NASEngineNoteOff(nas_NoteRef notePtr, nas_EngineRef instance);

	// Turn off Note immediately
	bool NASEngineNoteOffImmediate(nas_NoteRef notePtr, nas_EngineRef instance);

	// See whether a given noteref is valid
	bool NASEngineIsValidNoteRef(nas_NoteRef notePtr, nas_EngineRef instance);

	// Returns true if the voice is currently active, false if it is  inactive.
	// Can be used to determine the actual end of a note.
	bool NASEngineIsVoicePlaying(nas_NoteRef notePtr, nas_EngineRef instance);

	// Gets the MIDI note number of the specified note
	long NASEngineGetNoteNumber(nas_NoteRef notePtr, nas_EngineRef instance);

	// returns the time (in frames) the note has been playing.
	unsigned long NASEngineGetNoteAgeInFrames(nas_NoteRef notePtr, nas_EngineRef instance);

	// as the name says this returns the gain of given voice
	float NASEngineGetVoiceGain(nas_NoteRef notePtr, nas_EngineRef instance);

	// TODO: update global and effects
	void NASEngineUpdateParameterGroup(long groupID, float *thisSound, nas_EngineRef instance);
	void NASEngineSetModelData(int resy, int keyIndex, int rootKey, char *loScape, char *hiScape, char *loSphere, char *hiSphere, int detune, float volume, nas_EngineRef instance);
	bool NASEngineNoteOffWithRelease(nas_NoteRef notePtr, float release, nas_EngineRef instance);


	
#ifdef __cplusplus
}
#endif


// ------------------------ General Utility Functions  -----------------------------


// Returns the number of voices that the engine will currently handle.
long NASgetMaxNumVoices();

// Sets the maximum number of voices the engine can handle.
// Presently, 128 is the absolute maximum - if a value > 128 is  requested,
// the engine uses 128 and returns false, otherwise true.
bool NASsetMaxNumVoices(long numVoices);

// Returns a pointer to the engine instance that owns this note
void *NASgetOwner(nas_NoteRef notePtr);

// Shuts off all voices at once. This is not the same as a repeated  call to NoteOff(),
// it takes effect immediately and applies to all notes of all  instances currently
// playing.
bool NASallVoicesOff();

// convert modeldata pointers&values to mac big-endian style
// first call uses scape, the second sphere
bool NASconvertModelDataToMac(void *scapeSphereData, unsigned long Datasize);

bool NASgetScapeParameterNames(void *scapeData, char *names);
bool NASgetSphereParameterNames(void *sphereData, char *names);
long NASgetDefaultParsetNumber(void *sphereData);
bool NASgetDefaultScapeParameters(void *scapeData, float *params);
bool NASgetDefaultSphereParameters(void *sphereData, float *params);

//  ------------------------------------------------------------------------ ---------
//  ------------------------------------------------------------------------ ---------
//  ------------------------------------------------------------------------ ---------

#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: NASengine.h,v $
// Revision 1.9  2004/11/30 17:03:03  joffe
// new engine (pc)
//
// Revision 1.8  2004/11/29 06:48:39  joffe
// NASnoteOffImmediate added
//
// Revision 1.7  2004/11/26 19:56:10  joffe
// new engine
//
// Revision 1.6  2004/11/22 03:13:08  joffe
// new engine
//
// Revision 1.5  2004/11/10 14:23:15  joffe
// adaptions to module-engine
//
// Revision 1.4  2004/08/26 01:00:19  joffe
// prototypes added
//
// Revision 1.3  2004/08/14 06:26:59  joffe
// old statics now memberized
//
// Revision 1.2  2004/08/04 14:02:02  joffe
// mac engine added
//
// Revision 1.1  2004/07/23 18:17:48  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
