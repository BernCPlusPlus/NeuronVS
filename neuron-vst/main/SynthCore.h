///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthCore.h,v $
// $Revision: 1.10 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SYNTHCORE_H
#define SYNTHCORE_H

#include "VstWrap.h"
#include "SoundParams.h"
#include "SynthEditor.h"
#include "ModuleEngine.h"
#include "ModuleParams.h"
#include "CRemote.h"

#define NUM_VST_PARAMS 26


class SynthCore : public VstWrap
{
public:
	friend class SynthEditor;
	SynthCore(audioMasterCallback audioMaster, bool *error, int numprogs);
	~SynthCore();
	
	virtual void getProgramName (char *name);	
	virtual void setSampleRate (float sampleRate);
	virtual void setBlockSize (long blockSize);
	
	virtual void resume ();
	
	virtual bool getOutputProperties (long index, VstPinProperties* properties);
	
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual long getVendorVersion();
	virtual long canDo(char* text);
	virtual long getNumAutomatableParameters();
	virtual bool canParameterBeAutomated(long index);
	
	virtual void setParameter (long index, float value);
	virtual float getParameter (long index);
	virtual void getParameterLabel (long index, char *label);
	virtual void getParameterDisplay (long index, char *text);
	virtual void getParameterName (long index, char *text);
	
private:
	static void stAllow(void *this_p);
	static void stDeny(void *this_p);
	
	CParam  *mVstParams[NUM_VST_PARAMS];
	CParam::td_notify mVstParamsNtf[NUM_VST_PARAMS];
	CParam  mActualSound;
	CParam::td_notify mActualSoundNtf;
	static void stNewSound( float *in, CParam *param, void **inf );
	static void stVstParam( float *in, CParam *param, void **inf );
	static void stNewPrg( void *this_p, int num );
	
	CRemote      *remote;
	SoundParams  *snddat;
	nas_EngineRef    engine;
	ModuleEngine *noise;
	ModuleParams *params;
	void			*editor;
};

#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthCore.h,v $
// Revision 1.10  2004/12/02 17:24:12  joffe
// try automation setting vor au
//
// Revision 1.9  2004/12/02 13:34:50  joffe
// bugfix: editor crash
//
// Revision 1.8  2004/11/30 00:11:13  joffe
// automated parameters added
//
// Revision 1.7  2004/11/19 15:46:52  joffe
// reporting 1 program for fxpansion host (au)
//
// Revision 1.6  2004/11/16 18:17:57  joffe
// some vst-parameters added (au-wrap seems to need this)
//
// Revision 1.5  2004/11/11 04:06:46  joffe
// new program/programname handling, cleanup
//
// Revision 1.4  2004/09/15 22:42:33  joffe
// errorhandling improved
//
// Revision 1.3  2004/08/26 01:15:42  joffe
// fixes, improvements and auth
//
// Revision 1.2  2004/08/14 06:25:03  joffe
// remote-stuff added
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
