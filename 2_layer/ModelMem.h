///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: ModelMem.h,v $
// $Revision: 1.5 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MODELMEM_H
#define MODELMEM_H

class ModelZone
{
	friend class ModelMem;
public:
	
	int     LowKey;
	int     HiKey;
	int     RootKey;
	int     LowSource;
	int     HiSource;
	char    *LowDataScape;
	char    *LowDataSphere;
	char    *HiDataScape;
	char    *HiDataSphere;
	char    *LowDataScapeFileName;
	char    *LowDataSphereFileName;
	char    *HiDataScapeFileName;
	char    *HiDataSphereFileName;
	int     Detune;
	float   Volume;
	float   Pan;  // Nov 2003: In Model, but not currently used by engine.
	
	ModelZone();
	~ModelZone();
	
	int IncVoiceCount();
	int DecVoiceCount();
	int GetVoiceCount();
	void SetDeleteOnVCZero(bool value);
	bool GetDeleteOnVCZero();
	
	bool SetParam(char *parName, int parValue );
	bool IsValid();
	
	// USE FOR DEBUGGING ONLY
	void Print();
	
private:
	
	int     mVoiceCount;
	bool    mDeleteOnVCZero;
	
	bool LoadScapeAndSphere(int modelIndex);
	char *LoadBinary( char *fileName, unsigned long *size );
	
};


class ModelMem
{
public:
	
	int mIndex;
	ModelZone  *mKeys[128]; // Pointers to the corresponding zones.
	
	ModelMem(int index);
	~ModelMem();
	
	bool Load();
	
	int IncRefCount();
	int DecRefCount();
	int GetRefCount();
	
	void ClearUnusedZones();
	void ClearAllZones();
	
	bool HasZones();
	
	float ScapeParamDefaults[12];
	char  ScapeParamNames[12][9];
	float SphereParamDefaults[12];
	char  SphereParamNames[12][9];
	
private:
	
	typedef struct ModelZoneItem
	{
		ModelZone *mz;
		ModelZoneItem *next;
	};
	
	ModelZoneItem *mZoneList;
	int mRefCount;
	
#if DEBUG
	// USE FOR DEBUGGING ONLY
	void PrintZones();
	void PrintKeys();
#endif
	
};

#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: ModelMem.h,v $
// Revision 1.5  2004/12/02 16:53:55  joffe
// mac adaptions
//
// Revision 1.4  2004/11/11 03:16:15  joffe
// resy-param defaults added
//
// Revision 1.3  2004/08/26 01:01:52  joffe
// parameter-name access added
//
// Revision 1.2  2004/08/04 14:02:03  joffe
// mac engine added
//
// Revision 1.1  2004/07/23 18:17:50  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
