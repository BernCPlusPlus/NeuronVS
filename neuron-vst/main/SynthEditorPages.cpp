///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthEditorPages.cpp,v $
// $Revision: 1.5 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "SynthEditor.h"


///////////////////////////////////////////////////////////////////////////////
// part 1of3: single page info
// this is const-data for a page and its according controls or subpages.
// first int is the bitmap-resource or 0, then the control-ids with -1 as
// end of list. a -1 as control-id ends the page

static const long cPageResys[] =
{
	kBgndResys, kBranchR1Level,kBranchR2Level, -1,
	
	CID_SWITCH,
    kSwitchMpResys, kSwitchMpSilver, kSwitchMpRemote, kSwitchMpAboutOff, -4,
    kSwitchMpSndUp,kSwitchMpSndDn,-2,
    kSwitchMpSndSave,
	
    kSwitchR1Switch,
    kSwitchR1Record, kSwitchR1ParamLevel, kSwitchR1Type,
    kSwitchR1CtxStickPb, kSwitchR1CtxContour, -2,
    kSwitchR1OctavM2, kSwitchR1OctavM1,
    kSwitchR1OctavP0, kSwitchR1OctavP1, -4, 
    kSwitchR1CtxSelectXY,
	
    kSwitchR2Switch,
    kSwitchR2Record, kSwitchR2ParamLevel, kSwitchR2Type,
    kSwitchR2CtxStickPb, kSwitchR2CtxContour, -2,
    kSwitchR2OctavM2, kSwitchR2OctavM1,
    kSwitchR2OctavP0, kSwitchR2OctavP1, -4,
    kSwitchR2CtxSelectXY,
	
    kSwitchShaper12CtxMode,
    -1,
	
	CID_DISPLAY,
    kDisplaySoundNumber,kDisplaySoundName,
    kDisplayR1ModelNumber,kDisplayR1ModelName,
    kDisplayR2ModelNumber,kDisplayR2ModelName,
    -1,
	
	CID_SCROLL,
    kScrollerR1AmpLfoDepth, kScrollerR1AmpKeyTrack, kScrollerR1VolumeVelocityDepth,
    kScrollerR1ModelSizeKeyTrack, kScrollerR1ModelSizeOffset, kScrollerR1ModelVelocitySwitch,    
    kScrollerR1Semi, kScrollerR1Cents, kScrollerR1PitchLfoDepth, kScrollerR1PitchKeyTrack, 
    kScrollerR1FreeADSR1PitchDepth, kScrollerR1FreeADSR2PitchDepth, 
	
    kScrollerR2AmpLfoDepth, kScrollerR2AmpKeyTrack, kScrollerR2VolumeVelocityDepth,
    kScrollerR2ModelSizeKeyTrack, kScrollerR2ModelSizeOffset, kScrollerR2ModelVelocitySwitch,
    kScrollerR2Semi, kScrollerR2Cents, kScrollerR2PitchLfoDepth, kScrollerR2PitchKeyTrack, 
    kScrollerR2FreeADSR1PitchDepth, kScrollerR2FreeADSR2PitchDepth, 
	
    kScrollerBlenderAmount, kScrollerBlenderLfoDepth,
    kScrollerBlenderFreeADSR1Depth,kScrollerBlenderFreeADSR2Depth, 
    
    kScrollerShaper1ParamVeloDepth, kScrollerShaper1FreeVeloDepth,
    kScrollerShaper1FreeDepth,
    kScrollerShaper2ParamVeloDepth, kScrollerShaper2FreeVeloDepth,
    kScrollerShaper2FreeDepth,
	
    kScrollerShaper12CtxA,kScrollerShaper12CtxD,
    kScrollerShaper12CtxS,kScrollerShaper12CtxR,
    -1,
	
	CID_STICK,
    kStickR1, kStickR2,
    -1,
	
	CID_DIAL,
    kDialR1Volume, kDialR2Volume,
    -1,
	
	CID_SHAPER,
    kShaper1Resy,kShaper1Amp,kShaper1Free,
    kShaper2Resy,kShaper2Amp,kShaper2Free,-6,
    -1,
	
	CID_DROPDOWN,
    kDropdownMpSndLoad,kDropdownMpSndSaveAs,
    kDropdownR1ModelSelect,kDropdownR2ModelSelect,
    kDropdownBlenderType,
    -1,
	
	CID_AREA,
    kAreaAbout,
    -1,
	
	-1
};

static const long cPageR1Level1[] =
{
	kBgndRes1Lvl1, -1,
	
	CID_SCROLL,
    kScrollerR1CtxLfoDepth, kScrollerR1CtxKeyTrack,
    kScrollerR1CtxVelDepth, kScrollerR1CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageR1Level2[] =
{
	kBgndRes1Lvl2, -1,
	
	CID_SCROLL,
    kScrollerR1CtxLfoDepth, kScrollerR1CtxKeyTrack,
    kScrollerR1CtxVelDepth, kScrollerR1CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageR1Level3[] =
{
	kBgndRes1Lvl3, -1,
	
	CID_SCROLL,
    kScrollerR1CtxLfoDepth, kScrollerR1CtxKeyTrack,
    kScrollerR1CtxVelDepth, kScrollerR1CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageR2Level1[] =
{
	kBgndRes2Lvl1, -1,
	
	CID_SCROLL,
    kScrollerR2CtxLfoDepth, kScrollerR2CtxKeyTrack,
    kScrollerR2CtxVelDepth, kScrollerR2CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageR2Level2[] =
{
	kBgndRes2Lvl2, -1,
	
	CID_SCROLL,
    kScrollerR2CtxLfoDepth, kScrollerR2CtxKeyTrack,
    kScrollerR2CtxVelDepth, kScrollerR2CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageR2Level3[] =
{
	kBgndRes2Lvl3, -1,
	
	CID_SCROLL,
    kScrollerR2CtxLfoDepth, kScrollerR2CtxKeyTrack,
    kScrollerR2CtxVelDepth, kScrollerR2CtxEnvDepth, -4,
    -1,
	
	-1
};

static const long cPageSilver[] =
{
	kBgndSilver, kBranchFreqfx,kBranchTimefx, -1,
	
	CID_SWITCH, 
    kSwitchMpResys, kSwitchMpSilver, kSwitchMpRemote, kSwitchMpAboutOff, -4,
    kSwitchMpSndUp,kSwitchMpSndDn,-2,
    kSwitchMpSndSave,
	
    kSwitchFfxSwitch,
    kSwitchFfxTypeEQComp, kSwitchFfxTypeDistortion, kSwitchFfxTypeRingMod,
    kSwitchFfxTypeDecimator, kSwitchFfxTypeSpWarp, -5,
    
    kSwitchTfxSwitch, 
    kSwitchTfxTypeStereoSpr, kSwitchTfxTypeLRDelay, kSwitchTfxTypeFlanger,
    kSwitchTfxTypePhaser, kSwitchTfxTypeChorus, -5,   
	
    kSwitchLfoSwitch, 
    kSwitchLfoWfTri, kSwitchLfoWfSine, kSwitchLfoWfSawUp,
    kSwitchLfoWfSawDown, kSwitchLfoWfSquare, kSwitchLfoWfPosTri,
    kSwitchLfoWfPosSine, kSwitchLfoWfPosSquare, kSwitchLfoWfStepTri,
    kSwitchLfoWfStepSawUp, kSwitchLfoWfStepSawDown,
    kSwitchLfoWfRandom, -12,    
    
    kSwitchSilverSwitch, 
    kSwitchSilverRecord, kSwitchSilverParamLevel,
    kSwitchSilverCtxStickPb, kSwitchSilverCtxContour, -2,
    kSwitchSlicerSwitch,
    
    kSwitchSlicerType,
    kSwitchSlicerWfTri, kSwitchSlicerWfSine, kSwitchSlicerWfSawUp,
    kSwitchSlicerWfSawDown, kSwitchSlicerWfSquare, kSwitchSlicerWfPosTri,
    kSwitchSlicerWfPosSine, kSwitchSlicerWfPosSquare, kSwitchSlicerWfStepTri,
    kSwitchSlicerWfStepSawUp, kSwitchSlicerWfStepSawDown,
    kSwitchSlicerWfRandom, -12,  
	
    kSwitchShaper3Mode,
    -1,
	
	CID_DISPLAY,
    kDisplaySoundNumber,kDisplaySoundName,
    -1,
	
	CID_SCROLL,
    kScrollerLfoDepth, kScrollerLfoRate, kScrollerLfoDelay,
    kScrollerFilterCutoff, kScrollerFilterResonance,
    kScrollerFilterLfoDepth, kScrollerFilterKeyTrack, kScrollerFilterVeloDepth, 
    kScrollerSlicerDepth, kScrollerSlicerRate, 
    kScrollerShaper3Depth, kScrollerShaper3VeloDepth,
    kScrollerShaper3A,kScrollerShaper3D,
    kScrollerShaper3S,kScrollerShaper3R,
    -1,
	
	CID_STICK,
    kStickSilver,
    -1,
	
	CID_SHAPER,
    kShaper3,
    -1,
	
	CID_DROPDOWN,
    kDropdownMpSndLoad,kDropdownMpSndSaveAs,
    kDropdownFilterType,
    -1,
	
	CID_AREA,
    kAreaAbout,
    -1,
	
	-1
};

static const long cPageEqcompr[] =
{
	-1, kBranchEqcompr, -1,
	-1  
};

static const long cPageEqshelfL[] =
{
	kBgndEqShelf, -1,
	
	CID_SWITCH,
    kSwitchFfxEQSwitch, kSwitchFfxEQLowSwitch,
    kSwitchFfxEQLowSub, kSwitchFfxEQBand1Sub,
    kSwitchFfxEQBand2Sub, kSwitchFfxEQHighSub, kSwitchFfxCRSub, -5,
    -1,
	
	CID_SCROLL,
    kScrollerFfxEQLowGain, kScrollerFfxEQLowFreq, kScrollerFfxEQLowSlope,
    -1,
	
	-1
};

static const long cPageEqband1[] =
{
	kBgndEqBand, -1,
	
	CID_SWITCH,
    kSwitchFfxEQSwitch, kSwitchFfxEQBand1Switch, 
    kSwitchFfxEQLowSub, kSwitchFfxEQBand1Sub,
    kSwitchFfxEQBand2Sub, kSwitchFfxEQHighSub, kSwitchFfxCRSub, -5,
    -1,
	
	CID_SCROLL,
    kScrollerFfxEQBand1Gain, kScrollerFfxEQBand1Freq, kScrollerFfxEQBand1Q,
    -1,
	
	-1
};

static const long cPageEqband2[] =
{
	kBgndEqBand, -1,
	
	CID_SWITCH,
    kSwitchFfxEQSwitch, kSwitchFfxEQBand2Switch, 
    kSwitchFfxEQLowSub, kSwitchFfxEQBand1Sub,
    kSwitchFfxEQBand2Sub, kSwitchFfxEQHighSub, kSwitchFfxCRSub, -5,
    -1,
	
	CID_SCROLL,
    kScrollerFfxEQBand2Gain, kScrollerFfxEQBand2Freq, kScrollerFfxEQBand2Q,
    -1,
	
	-1
};

static const long cPageEqshelfH[] =
{
	kBgndEqShelf, -1,
	
	CID_SWITCH,
    kSwitchFfxEQSwitch, kSwitchFfxEQHighSwitch, 
    kSwitchFfxEQLowSub, kSwitchFfxEQBand1Sub,
    kSwitchFfxEQBand2Sub, kSwitchFfxEQHighSub, kSwitchFfxCRSub, -5,
    -1,
	
	CID_SCROLL,
    kScrollerFfxEQHighGain, kScrollerFfxEQHighFreq, kScrollerFfxEQHighSlope,
    -1,
	
	-1
};

static const long cPageCompr[] =
{
	kBgndCompr, -1,
	
	CID_SWITCH,
    kSwitchFfxEQSwitch, kSwitchFfxCRSwitch, 
    kSwitchFfxEQLowSub, kSwitchFfxEQBand1Sub,
    kSwitchFfxEQBand2Sub, kSwitchFfxEQHighSub, kSwitchFfxCRSub, -5,
    -1,
	
	CID_SCROLL,
    kScrollerFfxCRThreshold, kScrollerFfxCROutGain, kScrollerFfxCRReponsiveness,
    -1,
	
	-1
};

static const long cPageDistort[] =
{
	kBgndDistort, -1,
	
	CID_SWITCH,
    kSwitchFfxDSClipChop, kSwitchFfxDSClipLin, kSwitchFfxDSClipRipple,
    kSwitchFfxDSClipSoftKnee, kSwitchFfxDSClipSigmoid,
    kSwitchFfxDSClipExp, -6,
    -1,
	
	CID_SCROLL,
    kScrollerFfxDSInDrive, kScrollerFfxDSPreFilter, kScrollerFfxDSOutVolume,
    -1,
	
	-1
};

static const long cPageRingmod[] =
{
	-1, kBranchRingmod,-1,
	-1  
};

static const long cPageRingmod1[] =
{
	kBgndRingMod1, -1,
	
	CID_SWITCH,
    kSwitchFfxRMSub1, kSwitchFfxRMSub2, -2,
    kSwitchFfxRMWfTri, kSwitchFfxRMWfSine, kSwitchFfxRMWfSawUp,
    kSwitchFfxRMWfSawDown, kSwitchFfxRMWfSquare,  kSwitchFfxRMWfPosTri,
    kSwitchFfxRMWfPosSine, kSwitchFfxRMWfPosSquare, kSwitchFfxRMWfStepTri,
    kSwitchFfxRMWfStepSawUp, kSwitchFfxRMWfStepSawDown,
    kSwitchFfxRMWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerFfxRMMix, kScrollerFfxRMModFreq, kScrollerFfxRMSpeed, kScrollerFfxRMDepth,
    -1,
	
	-1
};

static const long cPageRingmod2[] =
{
	kBgndRingMod2, -1,
	
	CID_SWITCH,
    kSwitchFfxRMSub1, kSwitchFfxRMSub2, -2,
    kSwitchFfxRMWfTri, kSwitchFfxRMWfSine, kSwitchFfxRMWfSawUp,
    kSwitchFfxRMWfSawDown, kSwitchFfxRMWfSquare,  kSwitchFfxRMWfPosTri,
    kSwitchFfxRMWfPosSine, kSwitchFfxRMWfPosSquare, kSwitchFfxRMWfStepTri,
    kSwitchFfxRMWfStepSawUp, kSwitchFfxRMWfStepSawDown,
    kSwitchFfxRMWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerFfxRMXoverDelay, kScrollerFfxRMXoverTime, kScrollerFfxRMXoverFeedbk,
    -1,
	
	-1
};

static const long cPageDecimat[] =
{
	kBgndDecimat, -1,
	
	CID_SCROLL,
    kScrollerFfxDCMix, kScrollerFfxDCSHFactor, kScrollerFfxDCPreFilter,
    -1,
	
	-1
};

static const long cPageSpwarp[] =
{
	kBgndSpWarp, -1,
	
	CID_SCROLL,
    kScrollerFfxSWMix, kScrollerFfxSWFrequency, kScrollerFfxSWTilt, 
    kScrollerFfxSWDamping, kScrollerFfxSWSpeed, kScrollerFfxSWDepth,
    -1,
	
	-1
};

static const long cPageStereospr[] =
{
	kBgndStereoSpr, -1,
	
	CID_SCROLL,
    kScrollerTfxSSChanDelay, kScrollerTfxSSFeedback,
    -1,
	
	-1
};

static const long cPageLrdelay[] =
{
	kBgndLrDelay, -1,
	
	CID_SCROLL,
    kScrollerTfxLRDMix, kScrollerTfxLRDTime, kScrollerTfxLRDFeedback,
    -1,
	
	-1
};

static const long cPageFlanger[] =
{
	-1, kBranchFlanger,-1,
	-1  
};

static const long cPageFlanger1[] =
{
	kBgndFlanger1, -1,
	
	CID_SWITCH,
    kSwitchTfxFLSub1, kSwitchTfxFLSub2, -2,
    kSwitchTfxFLWfTri, kSwitchTfxFLWfSine, kSwitchTfxFLWfSawUp,
    kSwitchTfxFLWfSawDown, kSwitchTfxFLWfSquare,  kSwitchTfxFLWfPosTri,
    kSwitchTfxFLWfPosSine, kSwitchTfxFLWfPosSquare, kSwitchTfxFLWfStepTri,
    kSwitchTfxFLWfStepSawUp, kSwitchTfxFLWfStepSawDown,
    kSwitchTfxFLWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerTfxFLMix, kScrollerTfxFLFeedback, kScrollerTfxFLSpeed, kScrollerTfxFLDepth,
    -1,
	
	-1
};

static const long cPageFlanger2[] =
{
	kBgndFlanger2, -1,
	
	CID_SWITCH,
    kSwitchTfxFLSub1, kSwitchTfxFLSub2, -2,
    kSwitchTfxFLWfTri, kSwitchTfxFLWfSine, kSwitchTfxFLWfSawUp,
    kSwitchTfxFLWfSawDown, kSwitchTfxFLWfSquare,  kSwitchTfxFLWfPosTri,
    kSwitchTfxFLWfPosSine, kSwitchTfxFLWfPosSquare, kSwitchTfxFLWfStepTri,
    kSwitchTfxFLWfStepSawUp, kSwitchTfxFLWfStepSawDown,
    kSwitchTfxFLWfRandom, -12,
	-1,
	
	CID_SCROLL,
    kScrollerTfxFLStereoPhase,
    -1,
	
	-1
};

static const long cPagePhaser[] =
{
	-1, kBranchPhaser,-1,
	-1  
};

static const long cPagePhaser1[] =
{
	kBgndPhaser1, -1,
	
	CID_SWITCH,
    kSwitchTfxPHSub1, kSwitchTfxPHSub2, -2,
    kSwitchTfxPHWfTri, kSwitchTfxPHWfSine, kSwitchTfxPHWfSawUp,
    kSwitchTfxPHWfSawDown, kSwitchTfxPHWfSquare,  kSwitchTfxPHWfPosTri,
    kSwitchTfxPHWfPosSine, kSwitchTfxPHWfPosSquare, kSwitchTfxPHWfStepTri,
    kSwitchTfxPHWfStepSawUp, kSwitchTfxPHWfStepSawDown,
    kSwitchTfxPHWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerTfxPHMix, kScrollerTfxPHFeedback, kScrollerTfxPHSpeed, kScrollerTfxPHDepth,
    -1,
	
	-1
};

static const long cPagePhaser2[] =
{
	kBgndPhaser2, -1,
	
	CID_SWITCH,
    kSwitchTfxPHSub1, kSwitchTfxPHSub2, -2,
    kSwitchTfxPHWfTri, kSwitchTfxPHWfSine, kSwitchTfxPHWfSawUp,
    kSwitchTfxPHWfSawDown, kSwitchTfxPHWfSquare,  kSwitchTfxPHWfPosTri,
    kSwitchTfxPHWfPosSine, kSwitchTfxPHWfPosSquare, kSwitchTfxPHWfStepTri,
    kSwitchTfxPHWfStepSawUp, kSwitchTfxPHWfStepSawDown,
    kSwitchTfxPHWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerTfxPHStereoPhase,
    -1,
	
	-1
};

static const long cPageChorus[] =
{
	-1, kBranchChorus,-1,
	-1  
};

static const long cPageChorus1[] =
{
	kBgndChorus1, -1,
	
	CID_SWITCH,
    kSwitchTfxCHSub1, kSwitchTfxCHSub2, -2,
    kSwitchTfxCHWfTri, kSwitchTfxCHWfSine, kSwitchTfxCHWfSawUp,
    kSwitchTfxCHWfSawDown, kSwitchTfxCHWfSquare,  kSwitchTfxCHWfPosTri,
    kSwitchTfxCHWfPosSine, kSwitchTfxCHWfPosSquare, kSwitchTfxCHWfStepTri,
    kSwitchTfxCHWfStepSawUp, kSwitchTfxCHWfStepSawDown,
    kSwitchTfxCHWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerTfxCHMix, kScrollerTfxCHFeedback, kScrollerTfxCHSpeed, kScrollerTfxCHDepth,
    -1,
	
	-1
};

static const long cPageChorus2[] =
{
	kBgndChorus2, -1,
	
	CID_SWITCH,
    kSwitchTfxCHSub1, kSwitchTfxCHSub2, -2,
    kSwitchTfxCHWfTri, kSwitchTfxCHWfSine, kSwitchTfxCHWfSawUp,
    kSwitchTfxCHWfSawDown, kSwitchTfxCHWfSquare,  kSwitchTfxCHWfPosTri,
    kSwitchTfxCHWfPosSine, kSwitchTfxCHWfPosSquare, kSwitchTfxCHWfStepTri,
    kSwitchTfxCHWfStepSawUp, kSwitchTfxCHWfStepSawDown,
    kSwitchTfxCHWfRandom, -12,
    -1,
	
	CID_SCROLL,
    kScrollerTfxCHStereoPhase,kScrollerTfxCHPreDelay,
    -1,
	
	-1
};

static const long cPageRemote[] =
{
	kBgndRemote, -1,
	
	CID_SWITCH,
    kSwitchMpResys, kSwitchMpSilver, kSwitchMpRemote, kSwitchMpAboutOff, -4,
    kSwitchMpSndUp,kSwitchMpSndDn,-2,
    kSwitchMpSndSave,
    -1,
	
	CID_DISPLAY,
    kDisplaySoundNumber,kDisplaySoundName,
    -1,
	
	CID_SCROLL,
    kScrollerVoiceLimit,
    kScrollerDepthAftertouch,kScrollerDepthModulation,kScrollerDepthBreath,
    kScrollerDepthCC03,kScrollerDepthFoot,kScrollerDepthExpression,
    -1,
	
	CID_DROPDOWN,
    kDropdownMpSndLoad,kDropdownMpSndSaveAs,
    kDropdownKnob1Select,kDropdownKnob2Select,
    kDropdownKnob3Select,kDropdownKnob4Select,
    kDropdownDestAftertouch,kDropdownDestModulation,kDropdownDestBreath,
    kDropdownDestCC03,kDropdownDestFoot,kDropdownDestExpression,
    -1,
	
	CID_AREA,
    kAreaAbout,
    -1,
	
	-1
};

static const long cPageAbout[] =
{
	kBgndAbout, -1,
	
	CID_SWITCH,
    kSwitchMpAbout,
    -1,
	
	CID_DISPLAY,
    kDisplayVersion,
    -1,
	
	-1
};


///////////////////////////////////////////////////////////////////////////////
// part 2of3: tree information of the pagelists
// these are held as a list of void pointers, the first half of the list
// is a collection of pagelists, the second half is a collection of further
// trees. endmark of each half is 0. 

static const long *cBranchRoot[] =
{
	cPageResys, cPageSilver, cPageRemote, cPageAbout, 0
};

static const long *cBranchR1Level[] =
{
	cPageR1Level1, cPageR1Level2, cPageR1Level3, 0
};

static const long *cBranchR2Level[] =
{
	cPageR2Level1, cPageR2Level2, cPageR2Level3, 0
};

static const long *cBranchFreqfx[] =
{
	cPageEqcompr, cPageDistort, cPageRingmod, cPageDecimat, 
	cPageSpwarp, 0
};

static const long *cBranchEqcompr[] =
{
	cPageEqshelfL, cPageEqband1, cPageEqband2, cPageEqshelfH,
	cPageCompr, 0
};

static const long *cBranchRingmod[] =
{
	cPageRingmod1, cPageRingmod2, 0
};

static const long *cBranchTimeFx[] =
{
	cPageStereospr, cPageLrdelay, cPageFlanger, cPagePhaser,
	cPageChorus, 0
};

static const long *cBranchFlanger[] =
{
	cPageFlanger1, cPageFlanger2, 0
};

static const long *cBranchPhaser[] =
{
	cPagePhaser1, cPagePhaser2, 0
};

static const long *cBranchChorus[] =
{
	cPageChorus1, cPageChorus2, 0
};


///////////////////////////////////////////////////////////////////////////////
// part 3of3: array of all branches

const long **cBranch[]=
{
	cBranchRoot,
	cBranchR1Level,
	cBranchR2Level,
	cBranchFreqfx,
	cBranchEqcompr,
	cBranchRingmod,
	cBranchTimeFx,
	cBranchFlanger,
	cBranchPhaser,
	cBranchChorus,
};


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthEditorPages.cpp,v $
// Revision 1.5  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.4  2004/10/05 16:53:09  joffe
// dropdown-menu implementation
//
// Revision 1.3  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.2  2004/08/26 01:17:46  joffe
// remote added, fixes and improvements
//
// Revision 1.1  2004/08/14 06:23:55  joffe
// remote-stuff added, synth-editor splitup
//
///////////////////////////////////////////////////////////////////////////////
