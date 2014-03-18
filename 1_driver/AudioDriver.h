///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: AudioDriver.h,v $
// $Revision: 1.2 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AUDIODRIVER_H
#define AUDIODRIVER_H

class AudioDriver
{
public:
  AudioDriver();
  ~AudioDriver();

  bool Open       // open audiodriver, returns success
  (
    void *info
//    char  ** const ioErrmsg=0 // plain text error-message on fault
  );

  void Close();   // close the instance of the driver
//  void Start();   // start audio-processing
//  void Stop();    // stop audio-processing

  void SetAudioProcess    // set callback-function that produces
  (                       //   audio-output and receives -input
    void (*AudioProcess)  // callback-fn pointer or NULL
    (
      void *this_p,       // the caller reference
      float **inAudio,    // list of audio-inputs
      float **outAudio,   // list of audio-output
      long  NumSamples,   // number of Samples
      long  CpuLoad       // actual cpu-load in percent
    ),
    void *this_p    // reference to caller
  );

//  volatile short  mCpuLoad;
  short           mNumInChannels;
  short           mNumOutChannels;
//  short           mNumFragments;

private:
  void *Handle;

};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: AudioDriver.h,v $
// Revision 1.2  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
