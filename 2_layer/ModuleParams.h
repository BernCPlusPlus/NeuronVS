///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModuleParams.h,v $
// $Revision: 1.8 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MODULEPARAMS_H
#define MODULEPARAMS_H


#include "ModelMem.h"
#include "SoundParams.h"
#include "ModelAdmin.h"
#include "ConstEnums.h"

#include "CParam.h"
#include "NASengine.h"

//#define	NASengine	NASengineCore


class ModuleParams
{
  friend class ModuleEngine;

public:
  ModuleParams(nas_EngineRef engine, SoundParams *soundData);
  ~ModuleParams();
  bool IsBad();

  void LoadSound(int index);
  void SaveSound(int index);

  void SetModCvsVal(int index, float val);
  void SetPitchBend(float val);

  static void stModelIndexChange( float *inScaledVals, CParam *inParam, void **inInfos );
  static void stGPEngineCb( float *inScaledVals, CParam *inParam, void **inInfos );
  static void stSPEngineCb( float *inScaledVals, CParam *inParam, void **inInfos );
  static void stEPEngineCb( float *inScaledVals, CParam *inParam, void **inInfos );

  char *GetModelName(int modelIndex);
  char *GetSoundName(int soundIndex);
  void SetSoundName(int soundIndex);
  void SetUpdateNamesCb( void (*callback)(void *), void *parent );

private:
  void (*mUpdateNames)(void *parent);
  void *mUpdateNamesParent;
  void Modulate(int changed);

  static void stModDest( float *inScaledVals, CParam *inParam, void **inInfos );
  static void stModDepth( float *inScaledVals, CParam *inParam, void **inInfos );

  bool ReadNames(char *fileName, char names[][32], int numNames, int nameLength);
  bool WriteNames(char *fileName, char names[][32], int numNames, int nameLength);

  bool mError;

  float mR1AmpR;
  float mR2AmpR;
  int   mModCvsDest[cvs_num];
  float mModCvsDepth[cvs_num];
  float mModCvsVal[cvs_num];
  CParam::td_notify mod_dest_ntf[cvs_num];
  CParam::td_notify mod_depth_ntf[cvs_num];

  float mModCvdVal[cvd_num];

  typedef struct
  {
    ModuleParams *mp;
    int engineGroup;
    int engineParam;
    int engineModcv;
  } EngineNtfInfo;

  SoundParams *mSD;
  nas_EngineRef mEngine;

  CParam::td_notify mNtfModelIndexChange;

  CParam::td_notify engine_gp_ntf[kNumEngineGlobalParams];
  CParam::td_notify engine_sp_ntf[kNumEngineSoundParams+cvd_num];
  CParam::td_notify engine_ep_ntf[kNumEngineMFXParams];

  float mEngineGlobalParams[kNumEngineGlobalParams];  
  float mEngineSoundParams[kNumEngineSoundParams];
  float mEngineMFXParams[kNumEngineMFXParams];

  CParam mParamMasterTune;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModuleParams.h,v $
// Revision 1.8  2004/11/23 08:10:11  joffe
// update namelist in dropdown on new soundname
//
// Revision 1.7  2004/11/22 03:09:54  joffe
// bugfix
//
// Revision 1.6  2004/11/11 04:01:25  joffe
// bugfix soundnames/modelnames handling
//
// Revision 1.5  2004/11/02 13:08:17  joffe
// modulation-matrix added
//
// Revision 1.4  2004/10/28 09:28:07  joffe
// voice-limitation added
//
// Revision 1.3  2004/10/18 06:41:31  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.2  2004/08/26 01:04:17  joffe
// parameter-name access added, minor fixes
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
