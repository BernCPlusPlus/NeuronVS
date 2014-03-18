///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModelAdmin.h,v $
// $Revision: 1.2 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MODELADMIN_H
#define MODELADMIN_H


#include "ModelMem.h"
#include "NASengine.h"

#define NUM_MODELS 512

//TODO: Need to prevent simultaneous calls to open/close and perhaps start/stop.

class ModelAdmin
{
public:
	
	static ModelAdmin *stGetInstance(); // singleton
	ModelAdmin();
	~ModelAdmin();
	
	// Model is used by a sound.
	ModelMem *OpenModel(int index); 
	
	// A sound/resy no longer uses this model, but other sounds/resys may still use it.
	void CloseModel(int index); 
	
	// Model is used by a voice.
	void* StartModel(int index, int key); 
	
	// A voice no longer uses this model, but other voices may still use it.
	void StopModel(void* zone); 
	
	void ResetModelAdmin();
	
private:
	void ClearAllModelData();
	
	ModelMem *mModels[NUM_MODELS];
	
	void ClearUnusedModelData();
	
	// DEBUGGUNG ONLY
	void PrintModels();
	
};

#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModelAdmin.h,v $
// Revision 1.2  2004/11/17 16:23:38  joffe
// statics moved out of function-bodies
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
