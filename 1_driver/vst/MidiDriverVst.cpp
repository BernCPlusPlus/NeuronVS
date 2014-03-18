///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: MidiDriverVst.cpp,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// This is the MidiDriver implementation for Cubase-Vst hosts 
//
///////////////////////////////////////////////////////////////////////////////


#include "../MidiDriver.h"
#include "VstWrap.h"


MidiDriver::MidiDriver()
{
}

MidiDriver::~MidiDriver()
{
}

bool MidiDriver::Open(void *handle, short sxbufsize)
{
  if(handle)
  {
    Handle = handle;
    //class VstWrap *vw = (VstWrap *)Handle;

    return true;
  }

  return false;
}

void MidiDriver::Close()
{
  if(Handle)
  {
    class VstWrap *vw = (VstWrap *)Handle;
    vw->setMidiChm(0,0);
  }
}

void MidiDriver::SetGetChm(void (*GetChm)( void *, char * ), void *parent)
{
  if(Handle)
  {
    class VstWrap *vw = (VstWrap *)Handle;
    vw->setMidiChm(GetChm,parent);
  }
}

/*
void MidiDriver::SetGetRtm(void (*GetChm)( char * ))
{
  class VstWrap *vw = (VstWrap *)Handle;
}

void MidiDriver::SetGetSys(void (*GetChm)( char * ))
{
  class VstWrap *vw = (VstWrap *)Handle;
}
*/


///////////////////////////////////////////////////////////////////////////////
//
// $Log: MidiDriverVst.cpp,v $
// Revision 1.3  2004/08/14 07:20:10  joffe
// removed unused code and vars
//
// Revision 1.2  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
