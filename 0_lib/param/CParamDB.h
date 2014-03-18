///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CParamDB.h,v $
// $Revision: 1.5 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// Collection of Parameters and their handling to be saved and loaded
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CPARAMDB_H
#define CPARAMDB_H

#include "CParam.h"


void GetDbName(char *fillname, int numchars);

class CParamDB
{
public: 
	
	CParamDB(int pNumParams);
	~CParamDB();
	bool IsBad();
	
	CParam* mParam; // array of parameters
	
protected:
	bool mError;
	bool LoadRawDB(char *file, float *data, long numparams);
	bool SaveDB(char *folder,char *file);
	
	int mNumParams;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CParamDB.h,v $
// Revision 1.5  2004/11/25 13:56:47  joffe
// path to NeuronDB taken from registry
//
// Revision 1.4  2004/11/22 18:58:24  joffe
// now loading data in raw format, client has to set params manually
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
