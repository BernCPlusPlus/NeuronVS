///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModelMem.cpp,v $
// $Revision: 1.9 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include "NASengine.h"
#include "CParamDB.h"



static bool InitEndianFlag()
{
	short one = 1;
	char *bytes = (char*)&one;
	bool isBigEndian;
	
	if (bytes[0] == 0)
		isBigEndian = true;
	else
		isBigEndian = false;
	
	return isBigEndian;
}	


bool gIsBigEndian = InitEndianFlag();



#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <string.h>
#include <math.h>

#include "ModelMem.h"

ModelMem::ModelMem(int index)
{
	int i;
	
	mIndex = index;
	for (i = 0; i < 128; i++)
	{
		mKeys[i] = 0;
	}
	mZoneList = 0;
	mRefCount = 0; //  need to increase this explicitly
	for (i = 0; i < 12; i++)
	{
		ScapeParamNames[i][0] = 0;
		SphereParamNames[i][0] = 0;
	}
	
}

ModelMem::~ModelMem()
{
	ClearAllZones();
}

int ModelMem::IncRefCount()
{
	return ++mRefCount;
}

int ModelMem::DecRefCount()
{
	if (--mRefCount < 0)
	{
		mRefCount = 0;
	}
	if (mRefCount == 0)
	{
		for (int i = 0; i < 128; i++)
		{
			mKeys[i] = 0;
		}
		ModelZoneItem* current = mZoneList;
		while (current)
		{
			current->mz->SetDeleteOnVCZero(true);
			current = current->next;
		}
	}
	return mRefCount;
}

int ModelMem::GetRefCount()
{
	return mRefCount;
}

bool ModelMem::Load()
{  
	// SMB avoid memory allocation errors
	
//	ClearAllZones();	
	
	char dir[256] = "";
	char mapFileName[256] = "";
	bool err = false;
	
	sprintf(dir, "Models/%03d.model/map.script", mIndex);
	GetDbName(mapFileName,sizeof(mapFileName));
	strcat(mapFileName,dir);
	
	FILE* mapFile = fopen(mapFileName, "r");
	if (!mapFile)
	{
		return false;
	}
	
	char line[256] = "";
	int previousZoneId = -1;
	int zoneId;
	char parName[256];
	int parValue;
	ModelZone *zone = 0;
	ModelZoneItem *zoneItem = 0;
	ModelZoneItem *firstNewInList = 0;
	ModelZoneItem *current = mZoneList;
	
	// Locate the last zone item in the list as there might be some left
	// that are needed for voices that are still active.
	while (current && current->next)
	{
		current = current->next;
	}
	
	// fgets() followed by sscanf is safer than doing fscanf(), which may crash given a dodgy file.
	while (fgets(line, 256, mapFile) != NULL)
	{
		zoneId = -1;
		sprintf(parName, "%s", "");
		parValue = -1000; // Note: values could go down to -99.
		sscanf(line, "%d%s %d", &zoneId, parName, &parValue);
		//printf("zone = %d name = %s val = %d\n", zone, parName, parValue);
		if (zoneId < 0 || zoneId > 127 || !parName || !strcmp(parName, "") || parValue == -1000)
		{
			continue; // skip invalid lines (also version lines).
		}
		
		if (zoneId != previousZoneId)
		{
			zone = new ModelZone();
			zoneItem = new ModelZoneItem;
			if(!zone || !zoneItem)
			{
				err = true;
				break;
			}
			
			zoneItem->mz = zone;
			zoneItem->next = 0;
			
			if (current)
			{
				current->next = zoneItem;
			}
			else // list is empty
			{
				mZoneList = zoneItem;
			}
			current = zoneItem;
			
			if (previousZoneId < 0)
			{
				firstNewInList = zoneItem;
			}
			previousZoneId = zoneId;
		}
		if (zone)
		{
			zone->SetParam(parName, parValue);
		}
	}
	fclose(mapFile);
	
	if(err) return false;
	
	// Load binary model data
	current = firstNewInList;
	int i;
	char name[96];
	char* cp;
	bool unnamed = true;
	
	while (current)
	{
		if (current->mz->IsValid() && (current->mz->HiSource > 0 || current->mz->LowSource > 0))
		{
			if(current->mz->LoadScapeAndSphere(mIndex))
			{
				for (i = current->mz->LowKey; i <= current->mz->HiKey; i++)
				{
					mKeys[i] = current->mz;
				}
				if(unnamed)
				{
					NASgetDefaultScapeParameters((void*)(current->mz->LowDataScape), ScapeParamDefaults);
					NASgetScapeParameterNames((void*)(current->mz->LowDataScape), name);
					for(i=0,cp=name; i<12; i++,cp+=8)
					{
						strncpy(ScapeParamNames[i], cp, 8);
						ScapeParamNames[i][8] = 0;
					}
					
					NASgetDefaultSphereParameters((void*)(current->mz->LowDataSphere), SphereParamDefaults);
					NASgetSphereParameterNames((void*)(current->mz->LowDataSphere), name);
					for(i=0,cp=name; i<12; i++,cp+=8)
					{
						strncpy(SphereParamNames[i], cp, 8);
						SphereParamNames[i][8] = 0;
					}
					
					unnamed = false;
				}
			}
			else
			{
				err = true;
			}
		}
		current = current->next;
	}
	
	// TODO: DEBUGGING ONLY
	//PrintKeys();
	
	return !err;
}

void ModelMem::ClearUnusedZones()
{
	ModelZoneItem* previous = 0;
	ModelZoneItem* current = mZoneList;
	while (current)
	{
		if ((mRefCount == 0 && current->mz->GetVoiceCount() == 0)
			|| (current->mz->GetDeleteOnVCZero() && current->mz->GetVoiceCount() == 0))
		{
			if (current->mz) {
				delete current->mz;
				current->mz = NULL;
			}
			
			if (current == mZoneList) // first in list
			{
				mZoneList = mZoneList->next;
				if (current) {
					delete current; // free list item memory
					current = NULL;
				}
				current = mZoneList;
			}
			else // middle or last in list 
			{
				previous->next = current->next;
				if (current) {
					delete current; // free list item memory
					current = NULL;
				}
				current = previous->next;
			}
		}
		else
		{
			// keep zone data and move on to next item in list
			previous = current;
			current = current->next;
		}
	}
}

void ModelMem::ClearAllZones()
{
	ModelZoneItem* previous = 0;
	ModelZoneItem* current = mZoneList;
	while (current)
	{
		if (current->mz) {
			delete current->mz;
			current->mz = NULL;
		}
		previous = current;
		current = current->next;
		if(previous)
		{
			delete previous; // free list item memory
			previous = NULL;
		}
	}
	mZoneList = NULL;
}

bool ModelMem::HasZones()
{
	return mZoneList != 0;
}

#if DEBUG
// USE FOR DEBUGGING ONLY
void ModelMem::PrintZones()
{
	ModelZoneItem *current = mZoneList;
	int i = 0;
	while (current)
	{
		printf("MODEL %3d, ZONE %3d: ", mIndex, i);
		current->mz->Print();
		printf("\n");
		current = current->next;
		i++;
	}
}

// USE FOR DEBUGGING ONLY
void ModelMem::PrintKeys()
{
	for (int i = 0; i < 128; i++)
	{
		if (mKeys[i])
		{
			printf("MODEL %3d, KEY %3d: ", mIndex, i);
			mKeys[i]->Print();
			printf("\n");
		}
		else
		{
			printf("ERROR in Model %d: Key %d not set.\n", mIndex, i);
		}
	}
}
#endif


//////////////////////////////////////////////////////////////////////
//
// ModelZone
//
/////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------------------------------------------------------------

ModelZone::ModelZone()
{
	LowKey = 0;
	HiKey = 0;
	RootKey = 0;
	LowSource = 0;
	HiSource = 0;
	LowDataScape = NULL;
	LowDataSphere = NULL;
	HiDataScape = NULL;
	HiDataSphere = NULL;

	LowDataScapeFileName = NULL;
	LowDataSphereFileName = NULL;
	HiDataScapeFileName = NULL;
	HiDataSphereFileName = NULL;
	
	
	Detune = 0;
	Volume = 0;
	Pan = 0.0;
	
	mVoiceCount = 0;
	mDeleteOnVCZero = false;
}

// --------------------------------------------------------------------------------------------------------------------------------

ModelZone::~ModelZone()
{
	bool clearHiScape = (LowDataScape != HiDataScape);
	bool clearHiSphere = (LowDataSphere != HiDataSphere);
	
	// SMB HIER IST DER WURM DRIN!!!
	
#ifdef VERBOSE
	printf("deleting LowDataScape\n");
#endif
	if (LowDataScape) {
		
#ifdef DEBUG
		printf("deleting LowDataScape: %s\n", LowDataScapeFileName);
#endif
		if (LowDataScapeFileName) {
			delete[] LowDataScapeFileName;
			LowDataScapeFileName = NULL;
		}
		
		delete[] LowDataScape;
		LowDataScape = NULL;
	}
	
	
	
#ifdef VERBOSE
	printf("deleting LowDataSphere\n");
#endif
	if (LowDataSphere) {
		
#ifdef DEBUG
		printf("deleting LowDataSphere: %s\n", LowDataSphereFileName);
#endif
		if (LowDataSphereFileName) {
			delete[] LowDataSphereFileName;
			LowDataSphereFileName = NULL;
		}
		
		
		
		delete[] LowDataSphere;
		LowDataSphere = NULL;
	}
	if (clearHiScape)
	{
#ifdef VERBOSE
		printf("deleting HiDataScape\n");
#endif
		if (HiDataScape) {
			
#ifdef DEBUG
			printf("deleting HiDataScape: %s\n", HiDataScapeFileName);
#endif
			if (HiDataScapeFileName) {
				delete[] HiDataScapeFileName;
				HiDataScapeFileName = NULL;
			}
			
			
			
			delete[] HiDataScape;
			HiDataScape = NULL;
		}
	}
	if (clearHiSphere)
	{
#ifdef VERBOSE
		printf("deleting HiDataSphere\n");
#endif
		if (HiDataSphere) {
			
#ifdef DEBUG
			printf("deleting HiDataSphere: %s\n", HiDataSphereFileName);
#endif
			if (HiDataSphereFileName) {
				delete[] HiDataSphereFileName;
				HiDataSphereFileName = NULL;
			}
			
			
			delete[] HiDataSphere;
			HiDataSphere = NULL;
		}
	}
}
// --------------------------------------------------------------------------------------------------------------------------------

int ModelZone::IncVoiceCount()
{
	return ++mVoiceCount;
}
// --------------------------------------------------------------------------------------------------------------------------------

int ModelZone::DecVoiceCount()
{
	if (--mVoiceCount < 0)
	{
		mVoiceCount = 0;
	}
	return mVoiceCount;
}
// --------------------------------------------------------------------------------------------------------------------------------

int ModelZone::GetVoiceCount()
{
	return mVoiceCount;
}
// --------------------------------------------------------------------------------------------------------------------------------

void ModelZone::SetDeleteOnVCZero(bool value)
{
	mDeleteOnVCZero = value;
}
// --------------------------------------------------------------------------------------------------------------------------------

bool ModelZone::GetDeleteOnVCZero()
{
	return mDeleteOnVCZero;
}
// --------------------------------------------------------------------------------------------------------------------------------

bool ModelZone::SetParam(char* parName, int parValue)
{
	if (!strcmp(parName, "LowKey"))
	{
		LowKey = parValue;
	}
	else if (!strcmp(parName, "HiKey"))
	{
		HiKey = parValue;
	}
	else if (!strcmp(parName, "RootKey"))
	{
		RootKey = parValue;
	}
	else if (!strcmp(parName, "LowSource"))
	{
		LowSource = parValue;
	}
	else if (!strcmp(parName, "HiSource"))
	{
		HiSource = parValue;
	}
	else if (!strcmp(parName, "Detune"))
	{
		Detune = parValue;
	}
	else if (!strcmp(parName, "Volume"))
	{
		if (parValue > 12)
		{
			parValue = 12;
		}
		else if (parValue < -32)
		{
			parValue = -32;
		}
		Volume = (float)pow(10.0, (float)parValue / 20.0);
	}
	else if (!strcmp(parName, "Pan"))
	{
		if (parValue > 50)
		{
			Pan = 1.0;
		}
		else if (parValue < -50)
		{
			Pan = -1.0;
		}
		else
		{
			Pan = (float)((float)parValue / 50.0);
		}
	}
	else
	{
		return false;
	}
	
	return true;
}
// --------------------------------------------------------------------------------------------------------------------------------

bool ModelZone::IsValid()
{
	if (LowKey < 0) return false;
	if (LowKey > 127) return false;
	if (HiKey < 0) return false;
	if (HiKey > 127) return false;
	if (RootKey < 0) return false;
	if (RootKey > 127) return false;
	
	return true;
}
// --------------------------------------------------------------------------------------------------------------------------------

bool ModelZone::LoadScapeAndSphere(int modelIndex)
{
	char get[256] = "";
	char dir[256] = "";
	char lowVelScapeFileName[256] = "";
	char lowVelSphereFileName[256] = "";
	char hiVelScapeFileName[256] = "";
	char hiVelSphereFileName[256] = "";
	unsigned long size;
	bool err=false;
	
	sprintf(get, "Models/%03d.model", modelIndex);
	GetDbName(dir,sizeof(dir));
	strcat(dir,get);
	
	// Copy source index if only one has been set. 
	if (LowSource == 0 && HiSource > 0)
	{
		LowSource = HiSource;
	}
	if (HiSource == 0 && LowSource > 0)
	{
		HiSource = LowSource;
	}
	
	if (LowSource > 0)
	{
		sprintf(lowVelScapeFileName, "%s/%06d.scape", dir, LowSource);
#ifdef VERBOSE
		printf("Loading low scape: %s\n", lowVelScapeFileName);
#endif
		
		LowDataScapeFileName = new char[strlen(lowVelScapeFileName)+1];
		memset(LowDataScapeFileName, 0, (strlen(lowVelScapeFileName)+1));
		memmove(LowDataScapeFileName, lowVelScapeFileName, strlen(lowVelScapeFileName));
		
		LowDataScape = LoadBinary(lowVelScapeFileName,&size);
		err |= LowDataScape ? false : true;
		//#ifdef MAC
		if (gIsBigEndian) {
			if(LowDataScape) {
#ifdef VERBOSE
				printf("LowDataScape to Mac\n");
#endif
				NASconvertModelDataToMac(LowDataScape,size);
			}
		}
		//#endif
		
		sprintf(lowVelSphereFileName, "%s/%06d.sphere", dir, LowSource);
#ifdef VERBOSE
		printf("Loading low sphere: %s\n", lowVelSphereFileName);
#endif
		LowDataSphereFileName = new char[strlen(lowVelSphereFileName)+1];
		memset(LowDataSphereFileName, 0, (strlen(lowVelSphereFileName)+1));
		memmove(LowDataSphereFileName, lowVelSphereFileName, strlen(lowVelSphereFileName));

		
		LowDataSphere = LoadBinary(lowVelSphereFileName,&size);
		err |= LowDataSphere ? false : true;
		//#ifdef MAC
		if (gIsBigEndian) {
			if(LowDataSphere) {
#ifdef VERBOSE
				printf("LowDataSphere to Mac\n");
#endif
				NASconvertModelDataToMac(LowDataSphere,size);
			}
		}
		//#endif
	}
	
	if (HiSource == LowSource)
	{
		HiDataScape = LowDataScape;
		HiDataScapeFileName = LowDataScapeFileName;
		
		HiDataSphere = LowDataSphere;
		HiDataSphereFileName = LowDataSphereFileName;
	}
	else
	{  
		sprintf(hiVelScapeFileName, "%s/%06d.scape", dir, HiSource);
#ifdef VERBOSE
		printf("Loading hi scape: %s\n", hiVelScapeFileName);
#endif
		HiDataScapeFileName = new char[strlen(hiVelScapeFileName)+1];
		memset(HiDataScapeFileName, 0, (strlen(hiVelScapeFileName)+1));
		memmove(HiDataScapeFileName, hiVelScapeFileName, strlen(hiVelScapeFileName));

		
		HiDataScape = LoadBinary(hiVelScapeFileName,&size);
		err |= HiDataScape ? false : true;
		//#ifdef MAC
		if (gIsBigEndian) {
			if(HiDataScape) {
#ifdef VERBOSE
				printf("HiDataScape to Mac\n");
#endif
				NASconvertModelDataToMac(HiDataScape,size);
			}
		}
		//#endif
		sprintf(hiVelSphereFileName, "%s/%06d.sphere", dir, HiSource);
#ifdef VERBOSE
		printf("Loading hi sphere: %s\n", hiVelSphereFileName);
#endif
		
		HiDataSphereFileName = new char[strlen(hiVelSphereFileName)+1];
		memset(HiDataSphereFileName, 0, (strlen(hiVelSphereFileName)+1));
		memmove(HiDataSphereFileName, hiVelSphereFileName, strlen(hiVelSphereFileName));

		HiDataSphere = LoadBinary(hiVelSphereFileName,&size);
		err |= HiDataSphere ? false : true;
		//#ifdef MAC
		if (gIsBigEndian) {
			if(HiDataSphere) {
#ifdef VERBOSE
				printf("HiDataSphere to Mac\n");
#endif
				NASconvertModelDataToMac(HiDataSphere,size);
			}
		}
		//#endif
	}
    
	return !err;
}
// --------------------------------------------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
//

#ifndef O_BINARY
#define O_BINARY 0
#endif

char *ModelZone::LoadBinary(char *fileName, unsigned long *size)
{
	
#ifdef DEBUG
	printf("Loading data for model '%s'\n", fileName);
#endif
	
	char *data = NULL;
	int dataFile = open(fileName, O_RDONLY|O_BINARY);
	
	if(dataFile)
	{
		*size = (unsigned long)lseek(dataFile, 0, SEEK_END);
		//printf("SIZE of %s is %d\n", fileName, fileSize);
		lseek(dataFile, 0, SEEK_SET);
		
		// TODO: deal with lack of memory
		if (*size > 0) {
			data = new char[*size];
			if (data)
			{
				read(dataFile, data, *size);
			}
		}
		close(dataFile);
	}
	
	return data;
}

// --------------------------------------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
//

#if DEBUG

void ModelZone::Print()
{
	printf("LK[%3d] HK[%3d] RK[%3d] LS[%3d] HS[%3d] DT[%+3d] VL[%f] PN[%f] VC[%3d] DZ[%d]" ,
		   LowKey,
		   HiKey,
		   RootKey,
		   LowSource,
		   HiSource,
		   Detune,
		   Volume,
		   Pan,
		   mVoiceCount,
		   mDeleteOnVCZero);
}

#endif

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModelMem.cpp,v $
// Revision 1.9  2004/12/02 16:53:55  joffe
// mac adaptions
//
// Revision 1.8  2004/12/02 13:30:19  joffe
// bugfix: editor crash
//
// Revision 1.7  2004/11/30 14:57:58  joffe
// nulling object-pointers after delete
//
// Revision 1.6  2004/11/25 13:56:49  joffe
// path to NeuronDB taken from registry
//
// Revision 1.5  2004/11/11 03:16:15  joffe
// resy-param defaults added
//
// Revision 1.4  2004/08/26 01:01:52  joffe
// parameter-name access added
//
// Revision 1.3  2004/08/04 14:02:03  joffe
// mac engine added
//
// Revision 1.2  2004/07/27 02:01:28  joffe
// - NeuronDB location set to /NeuronDB
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
