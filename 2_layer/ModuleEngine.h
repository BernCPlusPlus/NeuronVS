///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModuleEngine.h,v $
// $Revision: 1.8 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MODULEENGINE_H
#define MODULEENGINE_H

#include "NASengine.h"
#include "AudioDriver.h"
#include "MidiDriver.h"
#include "ModuleParams.h"

class ModuleEngine
{
public:
  ModuleEngine(void *AudioDriverMessage, void *inEngine, ModuleParams *inParams);
  ~ModuleEngine();
  bool IsBad();

  void SetNewPrgCb( void (*callback)(void *, int), void *parent );

private:
  static void stGetChm(void *this_p, char *msg);
  static void stEngineNote( void *this_p, int slot, int key, int vel );
  static void stEngineProcess( void *this_p, float **in, float **out, long samples, long perf );

  void (*mNewPrg)(void *, int);
  void *mNewPrgParent;
  bool mError;

  AudioDriver* mAudio;
  MidiDriver*  mMidi;
  void*   mEngine;
  ModuleParams *mMP;
  float*  mOutCache;
  float** mOut;
  float*  mInCache;
  float** mIn;
//  float   mMvol = 0.1f;
  int     mOch2cp;//,stIch2cp;
//  int   stOskipeng=0,stIskipeng=0;
//  int   stOskipdrv=0,stIskipdrv=0;
  int     mOutCached;

  int     mBank;

  int     mNumVoices;

  nas_NoteRef *mNoteRef;
  bool mNoteStats[128];
  bool *mNoteFlg;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModuleEngine.h,v $
// Revision 1.8  2004/11/30 02:36:22  joffe
// bugfix voice-allocation
//
// Revision 1.7  2004/11/29 19:05:57  joffe
// now off'ed notes preferred for re-use
//
// Revision 1.6  2004/11/17 01:16:05  joffe
// fix: multiple instances
//
// Revision 1.5  2004/11/11 03:59:51  joffe
// soundselect by prgchange/bankselect added
//
// Revision 1.4  2004/10/28 09:28:07  joffe
// voice-limitation added
//
// Revision 1.3  2004/08/26 01:02:50  joffe
// minor fixes
//
// Revision 1.2  2004/08/14 06:15:01  joffe
// old statics now memberized
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
