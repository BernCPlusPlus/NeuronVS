///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: MapToEngineDef.h,v $
// $Revision: 1.2 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////


#ifdef GP_MAP

GP_MAP(MasterTune,                nasMasterTune,                 engine_gp_ntf)

#undef GP_MAP
#endif


#ifdef P_MAP

P_MAP(SoundPan,                   nasSoundPan,                   engine_sp_ntf)
P_MAP(SoundPanKeyTrack,           nasSoundPanKeyTrack,           engine_sp_ntf)
P_MAP(PitchBendRange,             nasPitchBendRange,             engine_sp_ntf)

//////////////
// RESYNATOR 1
//////////////

P_MAP(R1Switch,                   nasR1Switch,                   engine_sp_ntf)
//P_MAP(R1Volume,                   nasR1Volume,                   engine_sp_ntf)
P_MAP(R1AmpLfoDepth,              nasR1AmpLfoDepth,              engine_sp_ntf)
P_MAP(R1AmpKeyTrack,              nasR1AmpKeyTrack,              engine_sp_ntf)
P_MAP(R1VolumeVelocityDepth,      nasR1VolumeVelocityDepth,      engine_sp_ntf)
P_MAP(R1ModelSizeKeyTrack,        nasR1ModelSizeKeyTrack,        engine_sp_ntf)
P_MAP(R1ModelSizeOffset,          nasR1ModelSizeOffset,          engine_sp_ntf)
P_MAP(R1Octave,                   nasR1Octave,                   engine_sp_ntf)
//P_MAP(R1Semi,                     nasR1Semi,                     engine_sp_ntf)
P_MAP(R1Cents,                    nasR1Cents,                    engine_sp_ntf)
P_MAP(R1PitchLfoDepth,            nasR1PitchLfoDepth,            engine_sp_ntf)
P_MAP(R1PitchKeyTrack,            nasR1PitchKeyTrack,            engine_sp_ntf)
P_MAP(R1FreeADSR1PitchDepth,      nasR1FreeADSR1PitchDepth,      engine_sp_ntf)
P_MAP(R1FreeADSR2PitchDepth,      nasR1FreeADSR2PitchDepth,      engine_sp_ntf)
P_MAP(R1Free4L4TPitchDepth,       nasR1Free4L4TPitchDepth,       engine_sp_ntf)
P_MAP(R1ModelVelocitySwitch,      nasR1ModelVelocitySwitch,      engine_sp_ntf)

// -- Resynator 1 Model Parameters Level 1

//P_MAP(R1L1Sphere1Value,           nasR1L1Sphere1Value,           engine_sp_ntf)
//P_MAP(R1L1Sphere2Value,           nasR1L1Sphere2Value,           engine_sp_ntf)
P_MAP(R1L1Sphere1KeyTrack,        nasR1L1Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R1L1Sphere2KeyTrack,        nasR1L1Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R1L1Sphere1LfoDepth,        nasR1L1Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R1L1Sphere2LfoDepth,        nasR1L1Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R1L1Sphere1VelocityDepth,   nasR1L1Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R1L1Sphere2VelocityDepth,   nasR1L1Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R1L1ContourSphere,          nasR1L1ContourSphere,          engine_sp_ntf)

//P_MAP(R1L1Scape1Value,            nasR1L1Scape1Value,            engine_sp_ntf)
//P_MAP(R1L1Scape2Value,            nasR1L1Scape2Value,            engine_sp_ntf)
P_MAP(R1L1Scape1KeyTrack,         nasR1L1Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R1L1Scape2KeyTrack,         nasR1L1Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R1L1Scape1LfoDepth,         nasR1L1Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R1L1Scape2LfoDepth,         nasR1L1Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R1L1Scape1VelocityDepth,    nasR1L1Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R1L1Scape2VelocityDepth,    nasR1L1Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R1L1ContourScape,           nasR1L1ContourScape,           engine_sp_ntf)


// -- Resynator 1 Model Parameters Level 2

//P_MAP(R1L2Sphere1Value,           nasR1L2Sphere1Value,           engine_sp_ntf)
//P_MAP(R1L2Sphere2Value,           nasR1L2Sphere2Value,           engine_sp_ntf)
P_MAP(R1L2Sphere1KeyTrack,        nasR1L2Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R1L2Sphere2KeyTrack,        nasR1L2Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R1L2Sphere1LfoDepth,        nasR1L2Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R1L2Sphere2LfoDepth,        nasR1L2Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R1L2Sphere1VelocityDepth,   nasR1L2Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R1L2Sphere2VelocityDepth,   nasR1L2Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R1L2ContourSphere,          nasR1L2ContourSphere,          engine_sp_ntf)

//P_MAP(R1L2Scape1Value,            nasR1L2Scape1Value,            engine_sp_ntf)
//P_MAP(R1L2Scape2Value,            nasR1L2Scape2Value,            engine_sp_ntf)
P_MAP(R1L2Scape1KeyTrack,         nasR1L2Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R1L2Scape2KeyTrack,         nasR1L2Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R1L2Scape1LfoDepth,         nasR1L2Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R1L2Scape2LfoDepth,         nasR1L2Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R1L2Scape1VelocityDepth,    nasR1L2Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R1L2Scape2VelocityDepth,    nasR1L2Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R1L2ContourScape,           nasR1L2ContourScape,           engine_sp_ntf)


// -- Resynator 1 Model Parameters Level 3

//P_MAP(R1L3Sphere1Value,           nasR1L3Sphere1Value,           engine_sp_ntf)
//P_MAP(R1L3Sphere2Value,           nasR1L3Sphere2Value,           engine_sp_ntf)
P_MAP(R1L3Sphere1KeyTrack,        nasR1L3Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R1L3Sphere2KeyTrack,        nasR1L3Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R1L3Sphere1LfoDepth,        nasR1L3Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R1L3Sphere2LfoDepth,        nasR1L3Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R1L3Sphere1VelocityDepth,   nasR1L3Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R1L3Sphere2VelocityDepth,   nasR1L3Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R1L3ContourSphere,          nasR1L3ContourSphere,          engine_sp_ntf)

//P_MAP(R1L3Scape1Value,            nasR1L3Scape1Value,            engine_sp_ntf)
//P_MAP(R1L3Scape2Value,            nasR1L3Scape2Value,            engine_sp_ntf)
P_MAP(R1L3Scape1KeyTrack,         nasR1L3Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R1L3Scape2KeyTrack,         nasR1L3Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R1L3Scape1LfoDepth,         nasR1L3Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R1L3Scape2LfoDepth,         nasR1L3Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R1L3Scape1VelocityDepth,    nasR1L3Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R1L3Scape2VelocityDepth,    nasR1L3Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R1L3ContourScape,           nasR1L3ContourScape,           engine_sp_ntf)


//////////////
// RESYNATOR 2
//////////////

P_MAP(R2Switch,                   nasR2Switch,                   engine_sp_ntf)
//P_MAP(R2Volume,                   nasR2Volume,                   engine_sp_ntf)
P_MAP(R2AmpLfoDepth,              nasR2AmpLfoDepth,              engine_sp_ntf)
P_MAP(R2AmpKeyTrack,              nasR2AmpKeyTrack,              engine_sp_ntf)
P_MAP(R2VolumeVelocityDepth,      nasR2VolumeVelocityDepth,      engine_sp_ntf)
P_MAP(R2ModelSizeKeyTrack,        nasR2ModelSizeKeyTrack,        engine_sp_ntf)
P_MAP(R2ModelSizeOffset,          nasR2ModelSizeOffset,          engine_sp_ntf)
P_MAP(R2Octave,                   nasR2Octave,                   engine_sp_ntf)
//P_MAP(R2Semi,                     nasR2Semi,                     engine_sp_ntf)
P_MAP(R2Cents,                    nasR2Cents,                    engine_sp_ntf)
P_MAP(R2PitchLfoDepth,            nasR2PitchLfoDepth,            engine_sp_ntf)
P_MAP(R2PitchKeyTrack,            nasR2PitchKeyTrack,            engine_sp_ntf)
P_MAP(R2FreeADSR1PitchDepth,      nasR2FreeADSR1PitchDepth,      engine_sp_ntf)
P_MAP(R2FreeADSR2PitchDepth,      nasR2FreeADSR2PitchDepth,      engine_sp_ntf)
P_MAP(R2Free4L4TPitchDepth,       nasR2Free4L4TPitchDepth,       engine_sp_ntf)
P_MAP(R2ModelVelocitySwitch,      nasR2ModelVelocitySwitch,      engine_sp_ntf)

// -- Resynator 2 Model Parameters Level 1

//P_MAP(R2L1Sphere1Value,           nasR2L1Sphere1Value,           engine_sp_ntf)
//P_MAP(R2L1Sphere2Value,           nasR2L1Sphere2Value,           engine_sp_ntf)
P_MAP(R2L1Sphere1KeyTrack,        nasR2L1Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R2L1Sphere2KeyTrack,        nasR2L1Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R2L1Sphere1LfoDepth,        nasR2L1Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R2L1Sphere2LfoDepth,        nasR2L1Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R2L1Sphere1VelocityDepth,   nasR2L1Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R2L1Sphere2VelocityDepth,   nasR2L1Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R2L1ContourSphere,          nasR2L1ContourSphere,          engine_sp_ntf)

//P_MAP(R2L1Scape1Value,            nasR2L1Scape1Value,            engine_sp_ntf)
//P_MAP(R2L1Scape2Value,            nasR2L1Scape2Value,            engine_sp_ntf)
P_MAP(R2L1Scape1KeyTrack,         nasR2L1Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R2L1Scape2KeyTrack,         nasR2L1Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R2L1Scape1LfoDepth,         nasR2L1Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R2L1Scape2LfoDepth,         nasR2L1Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R2L1Scape1VelocityDepth,    nasR2L1Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R2L1Scape2VelocityDepth,    nasR2L1Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R2L1ContourScape,           nasR2L1ContourScape,           engine_sp_ntf)


// -- Resynator 2 Model Parameters Level 2

//P_MAP(R2L2Sphere1Value,           nasR2L2Sphere1Value,           engine_sp_ntf)
//P_MAP(R2L2Sphere2Value,           nasR2L2Sphere2Value,           engine_sp_ntf)
P_MAP(R2L2Sphere1KeyTrack,        nasR2L2Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R2L2Sphere2KeyTrack,        nasR2L2Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R2L2Sphere1LfoDepth,        nasR2L2Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R2L2Sphere2LfoDepth,        nasR2L2Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R2L2Sphere1VelocityDepth,   nasR2L2Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R2L2Sphere2VelocityDepth,   nasR2L2Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R2L2ContourSphere,          nasR2L2ContourSphere,          engine_sp_ntf)

//P_MAP(R2L2Scape1Value,            nasR2L2Scape1Value,            engine_sp_ntf)
//P_MAP(R2L2Scape2Value,            nasR2L2Scape2Value,            engine_sp_ntf)
P_MAP(R2L2Scape1KeyTrack,         nasR2L2Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R2L2Scape2KeyTrack,         nasR2L2Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R2L2Scape1LfoDepth,         nasR2L2Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R2L2Scape2LfoDepth,         nasR2L2Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R2L2Scape1VelocityDepth,    nasR2L2Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R2L2Scape2VelocityDepth,    nasR2L2Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R2L2ContourScape,           nasR2L2ContourScape,           engine_sp_ntf)


// -- Resynator 2 Model Parameters Level 3

//P_MAP(R2L3Sphere1Value,           nasR2L3Sphere1Value,           engine_sp_ntf)
//P_MAP(R2L3Sphere2Value,           nasR2L3Sphere2Value,           engine_sp_ntf)
P_MAP(R2L3Sphere1KeyTrack,        nasR2L3Sphere1KeyTrack,        engine_sp_ntf)
P_MAP(R2L3Sphere2KeyTrack,        nasR2L3Sphere2KeyTrack,        engine_sp_ntf)
P_MAP(R2L3Sphere1LfoDepth,        nasR2L3Sphere1LfoDepth,        engine_sp_ntf)
P_MAP(R2L3Sphere2LfoDepth,        nasR2L3Sphere2LfoDepth,        engine_sp_ntf)
P_MAP(R2L3Sphere1VelocityDepth,   nasR2L3Sphere1VelocityDepth,   engine_sp_ntf)
P_MAP(R2L3Sphere2VelocityDepth,   nasR2L3Sphere2VelocityDepth,   engine_sp_ntf)
P_MAP(R2L3ContourSphere,          nasR2L3ContourSphere,          engine_sp_ntf)

//P_MAP(R2L3Scape1Value,            nasR2L3Scape1Value,            engine_sp_ntf)
//P_MAP(R2L3Scape2Value,            nasR2L3Scape2Value,            engine_sp_ntf)
P_MAP(R2L3Scape1KeyTrack,         nasR2L3Scape1KeyTrack,         engine_sp_ntf)
P_MAP(R2L3Scape2KeyTrack,         nasR2L3Scape2KeyTrack,         engine_sp_ntf)
P_MAP(R2L3Scape1LfoDepth,         nasR2L3Scape1LfoDepth,         engine_sp_ntf)
P_MAP(R2L3Scape2LfoDepth,         nasR2L3Scape2LfoDepth,         engine_sp_ntf)
P_MAP(R2L3Scape1VelocityDepth,    nasR2L3Scape1VelocityDepth,    engine_sp_ntf)
P_MAP(R2L3Scape2VelocityDepth,    nasR2L3Scape2VelocityDepth,    engine_sp_ntf)
P_MAP(R2L3ContourScape,           nasR2L3ContourScape,           engine_sp_ntf)


//
// Shaper 1 Par. Levels
//
//P_MAP(R1ResEnvA,                  nasR1ResEnvA,                  engine_sp_ntf)
//P_MAP(R1ResEnvD,                  nasR1ResEnvD,                  engine_sp_ntf)
//P_MAP(R1ResEnvS,                  nasR1ResEnvS,                  engine_sp_ntf)
//P_MAP(R1ResEnvR,                  nasR1ResEnvR,                  engine_sp_ntf)
P_MAP(R1ResEnvMode,               nasR1ResEnvMode,               engine_sp_ntf)
P_MAP(R1ParaEnvVelocityDepth,     nasR1ParaEnvVelocityDepth,     engine_sp_ntf)

P_MAP(R1L1Scape1EnvDepth,         nasR1L1Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R1L1Scape2EnvDepth,         nasR1L1Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R1L1Sphere1EnvDepth,        nasR1L1Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R1L1Sphere2EnvDepth,        nasR1L1Sphere2EnvDepth,        engine_sp_ntf)
P_MAP(R1L2Scape1EnvDepth,         nasR1L2Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R1L2Scape2EnvDepth,         nasR1L2Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R1L2Sphere1EnvDepth,        nasR1L2Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R1L2Sphere2EnvDepth,        nasR1L2Sphere2EnvDepth,        engine_sp_ntf)
P_MAP(R1L3Scape1EnvDepth,         nasR1L3Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R1L3Scape2EnvDepth,         nasR1L3Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R1L3Sphere1EnvDepth,        nasR1L3Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R1L3Sphere2EnvDepth,        nasR1L3Sphere2EnvDepth,        engine_sp_ntf)


//
// Shaper 1 Amp
//
//P_MAP(R1AmpEnvA,                  nasR1AmpEnvA,                  engine_sp_ntf)
//P_MAP(R1AmpEnvD,                  nasR1AmpEnvD,                  engine_sp_ntf)
//P_MAP(R1AmpEnvS,                  nasR1AmpEnvS,                  engine_sp_ntf)
//P_MAP(R1AmpEnvR,                  nasR1AmpEnvR,                  engine_sp_ntf)
P_MAP(R1AmpEnvMode,               nasR1AmpEnvMode,               engine_sp_ntf)


//
// Shaper 1 Free ADSR
//
//P_MAP(R1FreeEnvA,                 nasR1FreeEnvA,                 engine_sp_ntf)
//P_MAP(R1FreeEnvD,                 nasR1FreeEnvD,                 engine_sp_ntf)
//P_MAP(R1FreeEnvS,                 nasR1FreeEnvS,                 engine_sp_ntf)
//P_MAP(R1FreeEnvR,                 nasR1FreeEnvR,                 engine_sp_ntf)
P_MAP(R1FreeEnvMode,              nasR1FreeEnvMode,              engine_sp_ntf)
P_MAP(R1FreeEnvDepth,             nasR1FreeEnvDepth,             engine_sp_ntf)
P_MAP(FreeADSR1VelocityDepth,     nasFreeADSR1VelocityDepth,     engine_sp_ntf)


//
// Shaper 2 Par. Levels
//
//P_MAP(R2ResEnvA,                  nasR2ResEnvA,                  engine_sp_ntf)
//P_MAP(R2ResEnvD,                  nasR2ResEnvD,                  engine_sp_ntf)
//P_MAP(R2ResEnvS,                  nasR2ResEnvS,                  engine_sp_ntf)
//P_MAP(R2ResEnvR,                  nasR2ResEnvR,                  engine_sp_ntf)
P_MAP(R2ResEnvMode,               nasR2ResEnvMode,               engine_sp_ntf)
P_MAP(R2ParaEnvVelocityDepth,     nasR2ParaEnvVelocityDepth,     engine_sp_ntf)

P_MAP(R2L1Scape1EnvDepth,         nasR2L1Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R2L1Scape2EnvDepth,         nasR2L1Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R2L1Sphere1EnvDepth,        nasR2L1Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R2L1Sphere2EnvDepth,        nasR2L1Sphere2EnvDepth,        engine_sp_ntf)
P_MAP(R2L2Scape1EnvDepth,         nasR2L2Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R2L2Scape2EnvDepth,         nasR2L2Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R2L2Sphere1EnvDepth,        nasR2L2Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R2L2Sphere2EnvDepth,        nasR2L2Sphere2EnvDepth,        engine_sp_ntf)
P_MAP(R2L3Scape1EnvDepth,         nasR2L3Scape1EnvDepth,         engine_sp_ntf)
P_MAP(R2L3Scape2EnvDepth,         nasR2L3Scape2EnvDepth,         engine_sp_ntf)
P_MAP(R2L3Sphere1EnvDepth,        nasR2L3Sphere1EnvDepth,        engine_sp_ntf)
P_MAP(R2L3Sphere2EnvDepth,        nasR2L3Sphere2EnvDepth,        engine_sp_ntf)


//
// Shaper 2 Amp
//
//P_MAP(R2AmpEnvA,                  nasR2AmpEnvA,                  engine_sp_ntf)
//P_MAP(R2AmpEnvD,                  nasR2AmpEnvD,                  engine_sp_ntf)
//P_MAP(R2AmpEnvS,                  nasR2AmpEnvS,                  engine_sp_ntf)
//P_MAP(R2AmpEnvR,                  nasR2AmpEnvR,                  engine_sp_ntf)
P_MAP(R2AmpEnvMode,               nasR2AmpEnvMode,               engine_sp_ntf)


//
// Shaper 2 Free ADSR
//
//P_MAP(R2FreeEnvA,                 nasR2FreeEnvA,                 engine_sp_ntf)
//P_MAP(R2FreeEnvD,                 nasR2FreeEnvD,                 engine_sp_ntf)
//P_MAP(R2FreeEnvS,                 nasR2FreeEnvS,                 engine_sp_ntf)
//P_MAP(R2FreeEnvR,                 nasR2FreeEnvR,                 engine_sp_ntf)
P_MAP(R2FreeEnvMode,              nasR2FreeEnvMode,              engine_sp_ntf)
P_MAP(R2FreeEnvDepth,             nasR2FreeEnvDepth,             engine_sp_ntf)
P_MAP(FreeADSR2VelocityDepth,     nasFreeADSR2VelocityDepth,     engine_sp_ntf)



//
// Shaper 1/2 Free 4 Level / 4 Time
//
P_MAP(FreeEnvLevel1,              nasFreeEnvLevel1,              engine_sp_ntf)
P_MAP(FreeEnvLevel2,              nasFreeEnvLevel2,              engine_sp_ntf)
P_MAP(FreeEnvLevel3,              nasFreeEnvLevel3,              engine_sp_ntf)
P_MAP(FreeEnvLevel4,              nasFreeEnvLevel4,              engine_sp_ntf)
P_MAP(FreeEnvTime1,               nasFreeEnvTime1,               engine_sp_ntf)
P_MAP(FreeEnvTime2,               nasFreeEnvTime2,               engine_sp_ntf)
P_MAP(FreeEnvTime3,               nasFreeEnvTime3,               engine_sp_ntf)
P_MAP(FreeEnvTime4,               nasFreeEnvTime4,               engine_sp_ntf)
P_MAP(TLFreeEnvMode,              nasTLFreeEnvMode,              engine_sp_ntf)
P_MAP(TLFreeEnvDepth,             nasTLFreeEnvDepth,             engine_sp_ntf)
P_MAP(Free4Level4TimeVelocityDepth, nasFree4Level4TimeVelocityDepth, engine_sp_ntf)


//
// Shaper 1/2 General
//
P_MAP(FreeEnvType,                nasFreeEnvType,                engine_sp_ntf)



//
// -- Mod/LFO
//
P_MAP(LFOSwitch,                  nasLFOSwitch,                  engine_sp_ntf)
//P_MAP(LFODepth,                   nasLFODepth,                   engine_sp_ntf)
//P_MAP(LFORate,                    nasLFORate,                    engine_sp_ntf)
P_MAP(LFODelay,                   nasLFODelay,                   engine_sp_ntf)
P_MAP(LFOWaveForm,                nasLFOWaveForm,                engine_sp_ntf)

//
// -- Blender
//
P_MAP(BlenderType,                nasBlenderType,                engine_sp_ntf)
//P_MAP(BlenderAmount,              nasBlenderAmount,              engine_sp_ntf)
P_MAP(BlenderLfoDepth,            nasBlenderLfoDepth,            engine_sp_ntf)
P_MAP(BlenderFreeADSR1Depth,      nasBlenderFreeADSR1Depth,      engine_sp_ntf)
P_MAP(BlenderFreeADSR2Depth,      nasBlenderFreeADSR2Depth,      engine_sp_ntf)
P_MAP(BlenderFree4L4TDepth,       nasBlenderFree4L4TDepth,       engine_sp_ntf)

//
// -- Slicer
//
P_MAP(SlicerSwitchType,           nasSlicerSwitchType,           engine_sp_ntf)
//P_MAP(SlicerDepth,                nasSlicerDepth,                engine_sp_ntf)
//P_MAP(SlicerRate,                 nasSlicerRate,                 engine_sp_ntf)
P_MAP(SlicerWaveForm,             nasSlicerWaveForm,             engine_sp_ntf)




//
// -- Silver Filter
//
P_MAP(FilterType,                 nasFilterType,                 engine_sp_ntf)
//P_MAP(FilterFreq,                 nasFilterFreq,                 engine_sp_ntf)
//P_MAP(FilterReso,                 nasFilterReso,                 engine_sp_ntf)
P_MAP(FilterLfoDepth,             nasFilterLfoDepth,             engine_sp_ntf)
P_MAP(FilterKeyTrack,             nasFilterKeyTrack,             engine_sp_ntf)
P_MAP(FilterCutoffVelocityDepth,  nasFilterCutoffVelocityDepth,  engine_sp_ntf)
P_MAP(SilverL1Contour,            nasFilterContour,              engine_sp_ntf)

//
// Shaper 3
//
//P_MAP(FilterEnvA,                 nasFilterEnvA,                 engine_sp_ntf)
//P_MAP(FilterEnvD,                 nasFilterEnvD,                 engine_sp_ntf)
//P_MAP(FilterEnvS,                 nasFilterEnvS,                 engine_sp_ntf)
//P_MAP(FilterEnvR,                 nasFilterEnvR,                 engine_sp_ntf)
P_MAP(FilterEnvMode,              nasFilterEnvMode,              engine_sp_ntf)
P_MAP(FilterEnvDepth,             nasFilterEnvDepth,             engine_sp_ntf)
P_MAP(FilterEnvVelocityDepth,     nasFilterEnvVelocityDepth,     engine_sp_ntf)


//
// -- Silver General
//
P_MAP(SilverSwitch,               nasSilverSwitch,               engine_sp_ntf)

//
// Silver Freq FX
//
P_MAP(FreqFXSwitch,               nasFreqFXSwitch,               engine_sp_ntf)
P_MAP(CurFreqFX,                  nasCurFreqFX,                  engine_sp_ntf)
P_MAP(SilverL2Contour,            nasFreqFXContour,              engine_sp_ntf)

// --- EQ/Compressor
P_MAP(EQ_Switch,                  nasEQ_Switch,                  engine_sp_ntf)
P_MAP(EQ_LowShelfSwitch,          nasEQ_LowShelfSwitch,          engine_sp_ntf)
P_MAP(EQ_LowShelfGain,            nasEQ_LowShelfGain,            engine_sp_ntf)
P_MAP(EQ_LowShelfFreq,            nasEQ_LowShelfFreq,            engine_sp_ntf)
P_MAP(EQ_LowShelfSlope,           nasEQ_LowShelfSlope,           engine_sp_ntf)
P_MAP(EQ_Band1Switch,             nasEQ_Band1Switch,             engine_sp_ntf)
P_MAP(EQ_Band1Gain,               nasEQ_Band1Gain,               engine_sp_ntf)
P_MAP(EQ_Band1Freq,               nasEQ_Band1Freq,               engine_sp_ntf)
P_MAP(EQ_Band1Q,                  nasEQ_Band1Q,                  engine_sp_ntf)
P_MAP(EQ_Band2Switch,             nasEQ_Band2Switch,             engine_sp_ntf)
P_MAP(EQ_Band2Gain,               nasEQ_Band2Gain,               engine_sp_ntf)
P_MAP(EQ_Band2Freq,               nasEQ_Band2Freq,               engine_sp_ntf)
P_MAP(EQ_Band2Q,                  nasEQ_Band2Q,                  engine_sp_ntf)
P_MAP(EQ_HighShelfSwitch,         nasEQ_HighShelfSwitch,         engine_sp_ntf)
P_MAP(EQ_HighShelfGain,           nasEQ_HighShelfGain,           engine_sp_ntf)
P_MAP(EQ_HighShelfFreq,           nasEQ_HighShelfFreq,           engine_sp_ntf)
P_MAP(EQ_HighShelfSlope,          nasEQ_HighShelfSlope,          engine_sp_ntf)

P_MAP(CR_Switch,                  nasCR_Switch,                  engine_sp_ntf)
P_MAP(CR_Threshold,               nasCR_Threshold,               engine_sp_ntf)
P_MAP(CR_OutGain,                 nasCR_OutGain,                 engine_sp_ntf)
P_MAP(CR_Responsiveness,          nasCR_Responsiveness,          engine_sp_ntf)



// --- Distortion
P_MAP(DS_InGain,                  nasDS_InGain,                  engine_sp_ntf)
P_MAP(DS_PreFilter,               nasDS_PreFilter,               engine_sp_ntf)
P_MAP(DS_ClipCurveType,           nasDS_ClipCurveType,           engine_sp_ntf)
P_MAP(DS_OutGain,                 nasDS_OutGain,                 engine_sp_ntf)

// --- Ring Modulator
P_MAP(RM_Mix,                     nasRM_Mix,                     engine_sp_ntf)
P_MAP(RM_Speed,                   nasRM_Speed,                   engine_sp_ntf)
P_MAP(RM_Depth,                   nasRM_Depth,                   engine_sp_ntf)
P_MAP(RM_WaveForm,                nasRM_WaveForm,                engine_sp_ntf)
P_MAP(RM_ModFreq,                 nasRM_ModFreq,                 engine_sp_ntf)
P_MAP(RM_XoverDelay,              nasRM_XoverDelay,              engine_sp_ntf)
P_MAP(RM_XoverTime,               nasRM_XoverTime,               engine_sp_ntf)
P_MAP(RM_XoverDelayFeedback,      nasRM_XoverDelayFeedback,      engine_sp_ntf)


// --- Sp_warp
P_MAP(SW_Mix,                     nasSW_Mix,                     engine_sp_ntf)
P_MAP(SW_Frequency,               nasSW_Frequency,               engine_sp_ntf)
P_MAP(SW_Tilt,                    nasSW_Tilt,                    engine_sp_ntf)
P_MAP(SW_Damping,                 nasSW_Damping,                 engine_sp_ntf)
P_MAP(SW_Speed,                   nasSW_Speed,                   engine_sp_ntf)
P_MAP(SW_Depth,                   nasSW_Depth,                   engine_sp_ntf)

// --- Decimator
P_MAP(DC_Mix,                     nasDC_Mix,                     engine_sp_ntf)
P_MAP(DC_SHFactor,                nasDC_SHFactor,                engine_sp_ntf)
P_MAP(DC_PreFilterCutoff,         nasDC_PreFilterCutoff,         engine_sp_ntf)


//
// Silver Time FX
//
P_MAP(TimeFXSwitch,               nasTimeFXSwitch,               engine_sp_ntf)
P_MAP(CurTimeFX,                  nasCurTimeFX,                  engine_sp_ntf)
P_MAP(SilverL3Contour,            nasTimeFXContour,              engine_sp_ntf)

// --- Stereo Spread
P_MAP(SS_ChanDelay,               nasSS_ChanDelay,               engine_sp_ntf)
P_MAP(SS_Feedback,                nasSS_Feedback,                engine_sp_ntf)

// --- L/R Delay
P_MAP(LRD_Mix,                    nasLRD_Mix,                    engine_sp_ntf)
P_MAP(LRD_Time,                   nasLRD_Time,                   engine_sp_ntf)
P_MAP(LRD_Feedback,               nasLRD_Feedback,               engine_sp_ntf)

// --- Flanger
P_MAP(FL_Mix,                     nasFL_Mix,                     engine_sp_ntf)
P_MAP(FL_Depth,                   nasFL_Depth,                   engine_sp_ntf)
P_MAP(FL_Speed,                   nasFL_Speed,                   engine_sp_ntf)
P_MAP(FL_WaveForm,                nasFL_WaveForm,                engine_sp_ntf)
P_MAP(FL_Feedback,                nasFL_Feedback,                engine_sp_ntf)
P_MAP(FL_StereoPhase,             nasFL_StereoPhase,             engine_sp_ntf)


// --- Phaser
P_MAP(PH_Mix,                     nasPH_Mix,                     engine_sp_ntf)
P_MAP(PH_Depth,                   nasPH_Depth,                   engine_sp_ntf)
P_MAP(PH_Speed,                   nasPH_Speed,                   engine_sp_ntf)
P_MAP(PH_WaveForm,                nasPH_WaveForm,                engine_sp_ntf)
P_MAP(PH_Feedback,                nasPH_Feedback,                engine_sp_ntf)
P_MAP(PH_StereoPhase,             nasPH_StereoPhase,             engine_sp_ntf)

// --- Chorus
P_MAP(CH_Mix,                     nasCH_Mix,                     engine_sp_ntf)
P_MAP(CH_Depth,                   nasCH_Depth,                   engine_sp_ntf)
P_MAP(CH_Speed,                   nasCH_Speed,                   engine_sp_ntf)
P_MAP(CH_WaveForm,                nasCH_WaveForm,                engine_sp_ntf)
P_MAP(CH_Feedback,                nasCH_Feedback,                engine_sp_ntf)
P_MAP(CH_StereoPhase,             nasCH_StereoPhase,             engine_sp_ntf)
P_MAP(CH_PreDelay,                nasCH_PreDelay,                engine_sp_ntf)


//
// Master Effects: Sound Level (note: uses effects notifier list)
//
P_MAP(SoundMFXSwitch,             nasMFXSwitch,                  engine_ep_ntf) 

P_MAP(SoundMFXDelaySwitch,        nasMFXDelaySwitch,             engine_ep_ntf) 
P_MAP(SoundMFXDelayLTime,         nasMFXDelayLTime,              engine_ep_ntf) 
P_MAP(SoundMFXDelayRTime,         nasMFXDelayRTime,              engine_ep_ntf) 
P_MAP(SoundMFXDelayFeedback,      nasMFXDelayFeedback,           engine_ep_ntf) 
P_MAP(SoundMFXDelayFdbkDamp,      nasMFXDelayFdbkDamp,           engine_ep_ntf) 

P_MAP(SoundMFXReverbSwitch,       nasMFXReverbSwitch,            engine_ep_ntf) 
P_MAP(SoundMFXReverbRoom,         nasMFXReverbRoom,              engine_ep_ntf)
P_MAP(SoundMFXRevDecayTime,       nasMFXRevDecayTime,            engine_ep_ntf) 
P_MAP(SoundMFXRevDiffusion,       nasMFXRevDiffusion,            engine_ep_ntf) 
P_MAP(SoundMFXRevHFDamp,          nasMFXRevHFDamp,               engine_ep_ntf) 
P_MAP(SoundMFXRevDetune,          nasMFXRevDetune,               engine_ep_ntf) 
P_MAP(SoundMFXRevSpeed,           nasMFXRevSpeed,                engine_ep_ntf) 

#undef P_MAP
#endif

#ifdef SUP_MAP

//
// Master Effects: SetUp Level (note: same targets and notifier list as sound level)
//

// NOTE: The notifiers have to be removed from the sound level when we're in SetUp mode. 

SUP_MAP(MFXSwitch,                nasMFXSwitch,                  engine_ep_ntf) 

SUP_MAP(MFXDelaySwitch,           nasMFXDelaySwitch,             engine_ep_ntf) 
SUP_MAP(MFXDelayLTime,            nasMFXDelayLTime,              engine_ep_ntf) 
SUP_MAP(MFXDelayRTime,            nasMFXDelayRTime,              engine_ep_ntf) 
SUP_MAP(MFXDelayFeedback,         nasMFXDelayFeedback,           engine_ep_ntf) 
SUP_MAP(MFXDelayFdbkDamp,         nasMFXDelayFdbkDamp,           engine_ep_ntf) 

SUP_MAP(MFXReverbSwitch,          nasMFXReverbSwitch,            engine_ep_ntf) 
SUP_MAP(MFXReverbRoom,            nasMFXReverbRoom,              engine_ep_ntf)
SUP_MAP(MFXRevDecayTime,          nasMFXRevDecayTime,            engine_ep_ntf) 
SUP_MAP(MFXRevDiffusion,          nasMFXRevDiffusion,            engine_ep_ntf) 
SUP_MAP(MFXRevHFDamp,             nasMFXRevHFDamp,               engine_ep_ntf) 
SUP_MAP(MFXRevDetune,             nasMFXRevDetune,               engine_ep_ntf) 
SUP_MAP(MFXRevSpeed,              nasMFXRevSpeed,                engine_ep_ntf) 

#undef SUP_MAP
#endif


//
// CC-Modulated Sound Parameters
//

#ifdef M_MAP
M_MAP(R1Volume,           cvd_R1Volume,      nasR1Volume,          engine_sp_ntf)
M_MAP(R1Semi,             cvd_R1Detune,      nasR1Semi,            engine_sp_ntf)
M_MAP(R1L1Scape1Value,    cvd_R1L1Scape1,    nasR1L1Scape1Value,   engine_sp_ntf)
M_MAP(R1L1Scape2Value,    cvd_R1L1Scape2,    nasR1L1Scape2Value,   engine_sp_ntf)
M_MAP(R1L1Sphere1Value,   cvd_R1L1Sphere1,   nasR1L1Sphere1Value,  engine_sp_ntf)
M_MAP(R1L1Sphere2Value,   cvd_R1L1Sphere2,   nasR1L1Sphere2Value,  engine_sp_ntf)
M_MAP(R1L2Scape1Value,    cvd_R1L2Scape1,    nasR1L2Scape1Value,   engine_sp_ntf)
M_MAP(R1L2Scape2Value,    cvd_R1L2Scape2,    nasR1L2Scape2Value,   engine_sp_ntf)
M_MAP(R1L2Sphere1Value,   cvd_R1L2Sphere1,   nasR1L2Sphere1Value,  engine_sp_ntf)
M_MAP(R1L2Sphere2Value,   cvd_R1L2Sphere2,   nasR1L2Sphere2Value,  engine_sp_ntf)
M_MAP(R1L3Scape1Value,    cvd_R1L3Scape1,    nasR1L3Scape1Value,   engine_sp_ntf)
M_MAP(R1L3Scape2Value,    cvd_R1L3Scape2,    nasR1L3Scape2Value,   engine_sp_ntf)
M_MAP(R1L3Sphere1Value,   cvd_R1L3Sphere1,   nasR1L3Sphere1Value,  engine_sp_ntf)
M_MAP(R1L3Sphere2Value,   cvd_R1L3Sphere2,   nasR1L3Sphere2Value,  engine_sp_ntf)

M_MAP(R2Volume,           cvd_R2Volume,      nasR2Volume,          engine_sp_ntf)
M_MAP(R2Semi,             cvd_R2Detune,      nasR2Semi,            engine_sp_ntf)
M_MAP(R2L1Scape1Value,    cvd_R2L1Scape1,    nasR2L1Scape1Value,   engine_sp_ntf)
M_MAP(R2L1Scape2Value,    cvd_R2L1Scape2,    nasR2L1Scape2Value,   engine_sp_ntf)
M_MAP(R2L1Sphere1Value,   cvd_R2L1Sphere1,   nasR2L1Sphere1Value,  engine_sp_ntf)
M_MAP(R2L1Sphere2Value,   cvd_R2L1Sphere2,   nasR2L1Sphere2Value,  engine_sp_ntf)
M_MAP(R2L2Scape1Value,    cvd_R2L2Scape1,    nasR2L2Scape1Value,   engine_sp_ntf)
M_MAP(R2L2Scape2Value,    cvd_R2L2Scape2,    nasR2L2Scape2Value,   engine_sp_ntf)
M_MAP(R2L2Sphere1Value,   cvd_R2L2Sphere1,   nasR2L2Sphere1Value,  engine_sp_ntf)
M_MAP(R2L2Sphere2Value,   cvd_R2L2Sphere2,   nasR2L2Sphere2Value,  engine_sp_ntf)
M_MAP(R2L3Scape1Value,    cvd_R2L3Scape1,    nasR2L3Scape1Value,   engine_sp_ntf)
M_MAP(R2L3Scape2Value,    cvd_R2L3Scape2,    nasR2L3Scape2Value,   engine_sp_ntf)
M_MAP(R2L3Sphere1Value,   cvd_R2L3Sphere1,   nasR2L3Sphere1Value,  engine_sp_ntf)
M_MAP(R2L3Sphere2Value,   cvd_R2L3Sphere2,   nasR2L3Sphere2Value,  engine_sp_ntf)

M_MAP(R1ResEnvA,          cvd_Res1EnvA,      nasR1ResEnvA,         engine_sp_ntf)
M_MAP(R1ResEnvD,          cvd_Res1EnvD,      nasR1ResEnvD,         engine_sp_ntf)
M_MAP(R1ResEnvS,          cvd_Res1EnvS,      nasR1ResEnvS,         engine_sp_ntf)
M_MAP(R1ResEnvR,          cvd_Res1EnvR,      nasR1ResEnvR,         engine_sp_ntf)
M_MAP(R1AmpEnvA,          cvd_Amp1EnvA,      nasR1AmpEnvA,         engine_sp_ntf)
M_MAP(R1AmpEnvD,          cvd_Amp1EnvD,      nasR1AmpEnvD,         engine_sp_ntf)
M_MAP(R1AmpEnvS,          cvd_Amp1EnvS,      nasR1AmpEnvS,         engine_sp_ntf)
M_MAP(R1AmpEnvR,          cvd_Amp1EnvR,      nasR1AmpEnvR,         engine_sp_ntf)
M_MAP(R1FreeEnvA,         cvd_Free1EnvA,     nasR1FreeEnvA,        engine_sp_ntf)
M_MAP(R1FreeEnvD,         cvd_Free1EnvD,     nasR1FreeEnvD,        engine_sp_ntf)
M_MAP(R1FreeEnvS,         cvd_Free1EnvS,     nasR1FreeEnvS,        engine_sp_ntf)
M_MAP(R1FreeEnvR,         cvd_Free1EnvR,     nasR1FreeEnvR,        engine_sp_ntf)

M_MAP(R2ResEnvA,          cvd_Res2EnvA,      nasR2ResEnvA,         engine_sp_ntf)
M_MAP(R2ResEnvD,          cvd_Res2EnvD,      nasR2ResEnvD,         engine_sp_ntf)
M_MAP(R2ResEnvS,          cvd_Res2EnvS,      nasR2ResEnvS,         engine_sp_ntf)
M_MAP(R2ResEnvR,          cvd_Res2EnvR,      nasR2ResEnvR,         engine_sp_ntf)
M_MAP(R2AmpEnvA,          cvd_Amp2EnvA,      nasR2AmpEnvA,         engine_sp_ntf)
M_MAP(R2AmpEnvD,          cvd_Amp2EnvD,      nasR2AmpEnvD,         engine_sp_ntf)
M_MAP(R2AmpEnvS,          cvd_Amp2EnvS,      nasR2AmpEnvS,         engine_sp_ntf)
M_MAP(R2AmpEnvR,          cvd_Amp2EnvR,      nasR2AmpEnvR,         engine_sp_ntf)
M_MAP(R2FreeEnvA,         cvd_Free2EnvA,     nasR2FreeEnvA,        engine_sp_ntf)
M_MAP(R2FreeEnvD,         cvd_Free2EnvD,     nasR2FreeEnvD,        engine_sp_ntf)
M_MAP(R2FreeEnvS,         cvd_Free2EnvS,     nasR2FreeEnvS,        engine_sp_ntf)
M_MAP(R2FreeEnvR,         cvd_Free2EnvR,     nasR2FreeEnvR,        engine_sp_ntf)

M_MAP(FilterEnvA,         cvd_FilterEnvA,    nasFilterEnvA,        engine_sp_ntf)
M_MAP(FilterEnvD,         cvd_FilterEnvD,    nasFilterEnvD,        engine_sp_ntf)
M_MAP(FilterEnvS,         cvd_FilterEnvS,    nasFilterEnvS,        engine_sp_ntf)
M_MAP(FilterEnvR,         cvd_FilterEnvR,    nasFilterEnvR,        engine_sp_ntf)

M_MAP(BlenderAmount,      cvd_BlenderAmount, nasBlenderAmount,     engine_sp_ntf)

M_MAP(SlicerDepth,        cvd_SlicerDepth,   nasSlicerDepth,       engine_sp_ntf)
M_MAP(SlicerRate,         cvd_SlicerRate,    nasSlicerRate,        engine_sp_ntf)

M_MAP(LFODepth,           cvd_LFODepth,      nasLFODepth,          engine_sp_ntf)
M_MAP(LFORate,            cvd_LFORate,       nasLFORate,           engine_sp_ntf)

M_MAP(FilterFreq,         cvd_FilterFreq,    nasFilterFreq,        engine_sp_ntf)
M_MAP(FilterReso,         cvd_FilterReso,    nasFilterReso,        engine_sp_ntf)

#undef M_MAP
#endif


///////////////////////////////////////////////////////////////////////////////
//
// $Log: MapToEngineDef.h,v $
// Revision 1.2  2004/11/02 13:08:17  joffe
// modulation-matrix added
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
