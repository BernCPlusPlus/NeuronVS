///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthCore.cpp,v $
// $Revision: 1.20 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "SynthCore.h"
#include "SynthEditor.h"


///////////////////////////////////////////////////////////////////////////////
// Constructor

SynthCore::SynthCore(audioMasterCallback audioMaster, bool *error, int numprogs)
: VstWrap(audioMaster, numprogs, NUM_VST_PARAMS)
{
	const char *errfmt = "*** NeuronVS Core(err): %s failed\n";
	*error = false;
	
	remote = 0;
	snddat = 0;
	engine = NULL;
	params = 0;
	noise  = 0;
	editor = 0;
	
	if(audioMaster)
	{
		SynthEditor *sed=0;
		bool err=false, test=true;
		int i;
		
		for(i=0; i<NUM_VST_PARAMS; i++)
		{
			mVstParams[i] = 0;
		}
		
		remote = new CRemote;
		test = (!remote) ? true : remote->IsBad();
		err |= test; if(test) fprintf(stderr,errfmt,"remote");
		
		snddat = new SoundParams;
		test = (!snddat) ? true : snddat->IsBad();
		err |= test; if(test) fprintf(stderr,errfmt,"snddat"); 
		
		engine = NASEngineCreate();
		test = (!engine) ? true : false;
		err |= test; if(test) fprintf(stderr,errfmt,"engine");
		
		params = new ModuleParams(engine,snddat);
		test = (!params) ? true : params->IsBad();
		err |= test; if(test) fprintf(stderr,errfmt,"params");
		
		// need to do this here, examine why
		{
			mActualSound.mMin = 0.;
			mActualSound.mMax = 999.;
			mActualSoundNtf.inf[0] = this;
			mActualSoundNtf.inf[1] = 0;
			mActualSoundNtf.PstCbFn = stNewSound;
			mActualSound.AddNotify(&mActualSoundNtf,true);
		}
		
		noise  = new ModuleEngine(this,engine,params);
		test = (!noise) ? true : noise->IsBad();
		err |= test; if(test) fprintf(stderr,errfmt,"noise");
		
		sed = new SynthEditor(this);
		test = (!sed) ? true : sed->IsBad();
		err |= test; if(test) fprintf(stderr,errfmt,"editor");
		
		if(!err)
		{
			for(i=0; i<NUM_VST_PARAMS; i++)
			{
				const static int autparam[NUM_VST_PARAMS] =
				{
					R1L1Sphere1Value,R1L1Sphere2Value,
					R1L2Sphere1Value,R1L2Sphere2Value,
					R1L3Sphere1Value,R1L3Sphere2Value,
					R1L1Scape1Value,R1L1Scape2Value,
					R1L2Scape1Value,R1L2Scape2Value,
					R1L3Scape1Value,R1L3Scape2Value,
					
					R2L1Sphere1Value,R2L1Sphere2Value,
					R2L2Sphere1Value,R2L2Sphere2Value,
					R2L3Sphere1Value,R2L3Sphere2Value,
					R2L1Scape1Value,R2L1Scape2Value,
					R2L2Scape1Value,R2L2Scape2Value,
					R2L3Scape1Value,R2L3Scape2Value,
					
					FilterFreq, FilterReso,
				};
				
				mVstParamsNtf[i].clear();
				mVstParamsNtf[i].min = 0.;
				mVstParamsNtf[i].max = 1.;
				mVstParamsNtf[i].inf[0] = this;
				mVstParamsNtf[i].inf[1] = (void *)i;
				mVstParamsNtf[i].PstCbFn = stVstParam;
				mVstParams[i] = snddat->mParam + autparam[i];
				mVstParams[i]->AddNotify(&mVstParamsNtf[i],false,NFLG_FORCE|NFLG_ALL);
			}
			
			noise->SetNewPrgCb(stNewPrg,this);
			
			setNumInputs(0);  // no inputs, doesn't work anyways
			setNumOutputs(2); // 2 outputs
			canProcessReplacing();
			hasVu(false);
			hasClip(false);
			isSynth();
			setUniqueID('NAS2');			// NeuronVS tag
			editor = sed;
			
			
			if(remote)
			{
				void (*authcb[])(void*) = {stDeny,stAllow};
				remote->SetAuthCb(authcb,sed);
			}
			
			// SMB NEW
			//			stAllow(sed);
			
		}
		else
		{
			*error = true;
			fprintf(stderr,errfmt,"components");
			this->~SynthCore();
		}
	}
	else
	{
		fprintf(stderr,errfmt,"audiomaster");
		*error = true;
	}
	
	suspend();
}


///////////////////////////////////////////////////////////////////////////////
// Destructor

SynthCore::~SynthCore()
{
	NASEngineInit(engine);
	NASEngineHalt(engine);
	
	if(remote) {delete remote; remote = 0;}
	if(noise)  {delete noise;  noise = 0; }
	if(params) {delete params; params = 0;}
	if(engine) {NASEngineDestroy(engine); engine = NULL;}
	if(snddat) {delete snddat; snddat = 0;}
}

int RaiseThreadSafeAlert(double timeout, CFStringRef alertHeader, CFStringRef alertMessage, CFStringRef defaultButtonTitle, CFStringRef alternateButtonTitle, CFStringRef otherButtonTitle);

///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::stAllow(void *this_p)
{
	SynthEditor* se = (SynthEditor *)this_p;
	int res = RaiseThreadSafeAlert(1, CFSTR("<NUKE> Remote detected!"), NULL, CFSTR("Yay!"), NULL, NULL);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::stDeny(void *this_p)
{
	SynthEditor* se = (SynthEditor *)this_p;
	int res = RaiseThreadSafeAlert(1, CFSTR("No <NUKE> Remote!"), NULL, CFSTR("What!?"), NULL, NULL);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::stNewSound( float *in, CParam *param, void **inf )
{
	SynthCore* sc = (SynthCore *)inf[0];
	SynthEditor *se = (SynthEditor*)sc->editor;
	int index = (int)in[1];
	
	if(se) se->BlockEdit(true);
	sc->params->LoadSound(index);
	if(se) se->BlockEdit(false);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::stVstParam( float *in, CParam *param, void **inf )
{
	SynthCore* sc = (SynthCore *)inf[0];
	int index = (int)inf[1];
	float val = in[1];
	
	sc->setParameterAutomated(index,val);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::stNewPrg( void *this_p, int index )
{
	SynthCore* sc = (SynthCore *)this_p;
	sc->mActualSound.SetVal((float)index,NFLG_ALL);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::getProgramName(char *name)
{
	strcpy(name, "No Program Name");
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::setSampleRate(float sampleRate)
{
	AudioEffectX::setSampleRate(sampleRate);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::setBlockSize(long blockSize)
{
	AudioEffectX::setBlockSize(blockSize);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::resume()
{
	wantEvents();
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthCore::getOutputProperties(long index, VstPinProperties* properties)
{
	if(index < 2 /* num outputs*/)
	{
		sprintf(properties->label, "Neuron %1li", index + 1);
		properties->flags = kVstPinIsActive;
		if(index < 2)
			properties->flags |= kVstPinIsStereo;	// make channel 1+2 stereo
		return true;
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthCore::getEffectName(char* name)
{
	strcpy(name, "NeuronVS");
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthCore::getVendorString(char* text)
{
	strcpy(text, "Hartmann Music GmbH");
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthCore::getProductString(char* text)
{
	strcpy(text, "NeuronVS VST-PlugIn");
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

long SynthCore::getVendorVersion()
{
	return 900;
}


///////////////////////////////////////////////////////////////////////////////
//

long SynthCore::canDo(char* text)
{
	if(!strcmp(text, "receiveVstEvents"))
		return 1;
	if(!strcmp(text, "receiveVstMidiEvent"))
		return 1;
	return -1;	// explicitly can't do; 0 => don't know
}


///////////////////////////////////////////////////////////////////////////////
//

long SynthCore::getNumAutomatableParameters()
{
	return NUM_VST_PARAMS;
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthCore::canParameterBeAutomated(long index)
{
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::setParameter(long index, float value)
{
	if(mVstParams[index])
		mVstParams[index]->SetVal(value,NFLG_OTHERS|NFLG_FORCE,mVstParamsNtf+index);
}


///////////////////////////////////////////////////////////////////////////////
//

float SynthCore::getParameter(long index)
{
	if(mVstParams[index])
		return mVstParams[index]->GetVal(mVstParamsNtf+index);
	else
		return 0.;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::getParameterName (long index, char *label)
{
	sprintf(label,"%24s",mVstParams[index]->mName);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::getParameterDisplay (long index, char *text)
{
	sprintf(text,"---");
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthCore::getParameterLabel (long index, char *label)
{
	sprintf(label,"Unit");
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthCore.cpp,v $
// Revision 1.20  2004/12/02 17:34:32  joffe
// mac adaptions
//
// Revision 1.19  2004/12/02 17:24:12  joffe
// try automation setting vor au
//
// Revision 1.18  2004/12/02 16:22:40  joffe
// engine init moved to params
//
// Revision 1.17  2004/12/02 15:26:11  joffe
// bugfix: editor crash
//
// Revision 1.16  2004/11/30 02:33:36  joffe
// engine shutdown before destruction added
//
// Revision 1.15  2004/11/30 00:11:13  joffe
// automated parameters added
//
// Revision 1.14  2004/11/29 16:45:45  joffe
// Init() before LoadSound() called
//
// Revision 1.13  2004/11/23 10:16:13  joffe
// remote void prg-change draw
//
// Revision 1.12  2004/11/19 15:46:52  joffe
// reporting 1 program for fxpansion host (au)
//
// Revision 1.11  2004/11/19 11:38:07  joffe
// numprograms set to 1
//
// Revision 1.10  2004/11/17 03:03:25  joffe
// mac adaptions
//
// Revision 1.9  2004/11/16 18:17:57  joffe
// some vst-parameters added (au-wrap seems to need this)
//
// Revision 1.8  2004/11/15 14:43:09  joffe
// multiple instances/advanced error-dbg output
//
// Revision 1.7  2004/11/15 14:39:29  joffe
// multiple instances/advanced error-dbg output
//
// Revision 1.6  2004/11/11 04:06:46  joffe
// new program/programname handling, cleanup
//
// Revision 1.5  2004/10/28 09:28:10  joffe
// voice-limitation added
//
// Revision 1.4  2004/09/15 22:42:33  joffe
// errorhandling improved
//
// Revision 1.3  2004/08/26 01:15:42  joffe
// fixes, improvements and auth
//
// Revision 1.2  2004/08/14 06:25:03  joffe
// remote-stuff added
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
