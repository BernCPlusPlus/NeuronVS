///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthEditorConfigs.cpp,v $
// $Revision: 1.17 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "SynthEditor.h"

const char *cCtrDest[] =
{
	"Resy1 Volume",
	"Resy1 Detune",
	"Resy1 L1 Scape 1/3",
	"Resy1 L1 Scape 2/4",
	"Resy1 L1 Spher 1/3",
	"Resy1 L1 Spher 2/4",
	"Resy1 L2 Scape 1/3",
	"Resy1 L2 Scape 2/4",
	"Resy1 L2 Spher 1/3",
	"Resy1 L2 Spher 2/4",
	"Resy1 L3 Scape 1/3",
	"Resy1 L3 Scape 2/4",
	"Resy1 L3 Spher 1/3",
	"Resy1 L3 Spher 2/4",
	
	"Resy2 Volume",
	"Resy2 Detune",
	"Resy2 L1 Scape 1/3",
	"Resy2 L1 Scape 2/4",
	"Resy2 L1 Spher 1/3",
	"Resy2 L1 Spher 2/4",
	"Resy2 L2 Scape 1/3",
	"Resy2 L2 Scape 2/4",
	"Resy2 L2 Spher 1/3",
	"Resy2 L2 Spher 2/4",
	"Resy2 L3 Scape 1/3",
	"Resy2 L3 Scape 2/4",
	"Resy2 L3 Spher 1/3",
	"Resy2 L3 Spher 2/4",
	
	"Shaper R1 Attack",
	"Shaper R1 Decay",
	"Shaper R1 Sustain",
	"Shaper R1 Release",
	"Shaper A1 Attack",
	"Shaper A1 Decay",
	"Shaper A1 Sustain",
	"Shaper A1 Release",
	"Shaper F1 Attack",
	"Shaper F1 Decay",
	"Shaper F1 Sustain",
	"Shaper F1 Release",
	
	"Shaper R2 Attack",
	"Shaper R2 Decay",
	"Shaper R2 Sustain",
	"Shaper R2 Release",
	"Shaper A2 Attack",
	"Shaper A2 Decay",
	"Shaper A2 Sustain",
	"Shaper A2 Release",
	"Shaper F2 Attack",
	"Shaper F2 Decay",
	"Shaper F2 Sustain",
	"Shaper F2 Release",
	
	"Shaper Filter A",
	"Shaper Filter D",
	"Shaper Filter S",
	"Shaper Filter R",
	
	"Blender Mix",
	
	"Slicer Depth",
	"Slicer Rate",
	
	"LFO Depth",
	"LFO Rate",
	
	"Filter Cutoff",
	"Filter Resonance",
};


///////////////////////////////////////////////////////////////////////////////
// build exclusive group of switches

void SynthEditor::ConfigSwitchGrp( CParam *param, const long *ids )
{
	int i;
	CSwitch *sw;
	
	if(param)
	{
		// count number of switches for this group
		for(i=0; ids[i]>=0 && i<100; i++);
		param->mQuant = 1.;
		param->mMin = 0.;
		param->mMax = (float)(i-1);
		
		// configure switches of this group
		for(i=0; *ids>=0 && i<100; i++,ids++)
		{
			if( (sw=mSwitch[*ids]) )
			{
				sw->SetMode(SWMD_CONSTANT, (float)i);
				sw->SetParam(param);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigSwitch(int index, const long *data)
{
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	switch(index)
	{
		case kSwitchMpSndSave:
			ntfSndSave.clear();
			ntfSndSave.inf[0] = this;
			ntfSndSave.inf[1] = &mSndSave;
			ntfSndSave.PstCbFn = stSndSave;
			mSndSave.mMin = 0.;
			mSndSave.mMax = 999.;
			mSndSave.AddNotify(&ntfSndSave,false,NFLG_NONE);
			mSwitch[kSwitchMpSndSave]->SetMode(SWMD_OFFLIKE,0.);
			mSwitch[kSwitchMpSndSave]->SetParam(&mSndSave);
			break;
			
		case kSwitchMpSndDn:
			if(*data<0)
			{
				mSwitch[kSwitchMpSndDn]->SetParam(&M_SYNTH->mActualSound);
				mSwitch[kSwitchMpSndDn]->SetMode(SWMD_OFFLIKE,-1.);
				mSwitch[kSwitchMpSndUp]->SetParam(&M_SYNTH->mActualSound);
				mSwitch[kSwitchMpSndUp]->SetMode(SWMD_OFFLIKE,1.);
			}
			break;
			
		case kSwitchMpAbout:
			mSwitch[index]->SetMode(SWMD_CONSTANT, mPgparm[kBranchRoot]->mMax);
			mSwitch[index]->SetParam(mPgparm[kBranchRoot]);
			break;
		case kSwitchMpAboutOff:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchRoot], data+*data);
			break;
			
		case kSwitchR1OctavP1:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + R1Octave, data+*data);
			break;
		case kSwitchR2OctavP1:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + R2Octave, data+*data);
			break;
			
		case kSwitchFfxTypeSpWarp:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchFreqfx], data+*data);
			break;
		case kSwitchFfxCRSub:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchEqcompr], data+*data);
			break;
		case kSwitchFfxRMSub2:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchRingmod], data+*data);
			break;
			
		case kSwitchTfxTypeChorus:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchTimefx], data+*data);
			break;
		case kSwitchTfxFLSub2:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchFlanger], data+*data);
			break;
		case kSwitchTfxPHSub2:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchPhaser], data+*data);
			break;
		case kSwitchTfxCHSub2:
			if(*data<0) ConfigSwitchGrp(mPgparm[kBranchChorus], data+*data);
			break;
			
		case kSwitchLfoWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + LFOWaveForm, data+*data);
			break;
		case kSwitchFfxRMWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + RM_WaveForm, data+*data);
			break;
		case kSwitchTfxFLWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + FL_WaveForm, data+*data);
			break;
		case kSwitchTfxPHWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + PH_WaveForm, data+*data);
			break;
		case kSwitchTfxCHWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + CH_WaveForm, data+*data);
			break;
		case kSwitchSlicerWfRandom:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + SlicerWaveForm, data+*data);
			break;
		case kSwitchFfxDSClipExp:
			if(*data<0) ConfigSwitchGrp(M_SYNTH->snddat->mParam + DS_ClipCurveType, data+*data);
			break;
			//  case kSwitchR1Record:
		case kSwitchR1Switch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R1Switch);
			break;
		case kSwitchR1ParamLevel:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R1ParamLevel);
			break;
			
		case kSwitchR1CtxContour:
			if(*data<0)
			{
				ntfR1SwitchCtx.clear();
				ntfR1SwitchCtx.inf[0] = this;
				ntfR1SwitchCtx.PstCbFn = stR1SwitchCtx;
				M_SYNTH->snddat->mParam[R1Type].AddNotify(&ntfR1SwitchCtx,true);
				M_SYNTH->snddat->mParam[R1ParamLevel].AddNotify(&ntfR1SwitchCtx,true);
			}
			break;
			
		case kSwitchR1Type:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R1Type);
			break;
		case kSwitchR1CtxSelectXY:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R1SelectStickPar);
			break;
			//  case kSwitchR2Record:
		case kSwitchR2Switch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R2Switch);
			break;
		case kSwitchR2ParamLevel:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R2ParamLevel);
			break;
			
		case kSwitchR2CtxContour:
			if(*data<0)
			{
				ntfR2SwitchCtx.clear();
				ntfR2SwitchCtx.inf[0] = this;
				ntfR2SwitchCtx.PstCbFn = stR2SwitchCtx;
				M_SYNTH->snddat->mParam[R2Type].AddNotify(&ntfR2SwitchCtx,true);
				M_SYNTH->snddat->mParam[R2ParamLevel].AddNotify(&ntfR2SwitchCtx,true);
			}
			break;
			
		case kSwitchR2Type:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R2Type);
			break;
		case kSwitchR2CtxSelectXY:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + R2SelectStickPar);
			break;
		case kSwitchLfoSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + LFOSwitch);
			break;
			//  case kSwitchSilverRecord:
		case kSwitchSilverSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + SilverSwitch);
			break;
		case kSwitchSilverParamLevel:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + SilverParamLevel);
			break;
			
		case kSwitchSilverCtxContour:
			if(*data<0)
			{
				ntfSISwitchCtx.clear();
				ntfSISwitchCtx.inf[0] = this;
				ntfSISwitchCtx.PstCbFn = stSISwitchCtx;
				M_SYNTH->snddat->mParam[SilverParamLevel].AddNotify(&ntfSISwitchCtx,true);
			}
			break;
			
		case kSwitchSlicerSwitch:
			mSlicerSwitch.mMax = 1.;
			mSlicerSwitch.AddNotify(&ntfSlicerSwitch,true,NFLG_NONE);
			mSwitch[index]->SetParam(&mSlicerSwitch);
			break;
		case kSwitchSlicerType:
			mSlicerType.mMax = 1.;
			mSlicerType.AddNotify(&ntfSlicerType,true,NFLG_NONE);
			mSwitch[index]->SetParam(&mSlicerType);
			break;
			
		case kSwitchFfxSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + FreqFXSwitch);
			break;
		case kSwitchFfxEQSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Switch);
			break;
		case kSwitchFfxEQLowSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + EQ_LowShelfSwitch);
			break;
		case kSwitchFfxEQBand1Switch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band1Switch);
			break;
		case kSwitchFfxEQBand2Switch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band2Switch);
			break;
		case kSwitchFfxEQHighSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + EQ_HighShelfSwitch);
			break;
		case kSwitchFfxCRSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + CR_Switch);
			break;
		case kSwitchTfxSwitch:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + TimeFXSwitch);
			break;
		case kSwitchShaper3Mode:
			mSwitch[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvMode);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigScroller(int index, const long *data)
{
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	// configure scrollers
	switch(index)
	{
		case kScrollerR1AmpLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1AmpLfoDepth);
			break;
		case kScrollerR1AmpKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1AmpKeyTrack);
			break;
		case kScrollerR1VolumeVelocityDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1VolumeVelocityDepth);
			break;
		case kScrollerR1ModelSizeKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1ModelSizeKeyTrack);
			break;
		case kScrollerR1ModelSizeOffset:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1ModelSizeOffset);
			break;
		case kScrollerR1ModelVelocitySwitch:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1ModelVelocitySwitch);
			break;
		case kScrollerR1Semi:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1Semi);
			break;
		case kScrollerR1Cents:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1Cents);
			break;
		case kScrollerR1PitchLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1PitchLfoDepth);
			break;
		case kScrollerR1PitchKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1PitchKeyTrack);
			break;
			
			
		case kScrollerR1CtxEnvDepth:
			if(*data<0)
			{
				ntfR1ScrollerCtx.inf[0] = mScroller;
				ntfR1ScrollerCtx.inf[1] = M_SYNTH->snddat->mParam;
				ntfR1ScrollerCtx.PreCbFn = 0;
				ntfR1ScrollerCtx.PstCbFn = stR1ScrollerCtx;
				M_SYNTH->snddat->mParam[R1Type].AddNotify(&ntfR1ScrollerCtx);
				M_SYNTH->snddat->mParam[R1ParamLevel].AddNotify(&ntfR1ScrollerCtx);
				M_SYNTH->snddat->mParam[R1SelectStickPar].AddNotify(&ntfR1ScrollerCtx);
			}
			break;
			
		case kScrollerR1FreeADSR1PitchDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1FreeADSR1PitchDepth);
			break;
		case kScrollerR1FreeADSR2PitchDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1FreeADSR2PitchDepth);
			break;
			
			
		case kScrollerBlenderAmount:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + BlenderAmount);
			break;
		case kScrollerBlenderLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + BlenderLfoDepth);
			break;
		case kScrollerBlenderFreeADSR1Depth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + BlenderFreeADSR1Depth);
			break;
		case kScrollerBlenderFreeADSR2Depth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + BlenderFreeADSR2Depth);
			break;
			
		case kScrollerR2AmpLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2AmpLfoDepth);
			break;
		case kScrollerR2AmpKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2AmpKeyTrack);
			break;
		case kScrollerR2VolumeVelocityDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2VolumeVelocityDepth);
			break;
		case kScrollerR2ModelSizeKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2ModelSizeKeyTrack);
			break;
		case kScrollerR2ModelSizeOffset:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2ModelSizeOffset);
			break;
		case kScrollerR2ModelVelocitySwitch:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2ModelVelocitySwitch);
			break;
		case kScrollerR2Semi:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2Semi);
			break;
		case kScrollerR2Cents:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2Cents);
			break;
		case kScrollerR2PitchLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2PitchLfoDepth);
			break;
		case kScrollerR2PitchKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2PitchKeyTrack);
			break;
			
		case kScrollerR2CtxEnvDepth:
			if(*data<0)
			{
				ntfR2ScrollerCtx.inf[0] = mScroller;
				ntfR2ScrollerCtx.inf[1] = M_SYNTH->snddat->mParam;
				ntfR2ScrollerCtx.PreCbFn = 0;
				ntfR2ScrollerCtx.PstCbFn = stR2ScrollerCtx;
				M_SYNTH->snddat->mParam[R2Type].AddNotify(&ntfR2ScrollerCtx);
				M_SYNTH->snddat->mParam[R2ParamLevel].AddNotify(&ntfR2ScrollerCtx);
				M_SYNTH->snddat->mParam[R2SelectStickPar].AddNotify(&ntfR2ScrollerCtx);
			}
			break;
			
		case kScrollerR2FreeADSR1PitchDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2FreeADSR1PitchDepth);
			break;
		case kScrollerR2FreeADSR2PitchDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2FreeADSR2PitchDepth);
			break;
			
			
			//TODO: no idea what these are for - the names are crap
		case kScrollerShaper1ParamVeloDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1ParaEnvVelocityDepth);
			break;
		case kScrollerShaper1FreeVeloDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FreeADSR1VelocityDepth);
			break;
		case kScrollerShaper1FreeDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R1FreeEnvDepth);
			break;
		case kScrollerShaper2ParamVeloDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2ParaEnvVelocityDepth);
			break;
		case kScrollerShaper2FreeVeloDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FreeADSR2VelocityDepth);
			break;
		case kScrollerShaper2FreeDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + R2FreeEnvDepth);
			break;
			
			
			//
			// Mod/LFO
			//
		case kScrollerLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LFODepth);
			break;
		case kScrollerLfoRate:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LFORate);
			break;
		case kScrollerLfoDelay:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LFODelay);
			break;
			// 
			// Silver Filter
			//
		case kScrollerFilterCutoff:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterFreq);
			break;
		case kScrollerFilterResonance:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterReso);
			break;
		case kScrollerFilterLfoDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterLfoDepth);
			break;
		case kScrollerFilterKeyTrack:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterKeyTrack);
			break;
		case kScrollerFilterVeloDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterCutoffVelocityDepth);
			break;
			//
			// Freq FX
			//
			// --- EQ/Compressor
		case kScrollerFfxEQLowGain:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_LowShelfGain);
			break;
		case kScrollerFfxEQLowFreq:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_LowShelfFreq);
			break;
		case kScrollerFfxEQLowSlope:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_LowShelfSlope);
			break;
		case kScrollerFfxEQBand1Gain:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band1Gain);
			break;
		case kScrollerFfxEQBand1Freq:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band1Freq);
			break;
		case kScrollerFfxEQBand1Q:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band1Q);
			break;
		case kScrollerFfxEQBand2Gain:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band2Gain);
			break;
		case kScrollerFfxEQBand2Freq:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band2Freq);
			break;
		case kScrollerFfxEQBand2Q:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_Band2Q);
			break;
		case kScrollerFfxEQHighGain:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_HighShelfGain);
			break;
		case kScrollerFfxEQHighFreq:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_HighShelfFreq);
			break;
		case kScrollerFfxEQHighSlope:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + EQ_HighShelfSlope);
			break;
		case kScrollerFfxCRThreshold:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CR_Threshold);
			break;
		case kScrollerFfxCROutGain:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CR_OutGain);
			break;
		case kScrollerFfxCRReponsiveness:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CR_Responsiveness);
			break;
			// --- Distortion
		case kScrollerFfxDSInDrive:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DS_InGain);
			break;
		case kScrollerFfxDSPreFilter:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DS_PreFilter);
			break;
		case kScrollerFfxDSOutVolume:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DS_OutGain);
			break;
			// --- Ring Modulator
		case kScrollerFfxRMMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_Mix);
			break;
		case kScrollerFfxRMModFreq:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_ModFreq);
			break;
		case kScrollerFfxRMSpeed:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_Speed);
			break;
		case kScrollerFfxRMDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_Depth);
			break;
		case kScrollerFfxRMXoverDelay:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_XoverDelay);
			break;
		case kScrollerFfxRMXoverTime:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_XoverTime);
			break;
		case kScrollerFfxRMXoverFeedbk:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + RM_XoverDelayFeedback);
			// --- Decimator
			break;
		case kScrollerFfxDCMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DC_Mix);
			break;
		case kScrollerFfxDCSHFactor:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DC_SHFactor);
			break;
		case kScrollerFfxDCPreFilter:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + DC_PreFilterCutoff);
			break;
			// --- Sp_warp
		case kScrollerFfxSWMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Mix);
			break;
		case kScrollerFfxSWFrequency:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Frequency);
			break;
		case kScrollerFfxSWTilt:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Tilt);
			break;
		case kScrollerFfxSWDamping:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Damping);
			break;
		case kScrollerFfxSWSpeed:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Speed);
			break;
		case kScrollerFfxSWDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SW_Depth);
			break;
			//
			// Time FX
			//
			// --- Stereo Spread
		case kScrollerTfxSSChanDelay:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SS_ChanDelay);
			break;
		case kScrollerTfxSSFeedback:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SS_Feedback);
			break;
			// --- L/R Delay
		case kScrollerTfxLRDMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LRD_Mix);
			break;
		case kScrollerTfxLRDTime:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LRD_Time);
			break;
		case kScrollerTfxLRDFeedback:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + LRD_Feedback);
			break;
			// --- Flanger
		case kScrollerTfxFLMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FL_Mix);
			break;
		case kScrollerTfxFLFeedback:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FL_Feedback);
			break;
		case kScrollerTfxFLSpeed:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FL_Speed);
			break;
		case kScrollerTfxFLDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FL_Depth);
			break;
		case kScrollerTfxFLStereoPhase:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FL_StereoPhase);
			break;
			// --- Phaser
		case kScrollerTfxPHMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + PH_Mix);
			break;
		case kScrollerTfxPHFeedback:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + PH_Feedback);
			break;
		case kScrollerTfxPHSpeed:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + PH_Speed);
			break;
		case kScrollerTfxPHDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + PH_Depth);
			break;
		case kScrollerTfxPHStereoPhase:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + PH_StereoPhase);
			break;
			// --- Chorus
		case kScrollerTfxCHMix:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_Mix);
			break;
		case kScrollerTfxCHFeedback:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_Feedback);
			break;
		case kScrollerTfxCHSpeed:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_Speed);
			break;
		case kScrollerTfxCHDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_Depth);
			break;
		case kScrollerTfxCHStereoPhase:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_StereoPhase);
			break;
		case kScrollerTfxCHPreDelay:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CH_PreDelay);
			break;
			//
			// Slicer
			//
		case kScrollerSlicerDepth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SlicerDepth);
			break;
		case kScrollerSlicerRate:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SlicerRate);
			break;
			//
			// Shaper 3
			//
		case kScrollerShaper3Depth:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvDepth);
			break;
		case kScrollerShaper3VeloDepth:
			mScroller[kScrollerShaper3VeloDepth]->SetParam(M_SYNTH->snddat->mParam + FilterEnvVelocityDepth);
			break;
		case kScrollerShaper3A:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvA);
			break;
		case kScrollerShaper3D:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvD);
			break;
		case kScrollerShaper3S:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvS);
			break;
		case kScrollerShaper3R:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FilterEnvR);
			break;
			//
			// Remote
			//
		case kScrollerVoiceLimit:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + SoundNumVoices);
			break;
		case kScrollerDepthAftertouch:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + AftertouchDepth);
			break;
		case kScrollerDepthModulation:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + ModulationDepth);
			break;
		case kScrollerDepthBreath:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + BreathDepth);
			break;
		case kScrollerDepthCC03:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + CC03Depth);
			break;
		case kScrollerDepthFoot:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + FootDepth);
			break;
		case kScrollerDepthExpression:
			mScroller[index]->SetParam(M_SYNTH->snddat->mParam + ExpressionDepth);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigDisplay(int index)
{
	// configure displays
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	
	switch(index)
	{
		case kDisplayR1ModelName:
			ntfR1Model.clear();
			ntfR1Model.inf[0] = this;
			ntfR1Model.inf[1] = 0;
			ntfR1Model.PstCbFn = stModel;
			M_SYNTH->snddat->mParam[R1ModellIndex].AddNotify(&ntfR1Model,true);
			break;
		case kDisplayR1ModelNumber:
			mInputR1ModelNumber.mParam = M_SYNTH->snddat->mParam + R1ModellIndex;
			mInputR1ModelNumber.mMP = ((SynthCore*)this->mSynth)->params;
			mInputR1ModelNumber.mAS = &(((SynthCore*)this->mSynth)->mActualSound);
			break;
			
		case kDisplayR2ModelName:
			ntfR2Model.clear();
			ntfR2Model.inf[0] = this;
			ntfR2Model.inf[1] = (void *)1;
			ntfR2Model.PstCbFn = stModel;
			M_SYNTH->snddat->mParam[R2ModellIndex].AddNotify(&ntfR2Model,true);
			break;
		case kDisplayR2ModelNumber:
			mInputR2ModelNumber.mParam = M_SYNTH->snddat->mParam + R2ModellIndex;
			mInputR2ModelNumber.mMP = ((SynthCore*)this->mSynth)->params;
			mInputR2ModelNumber.mAS = &(((SynthCore*)this->mSynth)->mActualSound);
			break;
			
		case kDisplaySoundName:
			ntfSound.clear();
			ntfSound.inf[0] = this;
			ntfSound.PstCbFn = stSound;
			M_SYNTH->mActualSound.AddNotify(&ntfSound,true);
			mInputSoundName.mParam = M_SYNTH->snddat->mParam + SoundNameC00;
			mInputSoundName.mSoundNameDisplay = mDisplay[kDisplaySoundName];
			mInputSoundName.mMP = ((SynthCore*)this->mSynth)->params;
			mInputSoundName.mAS = &(((SynthCore*)this->mSynth)->mActualSound);
			break;
		case kDisplaySoundNumber:
			mInputSoundNumber.mParam = &M_SYNTH->mActualSound;
			mInputSoundNumber.mMP = ((SynthCore*)this->mSynth)->params;
			mInputSoundNumber.mAS = &(((SynthCore*)this->mSynth)->mActualSound);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigStick(int index)
{
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	
	// configure sticks
	switch(index)
	{
		case kStickR1:
			ntfR1StickCtx.clear();
			ntfR1StickCtx.inf[0] = this;
			ntfR1StickCtx.PstCbFn = stR1StickCtx;
			M_SYNTH->snddat->mParam[R1Type].AddNotify(&ntfR1StickCtx,true);
			M_SYNTH->snddat->mParam[R1ParamLevel].AddNotify(&ntfR1StickCtx,true);
			mStick[index]->SetResetAllCb(stR1Reset,this);
			break;
			
		case kStickR2:
			ntfR2StickCtx.clear();
			ntfR2StickCtx.inf[0] = this;
			ntfR2StickCtx.PstCbFn = stR2StickCtx;
			M_SYNTH->snddat->mParam[R2Type].AddNotify(&ntfR2StickCtx,true);
			M_SYNTH->snddat->mParam[R2ParamLevel].AddNotify(&ntfR2StickCtx,true);
			mStick[index]->SetResetAllCb(stR2Reset,this);
			break;
			
		case kStickSilver:
			M_SYNTH->snddat->mParam[FilterFreq].mDscr1 =     "Cutoff";
			M_SYNTH->snddat->mParam[FilterReso].mDscr1 =     "Resonance";
			
			M_SYNTH->snddat->mParam[EQ_Band1Gain].mDscr1 =   "B1 Q";
			M_SYNTH->snddat->mParam[DS_InGain].mDscr1 =      "In Drive";
			M_SYNTH->snddat->mParam[RM_Mix].mDscr1 =         "Mix";
			M_SYNTH->snddat->mParam[DC_Mix].mDscr1 =         "Mix";
			M_SYNTH->snddat->mParam[SW_Mix].mDscr1 =         "Mix";
			
			M_SYNTH->snddat->mParam[EQ_Band1Freq].mDscr1 =   "B1 Freq";
			M_SYNTH->snddat->mParam[DS_PreFilter].mDscr1 =   "Pre Filt";
			M_SYNTH->snddat->mParam[RM_ModFreq].mDscr1 =     "Mod Freq";
			M_SYNTH->snddat->mParam[DC_SHFactor].mDscr1 =    "S&H Factor";
			M_SYNTH->snddat->mParam[SW_Frequency].mDscr1 =   "Frequency";
			
			M_SYNTH->snddat->mParam[SS_ChanDelay].mDscr1 =   "Chan Delay";
			M_SYNTH->snddat->mParam[LRD_Mix].mDscr1 =        "Mix";
			M_SYNTH->snddat->mParam[FL_Mix].mDscr1 =         "Mix";
			M_SYNTH->snddat->mParam[PH_Mix].mDscr1 =         "Mix";
			M_SYNTH->snddat->mParam[CH_Mix].mDscr1 =         "Mix";
			
			M_SYNTH->snddat->mParam[SS_Feedback].mDscr1 =    "Feedback";
			M_SYNTH->snddat->mParam[LRD_Time].mDscr1 =       "Time";
			M_SYNTH->snddat->mParam[FL_Feedback].mDscr1 =    "Feedback";
			M_SYNTH->snddat->mParam[PH_Feedback].mDscr1 =    "Feedback";
			M_SYNTH->snddat->mParam[CH_Feedback].mDscr1 =    "Feedback";
			
			ntfSIStickCtx.clear();;
			ntfSIStickCtx.inf[0] = this;
			ntfSIStickCtx.PstCbFn = stSIStickCtx;
			M_SYNTH->snddat->mParam[SilverParamLevel].AddNotify(&ntfSIStickCtx,true);
			M_SYNTH->snddat->mParam[CurFreqFX].AddNotify(&ntfSIStickCtx,true);
			M_SYNTH->snddat->mParam[CurTimeFX].AddNotify(&ntfSIStickCtx,true);
	}
}


///////////////////////////////////////////////////////////////////////////////
// build exclusive group of switches

void SynthEditor::ConfigDial(int index)
{
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	// configure scrollers
	switch(index)
	{
		case kDialR1Volume:
			mDial[index]->SetParam(M_SYNTH->snddat->mParam + R1Volume);
			break;
			
		case kDialR2Volume:
			mDial[index]->SetParam(M_SYNTH->snddat->mParam + R2Volume);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
// build exclusive group of shapers

void SynthEditor::ConfigShaperGrp( CParam *param, const long *ids )
{
	int i;
	CShaper *sh;
	
	if(param)
	{
		// count number of shapers for this group
		for(i=0; ids[i]>=0 && i<100; i++);
		param->mQuant = 1.;
		param->mMin = 0.;
		param->mMax = (float)(i-1);
		
		// configure shapers of this group
		for(i=0; *ids>=0 && i<100; i++,ids++)
		{
			if( (sh=mShaper[*ids]) )
			{
				sh->SetHitVal((float)i);
				sh->SetHitParam(param);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigShaper(int index, const long *data)
{
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	// configure shapers
	switch(index)
	{
		case kShaper1Resy:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R1ResEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R1ResEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R1ResEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R1ResEnvR);
			break;
		case kShaper1Amp:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R1AmpEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R1AmpEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R1AmpEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R1AmpEnvR);
			break;
		case kShaper1Free:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R1FreeEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R1FreeEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R1FreeEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R1FreeEnvR);
			break;
		case kShaper2Resy:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R2ResEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R2ResEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R2ResEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R2ResEnvR);
			break;
		case kShaper2Amp:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R2AmpEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R2AmpEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R2AmpEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R2AmpEnvR);
			break;
		case kShaper2Free:
			if(*data<0)
			{
				ConfigShaperGrp(mActShaper, data+*data);
				ntfShaperFocus.inf[0] = this;
				ntfShaperFocus.inf[1] = 0;
				ntfShaperFocus.PreCbFn = 0;
				ntfShaperFocus.PstCbFn = stShaperFocus;
				mActShaper->AddNotify(&ntfShaperFocus,true);
			}
			else
			{
				mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + R2FreeEnvA);
				mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + R2FreeEnvD);
				mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + R2FreeEnvS);
				mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + R2FreeEnvR);
			}
			break;
			
		case kShaper3:
			mShaper[index]->SetParamA(M_SYNTH->snddat->mParam + FilterEnvA);
			mShaper[index]->SetParamD(M_SYNTH->snddat->mParam + FilterEnvD);
			mShaper[index]->SetParamS(M_SYNTH->snddat->mParam + FilterEnvS);
			mShaper[index]->SetParamR(M_SYNTH->snddat->mParam + FilterEnvR);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigDropdown(int index)
{
	int i;
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	
	// configure dropdown menus
	switch(index)
	{
		case kDropdownMpSndLoad:
		case kDropdownMpSndSaveAs:
			mDropdown[index]->removeAllEntry();
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[0],"Sounds 000-099");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[1],"Sounds 100-199");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[2],"Sounds 200-299");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[3],"Sounds 300-399");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[4],"Sounds 400-499");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[5],"Sounds 500-599");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[6],"Sounds 600-699");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[7],"Sounds 700-799");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[8],"Sounds 800-899");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[9],"Sounds 900-999");
			
			for(i=0; i<10; i++)
			{
				mDropdown[index]->mSubs[i]->removeAllEntry();
				mDropdown[index]->mSubs[i]->setPrefixNumbers(4);
				mDropdown[index]->mSubs[i]->setNbItemsPerColumn(25);
				mDropdown[index]->mSubs[i]->SetOffset((float)i*(float)100.);
			}
			
			for(i=0; i<1000; i++)
			{
				mDropdown[index]->mSubs[i/100]->addEntry(M_SYNTH->params->GetSoundName(i),i);
			}
			break;
			
		case kDropdownR1ModelSelect:
		case kDropdownR2ModelSelect:
			mDropdown[index]->removeAllEntry();
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[0],"Models 000-127");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[1],"Models 128-255");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[2],"Models 256-383");
			mDropdown[index]->addEntry(mDropdown[index]->mSubs[3],"Models 384-511");
			
			for(i=0; i<4; i++)
			{
				mDropdown[index]->mSubs[i]->removeAllEntry();
				mDropdown[index]->mSubs[i]->setPrefixNumbers(4);
				mDropdown[index]->mSubs[i]->setNbItemsPerColumn(32);
				mDropdown[index]->mSubs[i]->SetOffset((float)i*(float)128.);
			}
			
			for(i=0; i<512; i++)
			{
				mDropdown[index]->mSubs[i>>7]->addEntry(M_SYNTH->params->GetModelName(i),i);
			}
			break;
			
		case kDropdownBlenderType:
			mDropdown[index]->removeAllEntry();
			mDropdown[index]->addEntry("Mix",bt_mix);
			mDropdown[index]->addEntry("Stereo",bt_stereo);
			mDropdown[index]->addEntry("SinglSpher",bt_mixssp);
			mDropdown[index]->addEntry("Chromophon",bt_chromo);
			mDropdown[index]->addEntry("DualSphere",bt_dual);
			mDropdown[index]->addEntry("Intermorph",bt_intermorph);
			mDropdown[index]->addEntry("DynTrSpher",bt_dtrans);
			mDropdown[index]->addEntry("DynXMorph",bt_dcross);
			mDropdown[index]->addEntry("VeloXMorph",bt_vcross);
			mDropdown[index]->addEntry("VeloChrome",bt_vchromo);
			break;
			
		case kDropdownFilterType:
			mDropdown[index]->removeAllEntry();
			mDropdown[index]->addEntry("24dB Low Pass",ft_24dbLP);
			mDropdown[index]->addEntry("12dB Low Pass",ft_12dbLP);
			mDropdown[index]->addEntry(" 6dB Low Pass",ft_6dbLP);
			mDropdown[index]->addEntry(" 6dB High Pass",ft_6dbHP);
			mDropdown[index]->addEntry("Band Pass",ft_Bandpass);
			break;
			
		case kDropdownKnob1Select:
		case kDropdownKnob2Select:
		case kDropdownKnob3Select:
		case kDropdownKnob4Select:
		case kDropdownDestAftertouch:
		case kDropdownDestModulation:
		case kDropdownDestBreath:
		case kDropdownDestCC03:
		case kDropdownDestFoot:
		case kDropdownDestExpression:
			mDropdown[index]->removeAllEntry();
			for(int cc=0; cc<(int)(sizeof(cCtrDest)/sizeof(cCtrDest[0])); cc++)
			{
				mDropdown[index]->addEntry((char *)cCtrDest[cc],cc);
			}
			mDropdown[index]->setNbItemsPerColumn(28);
			break;
	}
	
	// connect parameters
	switch(index)
	{
		case kDropdownMpSndLoad:
			mDropdown[index]->SetParam(&M_SYNTH->mActualSound);
			break;
		case kDropdownMpSndSaveAs:
			mDropdown[index]->SetParam(&mSndSave);
			break;
		case kDropdownR1ModelSelect:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + R1ModellIndex);
			break;
		case kDropdownR2ModelSelect:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + R2ModellIndex);
			break;
		case kDropdownBlenderType:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + BlenderType);
			break;
		case kDropdownFilterType:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + FilterType);
			break;
			
		case kDropdownKnob1Select:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + Knob1R1Select);
			ntfKnob.clear();
			ntfKnob.inf[0] = this;
			ntfKnob.PstCbFn = stKnob;
			M_SYNTH->snddat->mParam[Knob1R1Select].AddNotify(&ntfKnob,true);
			break;
		case kDropdownKnob2Select:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + Knob2R1Select);
			M_SYNTH->snddat->mParam[Knob2R1Select].AddNotify(&ntfKnob,true);
			break;
		case kDropdownKnob3Select:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + Knob3R1Select);
			M_SYNTH->snddat->mParam[Knob3R1Select].AddNotify(&ntfKnob,true);
			break;
		case kDropdownKnob4Select:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + Knob4R1Select);
			M_SYNTH->snddat->mParam[Knob4R1Select].AddNotify(&ntfKnob,true);
			break;
			
		case kDropdownDestAftertouch:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + AftertouchDest);
			break;
		case kDropdownDestModulation:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + ModulationDest);
			break;
		case kDropdownDestBreath:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + BreathDest);
			break;
		case kDropdownDestCC03:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + CC03Dest);
			break;
		case kDropdownDestFoot:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + FootDest);
			break;
		case kDropdownDestExpression:
			mDropdown[index]->SetParam(M_SYNTH->snddat->mParam + ExpressionDest);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::ConfigArea(int index)
{
	// configure areas
	switch(index)
	{
		case kAreaAbout:
			mArea[index]->SetMouseClickCb(stAbout,this);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthEditorConfigs.cpp,v $
// Revision 1.17  2004/12/02 13:33:18  joffe
// bugfix: editor crash
//
// Revision 1.16  2004/11/23 08:13:12  joffe
// added neuron-vs style slicer switch/type with kb-compatibility
//
// Revision 1.15  2004/11/20 11:18:56  joffe
// bugfix
//
// Revision 1.14  2004/11/20 08:23:17  joffe
// first implementation of shaper-previews
//
// Revision 1.13  2004/11/11 04:11:36  joffe
// shaper-resy select as sndparam, name-update for dropdown
//
// Revision 1.12  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.11  2004/11/03 00:59:35  joffe
// knobselect added
//
// Revision 1.10  2004/11/02 11:36:05  joffe
// 'silver' renamed to 'filter'
//
// Revision 1.9  2004/10/29 02:09:17  joffe
// mac-gcc warning removed
//
// Revision 1.8  2004/10/29 01:55:15  joffe
// controller-destinations added
//
// Revision 1.7  2004/10/29 00:41:25  joffe
// voice-limitation added
//
// Revision 1.6  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.5  2004/10/18 06:41:34  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
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
