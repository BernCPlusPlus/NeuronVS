///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: MidiDriver.h,v $
// $Revision: 1.2 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MIDIDRIVER_H
#define MIDIDRIVER_H

class MidiDriver
{
public:
  MidiDriver();
  ~MidiDriver();

  bool Open       // open mididriver, returns success
  (
    void *handle,
//    char  *inDevname,         // name of the device to open
    short inSysexBufSize=0     // buffersize for rxed sysexdata
//    char  ** const ioErrmsg=0 // plain text error-message on fault
  );

  void Close();   // close the instance of the driver

  void SetGetChm      // set callback-function that receives
  (                   //   channel-mode messages (note on/off, pitch etc)
    void (*GetChm)    // callback-fn pointer
    (
      void *this_p,   // reference to caller
      char *inMsg     // midi-message
    ),
    void *this_p      // the caller reference
  );
  
  void SetGetRtm      // set callback-function that receives
  (                   //   realtime messages (start, stop, clock etc)
    void (*GetRtm)    // callback-fn pointer
    (
      void *this_p,   // reference to caller
      char  inRtm     // realtime-message
    ),
    void *this_p      // the caller reference
  );                  
  
  void SetGetSys      // set callback-function that receives
  (                   //   system messages (songpos, mtc, sysex etc)
    void (*GetSys)    // callback-fn pointer
    (
      void *this_p,   // reference to caller
      char *inMsg     // system-message
    ),
    void *this_p      // the caller reference
  );                  

  void SendMsg( char *inMsg );  // send one message to midi-out
  void SendRtm( char inRtm );   // send realtime-message byte

private:
  void *Handle;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: MidiDriver.h,v $
// Revision 1.2  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
