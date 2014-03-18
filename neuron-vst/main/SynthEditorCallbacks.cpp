///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthEditorCallbacks.cpp,v $
// $Revision: 1.18 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "SynthEditor.h"

#include <stdio.h>

#define M_MAP(uiidx, cvidx, engineidx, ntflist) uiidx,
const int cCvdToSp[] =
{
#include "MapToEngineDef.h"
};


///////////////////////////////////////////////////////////////////////////////
//
// notification callbacks to change parameter-attachments
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stUpdateNames( void *this_p )
{
	const int ipDD[] = {kDropdownR1ModelSelect,kDropdownR2ModelSelect,kDropdownMpSndLoad,kDropdownMpSndSaveAs};
	SynthEditor *se = (SynthEditor *)this_p;
	int dropdn;
	
	for(int i=0; i<4;i++)
	{
		dropdn = ipDD[i];
		
		if(se->mDropdown[dropdn]) se->ConfigDropdown(dropdn);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stSlicerSwitch( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	//	SynthCore *M_SYNTH = (SynthCore*)se->mSynth;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	float slsw = param->GetVal();
	float newswt = se->mSlicerType.GetVal()+1.f;
	
	if(!inf[1])
	{
		sp[SlicerSwitchType].SetVal(slsw ? newswt : 0.f,NFLG_OTHERS);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stSlicerType( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	float slsw = se->mSlicerSwitch.GetVal();
	float newswt = param->GetVal()+1.f;
	
	if(!inf[1])
	{
		sp[SlicerSwitchBackup].SetVal(newswt,NFLG_ALL);
		sp[SlicerSwitchType].SetVal(slsw ? newswt : 0.f,NFLG_OTHERS);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stSlicerVal( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	float slswt = param->GetVal();
	
	se->ntfSlicerSwitch.inf[1] = (void *)1;
	se->ntfSlicerType.inf[1] = (void *)1;
	if(slswt)
	{
		// is switched on
		se->mSlicerType.SetVal(slswt-1.f,NFLG_ALL);
		se->mSlicerSwitch.SetVal(1.f,NFLG_ALL);
	}
	else
	{
		// is switched off
		slswt = sp[SlicerSwitchBackup].GetVal();
		se->mSlicerType.SetVal(slswt-1,NFLG_ALL);
		se->mSlicerSwitch.SetVal(0.f,NFLG_ALL);
	}
	se->ntfSlicerSwitch.inf[1] = (void *)0;
	se->ntfSlicerType.inf[1] = (void *)0;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stKnob( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam, *stp[4];
	
	if(((SynthCore*)se->mSynth)->remote)
	{
		stp[0] = &sp[cCvdToSp[(int)sp[Knob1R1Select].GetVal()]];
		stp[1] = &sp[cCvdToSp[(int)sp[Knob2R1Select].GetVal()]];
		stp[2] = &sp[cCvdToSp[(int)sp[Knob3R1Select].GetVal()]];
		stp[3] = &sp[cCvdToSp[(int)sp[Knob4R1Select].GetVal()]];
		
		((SynthCore*)se->mSynth)->remote->SetParamDials(0,stp);
		((SynthCore*)se->mSynth)->remote->SetParamDials(1,stp);
		((SynthCore*)se->mSynth)->remote->SetParamDials(2,stp);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stSound( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	char buf[17];
	int i;
	
	se->mSndSave.SetVal(in[1],NFLG_NONE);
	if(se->mDisplay[kDisplaySoundNumber])
	{
		se->mDisplay[kDisplaySoundNumber]->SetInt((int)in[1],false);
	}
	
	if(se->mDisplay[kDisplaySoundName])
	{
		for(i=0; i<16;i++)
		{
			buf[i] = (char)sp[SoundNameC00+i].GetVal();
		}
		if(i<17) buf[i] = 0;
		se->mDisplay[kDisplaySoundName]->SetText(buf);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stSndSave( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CParam *si = (CParam *)inf[1];
	float sidx = si->GetVal();
	
	((SynthCore*)se->mSynth)->params->SaveSound((int)sidx);
	((SynthCore*)se->mSynth)->mActualSound.SetVal(sidx,NFLG_ALL);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stModel( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	
	if(!inf[1])
	{
		se->mDisplay[kDisplayR1ModelNumber]->SetInt((int)in[1],false);
		se->mDisplay[kDisplayR1ModelName]->SetText(param->mDscr1);
	}
	else
	{
		se->mDisplay[kDisplayR2ModelNumber]->SetInt((int)in[1],false);
		se->mDisplay[kDisplayR2ModelName]->SetText(param->mDscr1);
	}
}


///////////////////////////////////////////////////////////////////////////////
// set contour and playback switches

void SynthEditor::stR1SwitchCtx( float *in, CParam *param, void **inf )
{
	const int ipCnt[] = {R1L1ContourSphere, R1L2ContourSphere, R1L3ContourSphere, R1L1ContourScape, R1L2ContourScape, R1L3ContourScape};
	const int ipPlb[] = {R1L1SphereStickPlayback, R1L2SphereStickPlayback, R1L3SphereStickPlayback, R1L1ScapeStickPlayback, R1L2ScapeStickPlayback, R1L3ScapeStickPlayback};
	SynthEditor *se = (SynthEditor *)inf[0];
	CSwitch **sw = se->mSwitch;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	int type = (int)sp[R1Type].GetVal();
	int level = (int)sp[R1ParamLevel].GetVal();
	sw[kSwitchR1CtxContour]->SetParam(sp + ipCnt[3*type + level]);
	sw[kSwitchR1CtxStickPb]->SetParam(sp + ipPlb[3*type + level]);
}

void SynthEditor::stR2SwitchCtx( float *in, CParam *param, void **inf )
{
	const int ipCnt[] = {R2L1ContourSphere, R2L2ContourSphere, R2L3ContourSphere, R2L1ContourScape, R2L2ContourScape, R2L3ContourScape };
	const int ipPlb[] = {R2L1SphereStickPlayback, R2L2SphereStickPlayback, R2L3SphereStickPlayback, R2L1ScapeStickPlayback, R2L2ScapeStickPlayback, R2L3ScapeStickPlayback};
	SynthEditor *se = (SynthEditor *)inf[0];
	CSwitch **sw = se->mSwitch;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	int type = (int)sp[R2Type].GetVal();
	int level = (int)sp[R2ParamLevel].GetVal();
	sw[kSwitchR2CtxContour]->SetParam(sp + ipCnt[3*type + level]);
	sw[kSwitchR2CtxStickPb]->SetParam(sp + ipPlb[3*type + level]);
}

void SynthEditor::stSISwitchCtx( float *in, CParam *param, void **inf )
{
	const int ipCnt[] = {SilverL1Contour,SilverL2Contour,SilverL3Contour};
	const int ipPlb[] = {SilverL1StickPlayback,SilverL2StickPlayback,SilverL3StickPlayback};
	SynthEditor *se = (SynthEditor *)inf[0];
	CSwitch **sw = se->mSwitch;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	int level = (int)sp[SilverParamLevel].GetVal();
	sw[kSwitchSilverCtxContour]->SetParam(sp + ipCnt[level]);
	sw[kSwitchSilverCtxStickPb]->SetParam(sp + ipPlb[level]);
}


///////////////////////////////////////////////////////////////////////////////
// set stick-parameters

const int ipR1V1[] = {R1L1Sphere1Value,R1L2Sphere1Value,R1L3Sphere1Value,R1L1Scape1Value,R1L2Scape1Value,R1L3Scape1Value};
const int ipR1V2[] = {R1L1Sphere2Value,R1L2Sphere2Value,R1L3Sphere2Value,R1L1Scape2Value,R1L2Scape2Value,R1L3Scape2Value};
const int ipR2V1[] = {R2L1Sphere1Value,R2L2Sphere1Value,R2L3Sphere1Value,R2L1Scape1Value,R2L2Scape1Value,R2L3Scape1Value};
const int ipR2V2[] = {R2L1Sphere2Value,R2L2Sphere2Value,R2L3Sphere2Value,R2L1Scape2Value,R2L2Scape2Value,R2L3Scape2Value};

void SynthEditor::stR1StickCtx( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CStick **stk = se->mStick;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam, *stp[2];
	
	int type = (int)sp[R1Type].GetVal();
	int level = (int)sp[R1ParamLevel].GetVal();
	stp[0] = sp + ipR1V1[type*3 + level];
	stp[1] = sp + ipR1V2[type*3 + level];
	stk[kStickR1]->SetView(level,type);
	stk[kStickR1]->SetParam(stp[0], stp[1]);
	if(((SynthCore*)se->mSynth)->remote) ((SynthCore*)se->mSynth)->remote->SetParamStick(0,stp);
}

void SynthEditor::stR1Reset( void *this_p )
{
	SynthEditor *se = (SynthEditor *)this_p;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	for(int i=0; i<6; i++)
	{
		sp[ipR1V1[i]].ResetVal(NFLG_ALL);
		sp[ipR1V2[i]].ResetVal(NFLG_ALL);
	}
}

void SynthEditor::stR2StickCtx( float *in, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	CStick **stk = se->mStick;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam, *stp[2];
	
	int type = (int)sp[R2Type].GetVal();
	int level = (int)sp[R2ParamLevel].GetVal();
	stp[0] = sp + ipR2V1[type*3 + level];
	stp[1] = sp + ipR2V2[type*3 + level];
	stk[kStickR2]->SetView(level,type);
	stk[kStickR2]->SetParam(stp[0], stp[1]);
	if(((SynthCore*)se->mSynth)->remote) ((SynthCore*)se->mSynth)->remote->SetParamStick(1, stp);
}

void SynthEditor::stR2Reset( void *this_p )
{
	SynthEditor *se = (SynthEditor *)this_p;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	for(int i=0; i<6; i++)
	{
		sp[ipR2V1[i]].ResetVal(NFLG_ALL);
		sp[ipR2V2[i]].ResetVal(NFLG_ALL);
	}
}

void SynthEditor::stSIStickCtx( float *in, CParam *param, void **inf )
{
	const int ipFfx1[] = {EQ_Band1Gain,DS_InGain,   RM_Mix,    DC_Mix,     SW_Mix};
	const int ipFfx2[] = {EQ_Band1Freq,DS_PreFilter,RM_ModFreq,DC_SHFactor,SW_Frequency};
	const int ipTfx1[] = {SS_ChanDelay,LRD_Mix, FL_Mix,     PH_Mix,     CH_Mix};
	const int ipTfx2[] = {SS_Feedback, LRD_Time,FL_Feedback,PH_Feedback,CH_Feedback};
	SynthEditor *se = (SynthEditor *)inf[0];
	CStick **stk = se->mStick;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam, *stp[2] = {0,0};
	
	int level = (int)sp[SilverParamLevel].GetVal();
	int ffx = (int)sp[CurFreqFX].GetVal();
	int tfx = (int)sp[CurTimeFX].GetVal();
	
	stk[kStickSilver]->SetView(level,0);
	switch(level)
	{
		case 0: stp[0] = sp + FilterFreq;  stp[1] = sp + FilterReso;  break;
		case 1: stp[0] = sp + ipFfx1[ffx]; stp[1] = sp + ipFfx2[ffx]; break;
		case 2: stp[0] = sp + ipTfx1[tfx]; stp[1] = sp + ipTfx2[tfx]; break;
	}
	stk[kStickSilver]->SetParam(stp[0], stp[1]);
	if(((SynthCore*)se->mSynth)->remote) ((SynthCore*)se->mSynth)->remote->SetParamStick(2 ,stp);
}


///////////////////////////////////////////////////////////////////////////////
// set context-sensed scrollers

void SynthEditor::stR1ScrollerCtx( float *in, CParam *param, void **inf )
{
	const int ipLfo[] = {R1L1Sphere1LfoDepth, R1L2Sphere1LfoDepth, R1L3Sphere1LfoDepth, R1L1Scape1LfoDepth, R1L2Scape1LfoDepth, R1L3Scape1LfoDepth,
		R1L1Sphere2LfoDepth, R1L2Sphere2LfoDepth, R1L3Sphere2LfoDepth, R1L1Scape2LfoDepth, R1L2Scape2LfoDepth, R1L3Scape2LfoDepth};
	const int ipKtr[] = {R1L1Sphere1KeyTrack, R1L2Sphere1KeyTrack, R1L3Sphere1KeyTrack, R1L1Scape1KeyTrack, R1L2Scape1KeyTrack, R1L3Scape1KeyTrack,
		R1L1Sphere2KeyTrack, R1L2Sphere2KeyTrack, R1L3Sphere2KeyTrack, R1L1Scape2KeyTrack, R1L2Scape2KeyTrack, R1L3Scape2KeyTrack};
	const int ipVel[] = {R1L1Sphere1VelocityDepth, R1L2Sphere1VelocityDepth, R1L3Sphere1VelocityDepth, R1L1Scape1VelocityDepth, R1L2Scape1VelocityDepth, R1L3Scape1VelocityDepth,
		R1L1Sphere2VelocityDepth, R1L2Sphere2VelocityDepth, R1L3Sphere2VelocityDepth, R1L1Scape2VelocityDepth, R1L2Scape2VelocityDepth, R1L3Scape2VelocityDepth};
	const int ipEnv[] = {R1L1Sphere1EnvDepth, R1L2Sphere1EnvDepth, R1L3Sphere1EnvDepth, R1L1Scape1EnvDepth, R1L2Scape1EnvDepth, R1L3Scape1EnvDepth,
		R1L1Sphere2EnvDepth, R1L2Sphere2EnvDepth, R1L3Sphere2EnvDepth, R1L1Scape2EnvDepth, R1L2Scape2EnvDepth, R1L3Scape2EnvDepth};
	CScroller **scr = (CScroller **)inf[0];
	CParam  *sp = (CParam *)inf[1];
	
	int type = (int)sp[R1Type].GetVal();
	int level = (int)sp[R1ParamLevel].GetVal();
	int par = (int)sp[R1SelectStickPar].GetVal();
	
	scr[kScrollerR1CtxLfoDepth]->SetParam(sp + ipLfo[6*par + 3*type + level]);
	scr[kScrollerR1CtxKeyTrack]->SetParam(sp + ipKtr[6*par + 3*type + level]);
	scr[kScrollerR1CtxVelDepth]->SetParam(sp + ipVel[6*par + 3*type + level]);
	scr[kScrollerR1CtxEnvDepth]->SetParam(sp + ipEnv[6*par + 3*type + level]);
}

void SynthEditor::stR2ScrollerCtx( float *in, CParam *param, void **inf )
{
	const int ipLfo[] = {R2L1Sphere1LfoDepth, R2L2Sphere1LfoDepth, R2L3Sphere1LfoDepth, R2L1Scape1LfoDepth, R2L2Scape1LfoDepth, R2L3Scape1LfoDepth,
		R2L1Sphere2LfoDepth, R2L2Sphere2LfoDepth, R2L3Sphere2LfoDepth, R2L1Scape2LfoDepth, R2L2Scape2LfoDepth, R2L3Scape2LfoDepth};
	const int ipKtr[] = {R2L1Sphere1KeyTrack, R2L2Sphere1KeyTrack, R2L3Sphere1KeyTrack, R2L1Scape1KeyTrack, R2L2Scape1KeyTrack, R2L3Scape1KeyTrack,
		R2L1Sphere2KeyTrack, R2L2Sphere2KeyTrack, R2L3Sphere2KeyTrack, R2L1Scape2KeyTrack, R2L2Scape2KeyTrack, R2L3Scape2KeyTrack};
	const int ipVel[] = {R2L1Sphere1VelocityDepth, R2L2Sphere1VelocityDepth, R2L3Sphere1VelocityDepth, R2L1Scape1VelocityDepth, R2L2Scape1VelocityDepth, R2L3Scape1VelocityDepth,
		R2L1Sphere2VelocityDepth, R2L2Sphere2VelocityDepth, R2L3Sphere2VelocityDepth, R2L1Scape2VelocityDepth, R2L2Scape2VelocityDepth, R2L3Scape2VelocityDepth};
	const int ipEnv[] = {R2L1Sphere1EnvDepth, R2L2Sphere1EnvDepth, R2L3Sphere1EnvDepth, R2L1Scape1EnvDepth, R2L2Scape1EnvDepth, R2L3Scape1EnvDepth,
		R2L1Sphere2EnvDepth, R2L2Sphere2EnvDepth, R2L3Sphere2EnvDepth, R2L1Scape2EnvDepth, R2L2Scape2EnvDepth, R2L3Scape2EnvDepth};
	CScroller **scr = (CScroller **)inf[0];
	CParam  *sp = (CParam *)inf[1];
	
	int type = (int)sp[R2Type].GetVal();
	int level = (int)sp[R2ParamLevel].GetVal();
	int par = (int)sp[R2SelectStickPar].GetVal();
	
	scr[kScrollerR2CtxLfoDepth]->SetParam(sp + ipLfo[6*par + 3*type + level]);
	scr[kScrollerR2CtxKeyTrack]->SetParam(sp + ipKtr[6*par + 3*type + level]);
	scr[kScrollerR2CtxVelDepth]->SetParam(sp + ipVel[6*par + 3*type + level]);
	scr[kScrollerR2CtxEnvDepth]->SetParam(sp + ipEnv[6*par + 3*type + level]);
}


///////////////////////////////////////////////////////////////////////////////
// shaper focus changed

void SynthEditor::stShaperFocus( float *in, CParam *param, void **inf )
{
	const int ipShp[] = {R1ResEnvA, R1ResEnvD, R1ResEnvS, R1ResEnvR, R1ResEnvMode,
		R1AmpEnvA, R1AmpEnvD, R1AmpEnvS, R1AmpEnvR, R1AmpEnvMode,
		R1FreeEnvA,R1FreeEnvD,R1FreeEnvS,R1FreeEnvR,R1FreeEnvMode, 
		R2ResEnvA, R2ResEnvD, R2ResEnvS, R2ResEnvR, R2ResEnvMode,
		R2AmpEnvA, R2AmpEnvD, R2AmpEnvS, R2AmpEnvR, R2AmpEnvMode,
		R2FreeEnvA,R2FreeEnvD,R2FreeEnvS,R2FreeEnvR,R2FreeEnvMode};
	int idx = (int)(in[1] * 5.);
	const int *ip = &ipShp[ idx ];
	SynthEditor *se = (SynthEditor *)inf[0];
	CScroller **scr = se->mScroller;
	CSwitch **swt = se->mSwitch;
	CParam *sp = ((SynthCore*)se->mSynth)->snddat->mParam;
	
	scr[kScrollerShaper12CtxA]->SetParam(sp + ip[0]);
	scr[kScrollerShaper12CtxD]->SetParam(sp + ip[1]);
	scr[kScrollerShaper12CtxS]->SetParam(sp + ip[2]);
	scr[kScrollerShaper12CtxR]->SetParam(sp + ip[3]);
	swt[kSwitchShaper12CtxMode]->SetParam(sp + ip[4]);
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthEditor::stPagePreCb( float *val, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	td_branch *branch = (td_branch *)inf[1];
	
	if(se->mOpened && branch->isvisible)
	{
		se->ClosePage(branch);
		branch->isvisible = true;
	}
	
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stPagePstCb( float *val, CParam *param, void **inf )
{
	SynthEditor *se = (SynthEditor *)inf[0];
	td_branch *branch = (td_branch *)inf[1];
	
	if(se->mOpened && branch->isvisible)
	{
		se->OpenPage(branch);
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::stBgClick( void *this_p )
{
	SynthEditor *se = (SynthEditor *)this_p;
	
	if(((SynthCore*)se->mSynth)->remote) ((SynthCore*)se->mSynth)->remote->SetRemoteFocus();
}


///////////////////////////////////////////////////////////////////////////////
//
void NASgetEngineVersion(char *version);

void SynthEditor::stAbout( void *this_p )
{
	SynthEditor *se = (SynthEditor *)this_p;
	float val = se->mPgparm[kBranchRoot]->GetVal();
	se->mSwitch[kSwitchMpAbout]->SetMode(SWMD_CONSTANT, se->mPgparm[kBranchRoot]->mMax);
	se->mPgparm[kBranchRoot]->SetVal(999.,NFLG_ALL);
	se->mSwitch[kSwitchMpAbout]->SetMode(SWMD_CONSTANT, val);
	char versionString[128];
	char engineVersion[128];
	NASgetEngineVersion(engineVersion);
	sprintf(versionString, "1.5.5-%s", engineVersion);
	se->mDisplay[kDisplayVersion]->SetText(versionString);
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthEditorCallbacks.cpp,v $
// Revision 1.18  2004/12/02 15:26:11  joffe
// bugfix: editor crash
//
// Revision 1.17  2004/11/30 20:56:33  joffe
// bugfix: slicer switch/type
//
// Revision 1.16  2004/11/26 21:28:11  joffe
// version info changed
//
// Revision 1.15  2004/11/23 09:09:17  joffe
// version info changed
//
// Revision 1.14  2004/11/23 08:14:34  joffe
// warning removed
//
// Revision 1.13  2004/11/23 08:13:12  joffe
// added neuron-vs style slicer switch/type with kb-compatibility
//
// Revision 1.12  2004/11/22 05:37:54  joffe
// version info changed
//
// Revision 1.11  2004/11/11 04:50:52  joffe
// mac-adaptions
//
// Revision 1.10  2004/11/11 04:10:38  joffe
// shaper-resy select as sndparam, name-update for dropdown
//
// Revision 1.9  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.8  2004/11/03 12:44:13  joffe
// knobselect mac-adaption
//
// Revision 1.7  2004/11/03 00:59:35  joffe
// knobselect added
//
// Revision 1.6  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.5  2004/10/19 03:50:36  joffe
// dblclick edit mac adaptions
//
// Revision 1.4  2004/10/18 06:41:34  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.3  2004/09/29 08:19:39  joffe
// scape/sphere bitmap added / page 2 type-button fixed
//
// Revision 1.2  2004/08/26 01:17:46  joffe
// remote added, fixes and improvements
//
// Revision 1.1  2004/08/14 06:23:55  joffe
// remote-stuff added, synth-editor splitup
//
///////////////////////////////////////////////////////////////////////////////
