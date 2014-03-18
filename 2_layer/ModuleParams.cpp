///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModuleParams.cpp,v $
// $Revision: 1.17 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "ModuleParams.h"


///////////////////////////////////////////////////////////////////////////////
//

static char stModelNames[NUM_MODELS][32];
static char stSoundNames[NUM_SOUND_PROGS][32];

//char ModuleParams::stModelNames[][32];
//char ModuleParams::stSoundNames[][32];


///////////////////////////////////////////////////////////////////////////////
//

const int cCvsToDest[] =
{
  AftertouchDest,ModulationDest,BreathDest, 
  CC03Dest,FootDest,ExpressionDest
};

const int cCvsToDepth[] =
{
  AftertouchDepth,ModulationDepth,BreathDepth,
  CC03Depth,FootDepth,ExpressionDepth,
};

#define M_MAP(uiidx, cvidx, engineidx, ntflist) engineidx,
const int cCvdToEp[] =
{
#include "MapToEngineDef.h"
};


///////////////////////////////////////////////////////////////////////////////
//

ModuleParams::ModuleParams(nas_EngineRef engine, SoundParams *soundData)
{
#ifdef DEBUG
  printf("ModuleParams::new\n");
#endif

  int i;

  mError = false;
  mSD = soundData;
  mEngine = engine;
  mParamMasterTune.mMin = 440.;
  mParamMasterTune.mMax = 440.;
  mParamMasterTune.SetVal(440.);
  mUpdateNames = 0;

  for(i=cvs_first; i<=cvs_last; i++)
  {
    mModCvsDest[i] = cvd_first;
    mModCvsDepth[i] = 0.;
  }

  NASEngineInit(mEngine);

  char dir[1024] = "";

  // TODO: Need to move this to a more suitable place and handle refreshing etc.
  for(int modelIdx = 0; modelIdx < NUM_MODELS; modelIdx++)
  {
    strcpy(stModelNames[modelIdx], "--<empty>--");
  }

  GetDbName(dir,1000);
  strcat(dir,"ModelNames");
  if(!ReadNames(dir, stModelNames, NUM_MODELS, 11))
  {
    // TODO: build ModelNames from all models
  }

  for(int soundIdx = 0; soundIdx < NUM_SOUND_PROGS; soundIdx++)
  {
    strcpy(stSoundNames[soundIdx], "InitSound");
  }

  GetDbName(dir,1000);
  strcat(dir,"SoundNames");
  if(!ReadNames(dir, stSoundNames, NUM_SOUND_PROGS, 16))
  {
    for(int idx = 0; idx < NUM_SOUND_PROGS; idx++)
    {
      mSD->Load(idx);
      SetSoundName(idx);
    }
    WriteNames(dir, stSoundNames, NUM_SOUND_PROGS, 16);
  }


  EngineNtfInfo *info;

#define NAS_GP(group, param, pmin, pmax)   \
  engine_gp_ntf[param].min = (float)pmin;  \
  engine_gp_ntf[param].max = (float)pmax;  \
  info = new EngineNtfInfo;                \
  info->mp = this;                         \
  info->engineGroup = group;               \
  info->engineParam = param;               \
  info->engineModcv = -1;                  \
  engine_gp_ntf[param].inf[0] = (void*)info; \
  engine_gp_ntf[param].PstCbFn = ModuleParams::stGPEngineCb;

#include "NASengine.h"


#define NAS_SP(group, param, pmin, pmax)   \
  engine_sp_ntf[param].min = (float)pmin;  \
  engine_sp_ntf[param].max = (float)pmax;  \
  info = new EngineNtfInfo;                \
  info->mp = this;                         \
  info->engineGroup = group;               \
  info->engineParam = param;               \
  info->engineModcv = -1;                  \
  engine_sp_ntf[param].inf[0] = (void*)info; \
  engine_sp_ntf[param].PstCbFn = ModuleParams::stSPEngineCb;

#include "NASengine.h"


#define NAS_EP(group, param, pmin, pmax)   \
  engine_ep_ntf[param].min = (float)pmin;  \
  engine_ep_ntf[param].max = (float)pmax;  \
  info = new EngineNtfInfo;                \
  info->mp = this;                         \
  info->engineGroup = group;               \
  info->engineParam = param;               \
  info->engineModcv = -1;                  \
  engine_ep_ntf[param].inf[0] = (void*)info; \
  engine_ep_ntf[param].PstCbFn = ModuleParams::stEPEngineCb;

#include "NASengine.h"


  mNtfModelIndexChange.inf[0] = this;
  mNtfModelIndexChange.PstCbFn = stModelIndexChange;
  mSD->mParam[R1ModellIndex].AddNotify(&mNtfModelIndexChange);
  mSD->mParam[R2ModellIndex].AddNotify(&mNtfModelIndexChange);


#define GP_MAP(uiidx, engineidx, ntflist) \
  mParam##uiidx.AddNotify(&ntflist[engineidx]);

#include "MapToEngineDef.h"


  for(i=cvs_first; i<=cvs_last; i++)
  {
    mod_dest_ntf[i].clear();
    mod_dest_ntf[i].min = cvd_first;
    mod_dest_ntf[i].max = cvd_last;
    mod_dest_ntf[i].inf[0] = this;
    mod_dest_ntf[i].inf[1] = (void *)i;
    mod_dest_ntf[i].PstCbFn = ModuleParams::stModDest;
    mSD->mParam[cCvsToDest[i]].AddNotify(&mod_dest_ntf[i]);

    mod_depth_ntf[i].clear();
    mod_depth_ntf[i].min = -1.;
    mod_depth_ntf[i].max = 1.;
    mod_depth_ntf[i].inf[0] = this;
    mod_depth_ntf[i].inf[1] = (void *)i;
    mod_depth_ntf[i].PstCbFn = ModuleParams::stModDepth;
    mSD->mParam[cCvsToDepth[i]].AddNotify(&mod_depth_ntf[i]);
  }


// TODO: only uses the first sound slot at the moment
#define P_MAP(uiidx, engineidx, ntflist) \
  mSD->mParam[uiidx].AddNotify(&ntflist[engineidx]);

#include "MapToEngineDef.h"


#define M_MAP(uiidx, cvidx, engineidx, ntflist) \
  mSD->mParam[uiidx].AddNotify(&ntflist[engineidx]);    \
  info = (EngineNtfInfo *)(ntflist[engineidx].inf[0]);  \
  info->engineModcv = cvidx;

#include "MapToEngineDef.h"

  
// TODO: Need to add SetUp parameters for master fx. 
// BUT: The notifiers have to be removed from the sound level when we're in SetUp mode.   

//  RunDataTest();
}


///////////////////////////////////////////////////////////////////////////////
//

ModuleParams::~ModuleParams()
{
#ifdef DEBUG
  printf("ModuleParams::del\n");
#endif
  mSD->mParam[R1ModellIndex].RmvNotify(&mNtfModelIndexChange);
  mSD->mParam[R2ModellIndex].RmvNotify(&mNtfModelIndexChange);
}


///////////////////////////////////////////////////////////////////////////////
//

bool ModuleParams::IsBad()
{
  return mError;
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::LoadSound(int index)
{
  char dir[1024] = "";
	
#pragma mark ----- SMB DEBUG -----
	

  NASEngineInit(mEngine);
	
	// SMB +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*	for (int key = 0; key < 128; key++)
    {
		if (mEngine) {
			mEngine->SetModelData(0, key, 0, 0, 0, 0, 0, 0, 0);
			mEngine->SetModelData(1, key, 0, 0, 0, 0, 0, 0, 0);
		}
    }
	
	mEngine->Init();*/

	ModelAdmin *ma = ModelAdmin::stGetInstance();
	ma->ResetModelAdmin();
	NASEngineInit(mEngine);
	// SMB +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  mSD->Load(index);
  SetSoundName(index);
  NASEngineUpdateParameterGroup(0, mEngineSoundParams, mEngine);
  GetDbName(dir,1000);
  strcat(dir,"SoundNames");
  WriteNames(dir, stSoundNames, NUM_SOUND_PROGS, 16);
  if(mUpdateNames) mUpdateNames(mUpdateNamesParent);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::SaveSound(int index)
{
  char dir[1024] = "";

  // reset version info to defaults
  mSD->mParam[SoundVersionMajor].ResetVal();
  mSD->mParam[SoundVersionMinor].ResetVal();
  mSD->mParam[SoundVersionBuild].ResetVal();
  mSD->Save(index);
  GetDbName(dir,1000);
  strcat(dir,"SoundNames");
  WriteNames(dir, stSoundNames, NUM_SOUND_PROGS, 16);
  if(mUpdateNames) mUpdateNames(mUpdateNamesParent);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::SetModCvsVal(int index, float val)
{
  if(index>=cvs_first && index<=cvs_last)
  {
    mModCvsVal[index] = val;
    Modulate(-1);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::SetPitchBend(float val)
{
  NASEngineSetPitchBend(val, mEngine);
  NASEngineUpdateParameterGroup(0, mEngineSoundParams, mEngine);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::Modulate(int changed)
{
  int i,spi,dpi;
  bool copy=true;
  float tmp[cvd_num], min,max;

  // get unmodulated values
  for(i=cvs_first; i<= cvs_last; i++)
  {
    spi = mModCvsDest[i];
    if(changed==spi) copy=false;
    tmp[spi] = mModCvdVal[spi];
  }

  // modulate
  for(i=cvs_first; i<= cvs_last; i++)
  {
    spi = mModCvsDest[i];
    tmp[spi] += mModCvsVal[i]*mModCvsDepth[i];
  }

  // write back modulated values
  for(i=cvs_first; i<= cvs_last; i++)
  {
    spi = mModCvsDest[i];
    dpi = cCvdToEp[spi];
    min = engine_sp_ntf[dpi].min;
    max = engine_sp_ntf[dpi].max;

    mEngineSoundParams[dpi] = tmp[spi]<min ? min : tmp[spi]>max ? max : tmp[spi];
  }

  if(copy) mEngineSoundParams[cCvdToEp[changed]] = mModCvdVal[changed];

  NASEngineUpdateParameterGroup(0, mEngineSoundParams, mEngine);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stModDest( float *ins, CParam *param, void **infos )
{
  ModuleParams* mp = (ModuleParams*)infos[0];
  int index = (int)infos[1];
  int changed = mp->mModCvsDest[index];

  mp->mModCvsDest[index] = (int)ins[1];
  mp->Modulate(changed);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stModDepth( float *ins, CParam *param, void **infos )
{
  ModuleParams* mp = (ModuleParams*)infos[0];
  int index = (int)infos[1];

  mp->mModCvsDepth[index] = ins[1];
  mp->Modulate(-1);
}

  
///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stModelIndexChange( float *ins, CParam *param, void **infos )
{
  void *info = infos[0];
  ModuleParams* mp = (ModuleParams*)info;
  nas_EngineRef engine = mp->mEngine;
  CParam *sp = mp->mSD->mParam;
  int midx = (int)param->GetVal();

  NASEngineHalt(engine);

  ModelAdmin *ma = ModelAdmin::stGetInstance();

  // Note: Have to use German spelling "Modell" as this is how
  // this parameter is held in the Sound file.
  int resy = strcmp(param->mName, "R1ModellIndex") == 0 ? 0 : 1;
  
  // SMB removed ma->CloseModel((int)(ins[0]));
	
//	ma->ResetModelAdmin();
//	engine->Init();
	
	
  ModelMem* model = ma->OpenModel(midx);

  if(model)
  {
    const int ipR1Sc[] = {R1L1Scape1Value,R1L1Scape2Value,R1L2Scape1Value,R1L2Scape2Value,R1L3Scape1Value,R1L3Scape2Value};
    const int ipR1Sp[] = {R1L1Sphere1Value,R1L1Sphere2Value,R1L2Sphere1Value,R1L2Sphere2Value,R1L3Sphere1Value,R1L3Sphere2Value};
    const int ipR2Sc[] = {R2L1Scape1Value,R2L1Scape2Value,R2L2Scape1Value,R2L2Scape2Value,R2L3Scape1Value,R2L3Scape2Value};
    const int ipR2Sp[] = {R2L1Sphere1Value,R2L1Sphere2Value,R2L2Sphere1Value,R2L2Sphere2Value,R2L3Sphere1Value,R2L3Sphere2Value};
    int i;
    const int *ipsc, *ipsp;

    // TODO: switch off any remaining voices (remaining memory will be freed automatically).
    // Also need to turn all sound off to be safe?

    param->mDscr1 = stModelNames[midx];
    if(resy==0)
    {
      ipsc = ipR1Sc;
      ipsp = ipR1Sp;
    }
    else
    {
      ipsc = ipR2Sc;
      ipsp = ipR2Sp;
    }

    for(i=0; i<6; i++)
    {
      const int cIdx[] = {0,1,4,5,8,9};
      int x=cIdx[i];
      int pn;
      
      pn=ipsc[i];
      sp[pn].mDef = model->ScapeParamDefaults[x];
      sp[pn].mDscr1 = model->ScapeParamNames[x];
      sp[pn].mDscr2 = model->ScapeParamNames[x+2];
      if( strcmp(sp[pn].mDscr1,sp[pn].mDscr2) == 0 )
      {
        sp[pn].mDscr2 = "";
      }

      pn=ipsp[i];
      sp[pn].mDef = model->SphereParamDefaults[x];
      sp[pn].mDscr1 = model->SphereParamNames[x];
      sp[pn].mDscr2 = model->SphereParamNames[x+2];
      if( strcmp(sp[pn].mDscr1,sp[pn].mDscr2) == 0 )
      {
        sp[pn].mDscr2 = "";
      }
    }

    for (int key = 0; key < 128; key++)
    {
      if (model->mKeys[key])
      {
        NASEngineSetModelData
        (
          resy, key, model->mKeys[key]->RootKey,
          model->mKeys[key]->LowDataScape, model->mKeys[key]->HiDataScape,
          model->mKeys[key]->LowDataSphere, model->mKeys[key]->HiDataSphere,
          model->mKeys[key]->Detune, model->mKeys[key]->Volume,
		 engine
        );
      }
      else // should never happen, unless the model data is corrupted on the disk
      {
        NASEngineSetModelData(resy, key, 0, 0, 0, 0, 0, 0, 0, engine);
      }
    }
  }

  NASEngineRun(engine);
  NASEngineUpdateParameterGroup(0,mp->mEngineSoundParams, engine);
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stGPEngineCb( float *inScaledVals, CParam *inParam, void **inInfo )
{
  EngineNtfInfo *info = (EngineNtfInfo*)(inInfo[0]);
  info->mp->mEngineGlobalParams[info->engineParam] = inScaledVals[1];
  //TODO: call engine update
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stSPEngineCb( float *inScaledVals, CParam *inParam, void **inInfo )
{
  EngineNtfInfo *info = (EngineNtfInfo*)(inInfo[0]);
  float val = inScaledVals[1];

  if(info->engineModcv >= cvd_first && info->engineModcv <= cvd_last)
  {
    // this is a modulatable parameter
    info->mp->mModCvdVal[info->engineModcv] = val;
    info->mp->Modulate(info->engineModcv);

    if(info->engineParam == nasR1AmpEnvR)
    {
      info->mp->mR1AmpR = val;
      if(info->mp->mEngineSoundParams[info->engineParam] > 5./127.)
      {  
        info->mp->mEngineSoundParams[info->engineParam] = val;
      }
    }
    else if(info->engineParam == nasR2AmpEnvR)
    {
      info->mp->mR2AmpR = val;
      if(info->mp->mEngineSoundParams[info->engineParam] > 5./127.)  
      {  
        info->mp->mEngineSoundParams[info->engineParam] = val;
      }
    }
  }
  else
  {
    info->mp->mEngineSoundParams[info->engineParam] = val;
    // TODO: pass in correct group once they have been agreed and the engine can handle it.
    NASEngineUpdateParameterGroup(0, info->mp->mEngineSoundParams, info->mp->mEngine);
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::stEPEngineCb( float *inScaledVals, CParam *inParam, void **inInfo )
{
  //printf("EP Engine idx = %i, val = %f \n", (int)inInfo, inScaledVal);
  //TODO mEngineMFXParams[(int)inInfo] = inScaledVal;
  //TODO: call engine update
}


///////////////////////////////////////////////////////////////////////////////
//

char *ModuleParams::GetModelName(int modelIndex)
{
  if (modelIndex >= 0 && modelIndex < NUM_MODELS)
  {
    return stModelNames[modelIndex];
  }
  else
  {
    return 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

char *ModuleParams::GetSoundName(int soundIndex)
{
  if (soundIndex >= 0 && soundIndex < NUM_SOUND_PROGS)
  {
    return stSoundNames[soundIndex];
  }
  else
  {
    return 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::SetSoundName(int soundIndex)
{
  if (soundIndex >= 0 && soundIndex < NUM_SOUND_PROGS)
  {
    for(int i=0; i<16; i++)
    {
      stSoundNames[soundIndex][i] = (char)mSD->mParam[SoundNameC00+i].GetVal();
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//

void ModuleParams::SetUpdateNamesCb( void (*callback)(void *), void *parent )
{
  mUpdateNames = callback;
  mUpdateNamesParent = parent;
}


///////////////////////////////////////////////////////////////////////////////
//

bool ModuleParams::ReadNames(char *fileName, char names[][32], int numNames, int nameLength)
{
  FILE *nameFile = fopen(fileName, "r");
  if (!nameFile)
  {
    return false;
  }

  char line[256] = "";
  char name[256] = "";
  int number;

  // fgets() followed by sscanf is safer than doing fscanf(), which may crash given a dodgy file.
  while(fgets(line, 256, nameFile) != NULL)
  {
    sscanf(line, "%d", &number);
    char *cpn = line;
    cpn += strspn(cpn,"\t ");         // skip leading whitespace
    cpn += strspn(cpn,"0123456789");  // skip number
    cpn += strspn(cpn,"\t ");         // skip trailing whitespace 
    sprintf(name,"%s",cpn);

    if (number>=0 && number<numNames)
    {
      if ((int)strlen(name) > nameLength)
      {
        name[nameLength] = '\0';
      }
      strcpy(names[number], name);
    }
    else
    {
      fclose(nameFile);
      return false;
    }
  }

  fclose(nameFile);
  return true;
}


///////////////////////////////////////////////////////////////////////////////
//

bool ModuleParams::WriteNames(char *fileName, char names[][32], int numNames, int nameLength)
{
  FILE *nameFile = fopen(fileName, "w+");
  if (!nameFile)
  {
    return false;
  }

  char *cr = "\n";
  char format[32];
  sprintf(format,"%%0%dd\t%%%ds",3,nameLength);
  char name[256];
  int nml,crl,w;

  for(int i = 0; i < numNames && i < 1000; i++)
  {
    sprintf(name, format, i,names[i]);
    nml = strlen(name);
    crl = strlen(cr);
    w = fwrite(name, 1, nml, nameFile);
    w += fwrite(cr, 1, crl, nameFile);
    if(w != (nml+crl))
    {
      return false;
    }
  }

  fclose(nameFile);
  return true;
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModuleParams.cpp,v $
// Revision 1.17  2004/12/02 16:22:40  joffe
// engine init moved to params
//
// Revision 1.16  2004/11/30 14:56:28  joffe
// parameter-update to engine after model loaded
//
// Revision 1.15  2004/11/25 13:56:49  joffe
// path to NeuronDB taken from registry
//
// Revision 1.14  2004/11/23 08:10:11  joffe
// update namelist in dropdown on new soundname
//
// Revision 1.13  2004/11/22 19:01:38  joffe
// now setting soundversion before save / bugfix readnames()
//
// Revision 1.12  2004/11/22 03:10:41  joffe
// bugfix
//
// Revision 1.11  2004/11/17 19:23:48  joffe
// fix: engine init(), halt() and run()
//
// Revision 1.10  2004/11/11 04:01:25  joffe
// bugfix soundnames/modelnames handling
//
// Revision 1.9  2004/11/02 13:08:17  joffe
// modulation-matrix added
//
// Revision 1.8  2004/10/28 09:28:07  joffe
// voice-limitation added
//
// Revision 1.7  2004/10/19 03:50:35  joffe
// dblclick edit mac adaptions
//
// Revision 1.6  2004/10/18 06:41:31  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.5  2004/08/26 01:04:16  joffe
// parameter-name access added, minor fixes
//
// Revision 1.4  2004/08/14 07:20:10  joffe
// removed unused code and vars
//
// Revision 1.3  2004/08/14 06:13:04  joffe
// rundatatest loaded sound value increments
//
// Revision 1.2  2004/07/27 02:01:28  joffe
// - NeuronDB location set to /NeuronDB
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
