///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: VstWrap.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This is a wrapper allowing to build vst-plugins that make use of the own
// designed very portable driver-architecture
//
///////////////////////////////////////////////////////////////////////////////

#ifndef VSTWRAP_H
#define VSTWRAP_H


#include "audioeffectx.h"
//#include "audioeffectx.h"


class VstWrap : public AudioEffectX
{
public:
	VstWrap(audioMasterCallback audioMaster, long numPrograms, long numParams);
	~VstWrap();
	
	void setProcess    // set callback-function that produces
	(                       //   audio-output and receives -input
	 void (*AudioProcess)  // callback-fn pointer, to switch off set to 0
	 (
      void *this_p,       // the caller reference
      float **inAudio,    // list of audio-inputs
      float **outAudio,   // list of audio-output
      long  NumSamples,   // number of Samples
      long  CpuLoad       // actual cpu-load in percent
	  ),
	 void *this_p    // reference to caller
	 );
	
	void setMidiChm   // set callback-function for MIDI-channelmode messages
	(
	 void (*GetChm)        // callback-fn pointer, to switch off set to 0
	 (
      void *this_p,       // the caller reference
      char *MidiMsg       // midi-message typical 2 or 3 bytes, incl. channel
	  ),
	 void *this_p    // reference to caller
	 );
	
	// here you can get the number of inputs and outputs
	virtual long getNumInputs(void){ return cEffect.numInputs; };  
	virtual long getNumOutputs(void){ return cEffect.numOutputs; };  
	
	// these are wrapped from AudioEffectX, see vstsdk-docs for further infos
	virtual void process (float **inputs, float **outputs, long sampleframes);
	virtual void processReplacing (float **inputs, float **outputs, long sampleframes);
	virtual long processEvents (VstEvents* events);
	
private:
	void (*mProcess)( void *, float **in, float **out, long samples, long perf );
	void *mProcessParent;
	void (*mMidiChm)( void *, char * );
	void *mMidiChmParent;
	
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: VstWrap.h,v $
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
