///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: VstWrap.cpp,v $
// $Revision: 1.1 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "VstWrap.h"
#include "audioeffectx.h"


static void stProcessEmpty(void *, float **, float **, long, long){};
static void stMidiChmEmpty(void *, char *){};


VstWrap::VstWrap (audioMasterCallback audioMaster, long numprogs, long numpars )
: AudioEffectX (audioMaster, numprogs, numpars)
{
	mProcess = stProcessEmpty;
	mMidiChm = stMidiChmEmpty;
}

VstWrap::~VstWrap()
{
}

void VstWrap::setProcess(void (*audio_process)( void *, float **, float **, long, long ), void *parent)
{
	mProcessParent = parent;
	if(audio_process)
	{
		mProcess = audio_process;
	}
	else
	{
		mProcess = stProcessEmpty;
	}
}

void VstWrap::setMidiChm(void (*GetChm)( void *, char * ), void *parent)
{
	mMidiChmParent = parent;
	if(GetChm)
	{
		mMidiChm = GetChm;
	}
	else
	{
		mMidiChm = stMidiChmEmpty;
	}
}

void VstWrap::process (float **inputs, float **outputs, long numSamples)
{
	mProcess(mProcessParent, inputs,outputs,numSamples,10);
}


void VstWrap::processReplacing (float **inputs, float **outputs, long numSamples)
{
	mProcess(mProcessParent, inputs,outputs,numSamples,10);
}


long VstWrap::processEvents (VstEvents *ev)
{
	for (long i = 0; i < ev->numEvents; i++)
	{
		if( (ev->events[i])->type != kVstMidiType)
		{
			continue;
		}
		
		VstMidiEvent *event = (VstMidiEvent *)ev->events[i];
		char *midiData = event->midiData;
		
		mMidiChm(mMidiChmParent, midiData);
		
		event++;
	}
	return 1;	// want more
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: VstWrap.cpp,v $
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
