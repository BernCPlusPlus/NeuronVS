///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: AppMain.cpp,v $
// $Revision: 1.4 $
//
// (C) J. Fornoff (jf@sub-out.de)
//
// View Change Log at end of file
//
// This is the Vst-Plugin main file, a lot adopted from vstsdk examples
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "SynthCore.h"


#if 0



#if MAC
#pragma export on
#endif

///////////////////////////////////////////////////////////////////////////////
// prototype of global main

#if MACX
#define main main_macho
extern "C" AEffect *main_macho(audioMasterCallback audioMaster);
#else
AEffect *main(audioMasterCallback audioMaster);
#endif


AEffect *main(audioMasterCallback audioMaster)
{
	// get VST version
	if(!audioMaster(0, audioMasterVersion, 0, 0, 0, 0))
	{
		fprintf(stderr,"*** NeuronVS main(err1): wrong version\n");
		return 0; // won't fit
	}
	
	// create plugin
	bool error = false;
	char test[65];
	test[0]=test[64]=0;
	audioMaster(0, audioMasterGetVendorString, 0, 0, test, 0);
	int numprogs = strncmp(test,"FXpansion",9) ? 0:1;
	
	SynthCore *plugin = new SynthCore(audioMaster,&error,numprogs);
	if(!plugin || error)
	{
		fprintf(stderr, "*** NeuronVS main(err2): %s failed\n", (error) ? "Init":"Core");
		return 0; // new failed
	}
	
	AEffect *r = plugin->getAeffect();
	//fprintf(stderr, "*** NeuronVS main(ret): 0x%08lX\n", r);
	return r;
}

#if MAC
#pragma export off
#endif


///////////////////////////////////////////////////////////////////////////////
// win-dlls use a dllmain

#if WIN32
#include <windows.h>
void *hInstance;  // whoever needs this...
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	hInstance = hInst;
	return 1;
}
#endif


#else

#if MAC
#pragma export on
#endif


extern "C" {
	
#if defined (__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define VST_EXPORT	__attribute__ ((visibility ("default")))
#else
#define VST_EXPORT
#endif
	
	//------------------------------------------------------------------------
	/** Prototype of the export function main */
	//------------------------------------------------------------------------
	VST_EXPORT AEffect* VSTPluginMain (audioMasterCallback audioMaster)
	{
		bool error = false;
		// Get VST Version of the Host
		if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
			return 0;  // old version
		
		SynthCore *plugin = new SynthCore(audioMaster,&error,0);
		if(!plugin || error)
		{
			fprintf(stderr, "*** NeuronVS main(err2): %s failed\n", (error) ? "Init":"Core");
			return 0; // new failed
		}
		
		AEffect *r = plugin->getAeffect();
		//fprintf(stderr, "*** NeuronVS main(ret): 0x%08lX\n", r);
		return r;
	}
	
	// support for old hosts not looking for VSTPluginMain
#if (TARGET_API_MAC_CARBON /*&& __ppc__*/)
	VST_EXPORT AEffect* main_macho (audioMasterCallback audioMaster) { return VSTPluginMain (audioMaster); }
#elif WIN32
	VST_EXPORT AEffect* MAIN (audioMasterCallback audioMaster) { return VSTPluginMain (audioMaster); }
#elif BEOS
	VST_EXPORT AEffect* main_plugin (audioMasterCallback audioMaster) { return VSTPluginMain (audioMaster); }
#endif
	
} // extern "C"


#if MAC
#pragma export off
#endif


//------------------------------------------------------------------------
#if WIN32
#include <windows.h>
void* hInstance;

extern "C" {
	BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
	{
		hInstance = hInst;
		return 1;
	}
} // extern "C"
#endif






#endif

///////////////////////////////////////////////////////////////////////////////
//
// $Log: AppMain.cpp,v $
// Revision 1.4  2004/11/19 15:46:52  joffe
// reporting 1 program for fxpansion host (au)
//
// Revision 1.3  2004/11/15 14:39:28  joffe
// multiple instances/advanced error-dbg output
//
// Revision 1.2  2004/09/15 22:42:33  joffe
// errorhandling improved
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
