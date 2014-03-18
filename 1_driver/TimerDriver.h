///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: TimerDriver.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TIMERDRIVER_H
#define TIMERDRIVER_H

const unsigned short kTimerRes = 5; // timer resolution in milliseconds

extern class TimerDriver
{
  public:

  TimerDriver();
  ~TimerDriver();

  unsigned volatile long mUpTime;   // uptime in milliseconds
                   
  short SetTimer
  (
    void (*inCallback)(void), // callback-fn for timer-event
    long inTime,    // time in ms to be elapsed after callback is called
                    //   0: callback is called on next granularity
                    //  -1: delete timer
    long inReload   // time in ms to reload timer after callback
                    //  -1: don't reload, so you have a oneshot timer
  );

} gTimerDriver;


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: TimerDriver.h,v $
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
