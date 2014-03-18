///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SoundParams.cpp,v $
// $Revision: 1.8 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "ConstEnums.h"
#include "SoundParams.h"

//int SoundData::sMinIndex = 0;
//int SoundData::sMaxIndex = 999;


typedef struct
{
  char const *name;   // parameter name
  char const *dscr1;  // general purpose description 1
  char const *dscr2;  // general purpose description 2
  float min;          // min allowed value
  float max;          // max allowed value
  float def;          // Default value
  float quant;        // quantizestep, must be >0

} td_parinfo;


const td_parinfo stParInfo[kNumSoundParams] =
{
#define P(name, min, max, preset, quant) \
  {#name, "", "", min, max, preset, quant},
#include "SoundParams.h"
};


SoundParams::SoundParams() : CParamDB(kNumSoundParams)
{
  if(!mError)
  {
    int i;

    for(i=0; i<kNumSoundParams; i++)
    {
      mParam[i].mName = stParInfo[i].name;
      mParam[i].mMin = stParInfo[i].min;
      mParam[i].mMax = stParInfo[i].max;
      mParam[i].mDef = stParInfo[i].def;
      mParam[i].mQuant = stParInfo[i].quant;
      mParam[i].SetVal(stParInfo[i].def);
    }
  }
}

bool SoundParams::Load(int index)
{
  bool retVal = false;
  if (index >= 0 && index < NUM_SOUND_PROGS)
  {
    int i;

    // TODO: stick recordings and snapshots
    char fileName[256] = "";
    float *vals = new float[mNumParams];

    sprintf(fileName, "Sounds/%03d.sound/sound.script", index);
    retVal = LoadRawDB(fileName,vals,mNumParams);

    // do conversions if necessary
    if(vals[SoundVersionMajor]<2.)
    {
      vals[BlenderAmount] -= 64;
    }

    for (i = 0; i < mNumParams; i++)
    {
      mParam[i].SetVal(vals[i], NFLG_NONE);
    }

    for (i = 0; i < mNumParams; i++)
    {
      mParam[i].SetVal(vals[i], NFLG_OTHERS|NFLG_FORCE);
    }

    delete vals;
  }
  return retVal;
}

bool SoundParams::Save(int index)
{
  bool retVal = false;
  if (index >= 0 && index < NUM_SOUND_PROGS)
  {
    // TODO: stick recordings and snapshots
    char folder[256] = "";
    sprintf(folder, "Sounds/%03d.sound", index);
    retVal = SaveDB(folder,"sound.script");
  }
  return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SoundParams.cpp,v $
// Revision 1.8  2004/11/25 13:56:49  joffe
// path to NeuronDB taken from registry
//
// Revision 1.7  2004/11/23 08:08:54  joffe
// bugfix: parameter set and update
//
// Revision 1.6  2004/11/22 18:59:58  joffe
// loading now raw data to allow value-conversion (here: blender-amount)
//
// Revision 1.5  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.4  2004/08/26 01:06:25  joffe
// minor fixes/improvements
//
// Revision 1.3  2004/07/27 02:01:28  joffe
// - NeuronDB location set to /NeuronDB
//
// Revision 1.2  2004/07/23 21:02:45  joffe
// kb-hardware adaptions
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
