///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModuleEngine.cpp,v $
// $Revision: 1.14 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "ModuleEngine.h"


///////////////////////////////////////////////////////////////////////////////
//

ModuleEngine::ModuleEngine(void *drvmsg, void *engine, ModuleParams *params)
{
#ifdef DEBUG
  printf("ModuleEngine::new\n");
#endif

  int i;

  mBank = 0;
  mNewPrg = 0;
  mNumVoices = NASgetMaxNumVoices();

  mNoteRef = new nas_NoteRef[mNumVoices];
  memset(mNoteRef,0,mNumVoices*sizeof(nas_NoteRef));
  mNoteFlg = new bool[mNumVoices];
  for(i=0; i<mNumVoices; i++) mNoteFlg[i] = false;
  for(i=0; i<128; i++) mNoteStats[i] = false;

  mMP = params;

  mError = false;

  mAudio = new AudioDriver;
  mError |= !mAudio ? true : !(mAudio->Open(drvmsg));

  mOutCache = new float[nas_NumOutChannels*nas_NumSamples];
  mOut = new float *[nas_NumOutChannels];
  mInCache = new float[nas_NumInChannels*nas_NumSamples];
  mIn = new float *[nas_NumInChannels];
  mOutCached = 0;

  for(i=0; i<nas_NumOutChannels; i++)
  {
    mOut[i] = &mOutCache[i*nas_NumSamples];
  }
  for(i=0; i<nas_NumInChannels; i++)
  {
    mIn[i] = &mInCache[i*nas_NumSamples];
  }
  if(mInCache && mOutCache)
  {
    // see how many channels of engine or driver should be skipped

    if(mAudio->mNumOutChannels < nas_NumOutChannels)
    {
      mOch2cp = mAudio->mNumOutChannels;
    }
    else
    {
      mOch2cp = nas_NumOutChannels;
    }
  }
  mOutCached = 0;
  mAudio->SetAudioProcess(stEngineProcess,this);

  mMidi = new MidiDriver;
  if(mMidi)
  {
    mError |= !(mMidi->Open(drvmsg));
    mMidi->SetGetChm(stGetChm,this);
  }
  else
  {
    mError = false;
  }

  mEngine = engine;
}


///////////////////////////////////////////////////////////////////////////////
//

ModuleEngine::~ModuleEngine()
{
#ifdef DEBUG
  printf("ModuleEngine::del\n");
#endif

  mMidi->Close();
  delete mMidi;
  mAudio->Close();
  delete mAudio;
  delete mInCache;
  delete mOutCache;
  delete mIn;
  delete mOut;
  delete mNoteRef;
  delete mNoteFlg;
}


///////////////////////////////////////////////////////////////////////////////
//

bool ModuleEngine::IsBad()
{
  return mError;
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleEngine::SetNewPrgCb( void (*callback)(void *, int), void *parent )
{
  mNewPrg = callback;
  mNewPrgParent = parent;
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleEngine::stGetChm(void *this_p, char *msg)
{
  ModuleEngine *me = (ModuleEngine *)this_p;
  int prg;

  switch( msg[0] & 0xF0 )
  {
  case 0x80:  // note off
    stEngineNote(this_p, 0,msg[1], 0);
    return;
  case 0x90:  // note on
    stEngineNote(this_p, 0,msg[1], msg[2]);
    return;
  case 0xA0:  // poly pressure
    return;
  case 0xB0:  // control change
    switch(msg[1])
    {
    case 1:
      me->mMP->SetModCvsVal(cvs_Modulation, 1.f/127.f * (float)msg[2]);
      break;
    case 2:
      me->mMP->SetModCvsVal(cvs_Breath, 1.f/127.f * (float)msg[2]);
      break;
    case 3:
      me->mMP->SetModCvsVal(cvs_CC03, 1.f/127.f * (float)msg[2]);
      break;
    case 4:
      me->mMP->SetModCvsVal(cvs_Foot, 1.f/127.f * (float)msg[2]);
      break;
    case 11:
      me->mMP->SetModCvsVal(cvs_Expression, 1.f/127.f * (float)msg[2]);
      break;
    case 32:  // bank-select lo
      me->mBank = msg[2];
      break;
    }
    return;
  case 0xC0:  // program change
    prg = me->mBank*100 + msg[1];
    if(me->mNewPrg) me->mNewPrg(me->mNewPrgParent, prg);
    return;
  case 0xD0:  // aftertouch
    me->mMP->SetModCvsVal(cvs_Aftertouch, 1.f/127.f * (float)msg[1]);
    return;
  case 0xE0:  // pitch bend
    me->mMP->SetPitchBend(1.f/16384.f * (float)(128*msg[2]+msg[1]));
    return;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleEngine::stEngineNote(void *this_p, int slot, int key, int vel )
{
  ModuleEngine *me = (ModuleEngine *)this_p;
	nas_EngineRef eng = me->mEngine;
  ModuleParams *mp = me->mMP;
  int maxvoices = (int)mp->mSD->mParam[SoundNumVoices].GetVal();
  int numvoices = 0;
  long v,msv=-1,nnv=-1,fv=-1,nio=-1;
  float vgain=999999.;
  bool noff;

  for(v = 0; v < me->mNumVoices; v++)
  {
    if(me->mNoteRef[v])
    {
      if(me->mNoteFlg[v]==false)
      {
        // note is offed
        nio = v;
      }

      if(NASEngineGetNoteNumber(me->mNoteRef[v], eng) == key)
      {
        if(nnv<0)
        {
          nnv = v;
        }
//        else
//        {
//          noff = NASnoteOffImmediate(me->mNoteRef[v]);
//          me->mNoteFlg[v] = false;
//        }
      }

      if(NASEngineIsVoicePlaying(me->mNoteRef[v], eng)==true)
      {
        float g = NASEngineGetVoiceGain(me->mNoteRef[v], eng);
        if(g<vgain)
        {
          vgain = g;
          msv = v;
        }
        numvoices++;
      }
      else
      {
        me->mNoteRef[v] = 0;
        me->mNoteFlg[v] = false;
        fv = v;
      }
    }
    else
    {
      fv = v;
    }
  }

  if(vel > 0)
  {
    me->mNoteStats[key] = true;

    if(numvoices >= maxvoices)
    {
      if(nnv>=0)
        noff = NASEngineNoteOffImmediate(me->mNoteRef[fv=nnv], eng);
      else if(nio>=0)
        noff = NASEngineNoteOffImmediate(me->mNoteRef[fv=nio], eng);
      else if(msv>=0)
        noff = NASEngineNoteOffImmediate(me->mNoteRef[fv=msv], eng);
      else
        noff = NASEngineNoteOffImmediate(me->mNoteRef[fv=0], eng);
      numvoices--;
    }

    nas_NoteRef vc = NASEngineNoteOn(key, vel, eng);
    me->mNoteRef[fv] = vc;
    me->mNoteFlg[fv] = true;
	}
  else
  {
    me->mNoteStats[key] = false;

    for(long v = 0; v < me->mNumVoices; v++)
    {
      if(NASEngineGetNoteNumber(me->mNoteRef[v], eng) == key)
      {
        NASEngineNoteOff(me->mNoteRef[v], eng);
        me->mNoteFlg[v] = false;
			}
    }
	}
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleEngine::stEngineProcess( void *this_p, float **in, float **out, long numSamples, long perf )
{
  ModuleEngine *me = (ModuleEngine *)this_p;
  nas_EngineRef eng = me->mEngine;

#if 0
  statics int acc=0, cnt=0;

  if(!(cnt++&31))
  {
    acc/=32;
    printf("\rcpu:%3i%% [%-20s] ", acc, &"||||||||||||||||||||"[20 - ((acc>100)?20:(acc/5))] ); fflush(stdout);
    acc=0;
  }
  else
  {
    acc += perf;
  }
#endif

#if 0
  statics int plop[2]={0};


    for(int j=0; j<2; j++)
    {
float *dp = out[j];

      for(int i = 0; i<numSamples; i++)
      {
        if(plop[j]++&256)
          *dp++ = 0.5;
        else
          *dp++ = -0.5;
      }
    }
#endif



#if 1

  float *sp,*dp;
  int spd = 0; //samples done
  int numouts = me->mOch2cp;


  // at the moment this is not usable for numSamples<nas_NumSamples and
  // also for input-handling. this is a q&d version

  // see whether we have cached stuff
  if(me->mOutCached)
  {
    float clip;
    int numUncache = me->mOutCached>numSamples ? numSamples : me->mOutCached;
    for(int j=0; j<numouts; j++)
    {
      sp = me->mOut[j] + nas_NumSamples - numUncache;
      dp = out[j];
      for(int i = 0; i<numUncache; i++)
      {
        clip = *sp++;
        if(clip*clip>1.) clip=0;
        *dp++ = clip;
      }
    }
    spd += numUncache;
    numSamples -= numUncache;
    me->mOutCached -= numUncache;
  }

  // now process audio
  while((numSamples-=nas_NumSamples)>=0)
  {
    float clip;
    NASEngineProcess(me->mOut[0],me->mOut[1], eng);
    
    for(int j=0; j<numouts; j++)
    {
      sp = me->mOut[j];
      dp = out[j] + spd;
      for(int i = 0; i<nas_NumSamples; i++)
      {
        clip = *sp++;
        if(clip*clip>1.) clip=0;
        *dp++ = clip;
      }
      //setup stCachedFrames and rest
    }
    spd += nas_NumSamples;
  }

  if(numSamples<0)
  {
    float clip;
    numSamples += nas_NumSamples;
    // engine will produce more samples than needed, so
    // turn another round but copy only needed and save the
    // rest
    NASEngineProcess(me->mOut[0],me->mOut[1], eng);
    for(int j=0; j<numouts; j++)
    {
      sp = me->mOut[j];
      dp = out[j] + spd;
      for(int i = 0; i<numSamples; i++)
      {
        clip = *sp++;
        if(clip*clip>1.) clip=0;
        *dp++ = clip;
      }
      //setup stCachedFrames and rest
    }
    // now save the number of cached samples
    me->mOutCached = nas_NumSamples - numSamples;
  }
  
#endif
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModuleEngine.cpp,v $
// Revision 1.14  2004/11/30 17:03:04  joffe
// new engine (pc)
//
// Revision 1.13  2004/11/30 02:36:22  joffe
// bugfix voice-allocation
//
// Revision 1.12  2004/11/29 19:05:57  joffe
// now off'ed notes preferred for re-use
//
// Revision 1.11  2004/11/29 06:49:06  joffe
// NASnoteOffImmediate added
//
// Revision 1.10  2004/11/22 03:12:11  joffe
// voice allocation changed
//
// Revision 1.9  2004/11/17 19:23:48  joffe
// fix: engine init(), halt() and run()
//
// Revision 1.8  2004/11/17 16:23:38  joffe
// statics moved out of function-bodies
//
// Revision 1.7  2004/11/17 01:16:05  joffe
// fix: multiple instances
//
// Revision 1.6  2004/11/11 03:59:51  joffe
// soundselect by prgchange/bankselect added
//
// Revision 1.5  2004/11/02 13:08:17  joffe
// modulation-matrix added
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
