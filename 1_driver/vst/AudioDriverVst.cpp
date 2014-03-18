///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: AudioDriverVst.cpp,v $
// $Revision: 1.2 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// This is the AudioDriver implementation for Cubase-Vst hosts 
//
///////////////////////////////////////////////////////////////////////////////

#include "../AudioDriver.h"
#include "VstWrap.h"

//AudioDriver gAudioDriver;

AudioDriver::AudioDriver()
{
  // set them default to 0, will be updated corectly by Open()
  mNumInChannels = 0;
  mNumOutChannels = 0; 
}

AudioDriver::~AudioDriver()
{
}


bool AudioDriver::Open(void *handle)
{
  if(handle)
  {
    Handle = handle;
    class VstWrap *vw = (VstWrap *)Handle;

    mNumInChannels = (short)vw->getNumInputs();
    mNumOutChannels = (short)vw->getNumOutputs(); 

    return true;
  }

  return false;
}


void AudioDriver::Close()
{
  if(Handle)
  {
    class VstWrap *vw = (VstWrap *)Handle;
    vw->setProcess(0,0);  // stop processing
  }
}


void AudioDriver::SetAudioProcess(void (*audio_process)( void *, float **, float **, long, long ), void *parent)
{
  class VstWrap *vw = (VstWrap *)Handle;

  vw->setProcess(audio_process,parent);
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: AudioDriverVst.cpp,v $
// Revision 1.2  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
