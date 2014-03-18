///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CParamDB.cpp,v $
// $Revision: 1.11 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <errno.h>

#if WIN32
#include <direct.h>
#include <afxext.h>         // MFC-Erweiterungen
extern "C" { int _afxForceEXCLUDE; }
#elif MAC
#include <sys/stat.h>
#endif

#include "CParamDB.h"
#include "CocoaUtils.h"


///////////////////////////////////////////////////////////////////////////////
//

void GetDbName(char *fillname, int numchars)
{
	//char dbname[8192],*name;
	
	//memset(dbname,0,8192);
	fillname[0] = 0;
	
#if WIN32
	long i,size;
	HKEY hk;
	
	i=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Hartmann Music\\NeuronVS", 0,KEY_READ,&hk);
	if(i!=ERROR_SUCCESS)
	{
		return;
	}
	
	size=8100; 
	long type=REG_SZ;
	char dst[8192];
	memset(dst,0,8192);
	i=RegQueryValueEx(hk,"NeuronDB",0,(unsigned long *)&type,(unsigned char *)&dst,(unsigned long *)&size);
	if(i!=ERROR_SUCCESS)
	{
		return;
	}
	strcat(dst,"/NeuronDB/");
	
	const char *folder = dst;
	
#elif MAC
	
	const char *folder = getActualPathFromResolvedAliases("/Library/Application Support/Hartmann Music/NeuronDB/");
	
#else
	
	const char *folder = "./NeuronDB/";
	
#endif
	
	if(numchars > (int)strlen(fillname)+(int)strlen(folder))
	{
		strcat(fillname,folder);
	}
	else
	{
		fillname[0] = 0;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

CParamDB::CParamDB(int numparams)
{
	mError = false;
	mNumParams = numparams;
	
	if(numparams > 0)
	{
		mParam = new CParam[numparams];
		if(!mParam) mError = true;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

CParamDB::~CParamDB()
{
	if(mParam)
	{
		// TODO: this causes to halt INT3, maybe there's smth. wrong in ~CParam
		//    delete mParam;
	}
}


///////////////////////////////////////////////////////////////////////////////
//

bool CParamDB::IsBad()
{
	return mError;
}


///////////////////////////////////////////////////////////////////////////////
//

bool CParamDB::LoadRawDB(char *file, float *vals, long numparams)
{
	char fileName[32768] = "";
	int i;
	
	GetDbName(fileName,sizeof(fileName)-1000);
	strncat(fileName,file,900);
	
	if (!numparams || !vals)
	{
		return false;
	}
	
	if(numparams>mNumParams) numparams = mNumParams;
	
	// Set all params to default...
	for (i = 0; i < numparams; i++)
	{
		vals[i] = mParam[i].mDef;
	}
	
	FILE *parFile = fopen(fileName, "r");
	if (!parFile)
	{
		return false;
	}
	
	// .. then overwrite with data from file
	
	char line[256] = "";
	char parName[256] = "";
	float parValue;
	
	// fgets() followed by sscanf is safer than doing fscanf(), which may crash given a dodgy file.
	while (fgets(line, 256, parFile) != NULL)
	{
		sscanf(line, "%s %f", parName, &parValue);
		//printf("name = %s val = %f\n", parName, parValue); fflush(stdout);
		for (int i = 0; i < numparams; i++)
		{
			if (strcmp(mParam[i].mName, parName) == 0)
			{
				vals[i] = parValue;
				break;
			}
		}
	}
	fclose(parFile);
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//

bool CParamDB::SaveDB(char *folder, char *file)
{
	if (!mNumParams)
	{
		return false;
	}
	
	char fileName[4096] = "";
	GetDbName(fileName,sizeof(fileName));
	
	strcat(fileName,folder);
#if WIN32
	mkdir(fileName);
#else
	mkdir(fileName, 0777);
#endif
	
	strcat(fileName,"/");
	strcat(fileName,file);
	FILE *parFile = fopen(fileName, "w");
	if (!parFile)
	{
		return false;
	}
	
	for (int i = 0; i < mNumParams; i++)
	{
		fprintf(parFile, "%s\t%d\n", mParam[i].mName, (int)mParam[i].GetVal());
	}
	
	fclose(parFile);
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CParamDB.cpp,v $
// Revision 1.11  2004/12/03 22:33:51  joffe
// new NeuronDB location for mac
//
// Revision 1.10  2004/11/26 12:32:22  joffe
// mac adaptions
//
// Revision 1.9  2004/11/25 13:56:47  joffe
// path to NeuronDB taken from registry
//
// Revision 1.8  2004/11/23 08:06:53  joffe
// bugfix: parameterupdate and wrongly destroyed array
//
// Revision 1.7  2004/11/22 18:58:24  joffe
// now loading data in raw format, client has to set params manually
//
// Revision 1.6  2004/11/11 03:13:36  joffe
// bugfix default parameter settings
//
// Revision 1.5  2004/10/19 06:53:34  joffe
// save-as pc adaptions
//
// Revision 1.4  2004/10/19 06:24:18  joffe
// save-as mac adaptions
//
// Revision 1.3  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.2  2004/08/26 00:46:26  joffe
// improvements for load, bad-flag added
//
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
