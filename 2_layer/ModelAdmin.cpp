///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModelAdmin.cpp,v $
// $Revision: 1.5 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <string.h>
#include <math.h>

#include "ModelAdmin.h"

static ModelAdmin stInstance;

ModelAdmin::ModelAdmin()
{
	
	for (int i = 0; i < NUM_MODELS; i++)
	{
		mModels[i] = new ModelMem(i);
	}
}

ModelAdmin::~ModelAdmin()
{
	for (int i = 0; i < NUM_MODELS; i++)
	{
		if (mModels[i]) {
			delete mModels[i];
			mModels[i] = NULL;
		}
	}
}


ModelAdmin* ModelAdmin::stGetInstance()
{
	return &stInstance;
}

// Model is used by a sound.
ModelMem* ModelAdmin::OpenModel(int index)
{
	bool err=false;
	
	mModels[index]->IncRefCount();
	if (mModels[index]->GetRefCount() == 1)
	{
		err = !(mModels[index]->Load());
	}
	
	// TODO: DEBUGGING ONLY
	//PrintModels();
	
	return err ? 0 : mModels[index];
}

// A sound/resy no longer uses this model, but other sounds/resys may still use it.
void ModelAdmin::CloseModel(int index)
{
	mModels[index]->DecRefCount();
	ClearUnusedModelData();
	//	ClearAllModelData();
}

// Model is used by a voice.
void* ModelAdmin::StartModel(int index, int key)
{
	mModels[index]->mKeys[key]->IncVoiceCount();  
	return (void*)mModels[index]->mKeys[key];
}

// A voice no longer uses this model, but other voices may still use it.
void ModelAdmin::StopModel(void* zone) 
{
	if (zone)
	{
		ModelZone *mz = (ModelZone*)zone;
		mz->DecVoiceCount();
	}
	ClearUnusedModelData();
}


void ModelAdmin::ClearUnusedModelData()
{
	for (int i = 0; i < NUM_MODELS; i++)
	{
		mModels[i]->ClearUnusedZones();
	}
}

void ModelAdmin::ResetModelAdmin()
{
	for (int i = 0; i < NUM_MODELS; i++)
	{
		if (mModels[i]) {
			delete mModels[i];
			mModels[i] = NULL;
		}
		mModels[i] = new ModelMem(i);
	}
}

void ModelAdmin::ClearAllModelData()
{
	for (int i = 0; i < NUM_MODELS; i++)
	{
		mModels[i]->ClearAllZones();
	}
}

// DEBUGGING ONLY
void ModelAdmin::PrintModels()
{
	// TODO: Debugging only! A real hack - should do this properly.
	FILE *logFile = fopen("./NeuronVSDebug.log", "a+");
	if (logFile)
	{
		fprintf(logFile, "   ##### Models with Zones\n");
		for (int i = 0; i < NUM_MODELS; i++)
		{
			if (mModels[i]->HasZones())
			{
				fprintf(logFile, "Model[%3d] Ref[%d] FirstKey[%d]\n", i, mModels[i]->GetRefCount(), mModels[i]->mKeys[0]);
			}
		}
		fclose(logFile);
	}
	
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModelAdmin.cpp,v $
// Revision 1.5  2004/11/30 14:57:58  joffe
// nulling object-pointers after delete
//
// Revision 1.4  2004/11/17 16:23:38  joffe
// statics moved out of function-bodies
//
// Revision 1.3  2004/10/18 06:41:31  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.2  2004/08/26 00:59:39  joffe
// minor fixes
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
