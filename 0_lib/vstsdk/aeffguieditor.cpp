//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 2.2         Date : 20/11/01
//
// © 2003, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// © 2003, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A  PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __aeffguieditor__
#include "aeffguieditor.h"
#endif

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#define kIdleRate    100 // host idle rate in ms
#define kIdleRate2    50
#define kIdleRateMin   4 // minimum time between 2 idles in ms

#if WINDOWS
struct tagMSG windowsMessage;
#endif

#if MOTIF
unsigned long _getTicks ();
#endif

#include <Carbon/Carbon.h>

int RaiseThreadSafeAlert(double timeout, CFStringRef alertHeader, CFStringRef alertMessage, CFStringRef defaultButtonTitle, CFStringRef alternateButtonTitle, CFStringRef otherButtonTitle)
{
	CFOptionFlags result = 0;
	CFUserNotificationDisplayAlert(timeout, kCFUserNotificationPlainAlertLevel, NULL, NULL, NULL, alertHeader, alertMessage, defaultButtonTitle, alternateButtonTitle, otherButtonTitle, &result);
	result &= 0x3;
	return result;
}	



//-----------------------------------------------------------------------------
// AEffGUIEditor Implementation
//-----------------------------------------------------------------------------
AEffGUIEditor::AEffGUIEditor (AudioEffect *pEffect) 
	: AEffEditor (pEffect), frame (0), inIdleStuff (false)
{
	pEffect->setEditor (this);
	systemWindow = 0;
	lLastTicks   = getTicks ();

	#if WINDOWS
	OleInitialize (0);
	#endif
	#if MACX
	void InitMachOLibrary ();
	InitMachOLibrary ();
	#endif
	
	
	
}

//-----------------------------------------------------------------------------
AEffGUIEditor::~AEffGUIEditor () 
{
	#if WINDOWS
	OleUninitialize ();
	#endif
	#if MACX
	void ExitMachOLibrary ();
	ExitMachOLibrary ();
	#endif
}

//-----------------------------------------------------------------------------
#if VST_2_1_EXTENSIONS
long AEffGUIEditor::onKeyDown (VstKeyCode &keyCode)
{
	
	return frame ? frame->onKeyDown (keyCode) : -1;
}

//-----------------------------------------------------------------------------
long AEffGUIEditor::onKeyUp (VstKeyCode &keyCode)
{
	return frame ? frame->onKeyUp (keyCode) : -1;
}
#endif

//-----------------------------------------------------------------------------
void AEffGUIEditor::draw (ERect *ppErect)
{
	ppErect = ppErect;	// not yet supported, is 0!

	if (frame)
		frame->draw ();
}

#if MAC
//-----------------------------------------------------------------------------
long AEffGUIEditor::mouse (long x, long y)
{
	CDrawContext context (frame, systemWindow, systemWindow);
	CPoint where (x, y);

	if (frame)
		frame->mouse (&context, where);

	return 1;
}
#endif

//-----------------------------------------------------------------------------
long AEffGUIEditor::open (void *ptr)
{
	static long gDs=0;
	if (!gDs) {
		gDs=1;
		
		CFStringRef copyright = CFSTR("NeuronVS is freeware. You may use it at no cost. However, it is still copyright (c) 2013 by PROSONIQ PRODUCTS SOFTWARE GmbH with parts used under license from Hartmann Music and its legal successors. All rights are reserved worldwide.\n\nWe welcome you to download it from www.neuronsynth.com and give it to anyone you like, as long as you leave the archive unchanged. Neither the package nor any of its components may be sold or bundled with any software that is sold, including shareware, without written permission. You are not allowed to copy or distribute, or have copied or distributed, copies of the NeuronVS archive or any of its files, in printed or electronic form, via CD ROM or online services.\n\nYou expressly acknowledge and agree that use of NeuronVS is at your exclusive risk. NeuronVS, any related files and documentation are  provided 'AS IS' and without any warranty of any kind, expressed or implied, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose. We make no warranty, express or implied, concerning the reliability of this product, and accept no responsibility for any damages caused by use or misuse of this program. All trademarks and registered trademarks are property of their respective holders.\n\nIN NO EVENT WILL PROSONIQ PRODUCTS SOFTWARE GmbH BE LIABLE FOR ANY DIRECT, INDIRECT SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES RESULTING FROM ANY DEFECT IN THE PRODUCT, INCLUDING LOST PROFITS, DAMAGE TO PROPERTY AND, TO THE EXTENT PERMITTED BY LAW, DAMAGE FOR PERSONAL INJURY, EVEN IF PROSONIQ HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.\n\nAll features and specifications subject to change without notice.");
		
		int res = RaiseThreadSafeAlert(0, CFSTR("DISCLAIMER"), copyright, CFSTR("Okay"), CFSTR("Visit web site"), NULL);
		
		//	 int res = RaiseThreadSafeAlert(0, CFSTR("This is an untested version that fell out of the sky right into my lap - provided 'as is' with no warranties of any kind.\n\n*** USE AT YOUR OWN RISK! ***"), CFSTR("Please note that this build is coming fresh out of an alien time machine, it's completely untamed and entirely untested (except by myself, and you wouldn't want to live in my shoes, wouldn't you). I don't provide any support or warranties of any kind as I don't have the money to hire a lawyer, but if you'd like to send me fan mail or your money please do so at <neuronaut@bernsee.com>.\n\nThe original NeuronVS is (c) 2000-2005 Hartmann Music, with the Neuron DSP engine (c) 1999-2013 Prosoniq Products Software. This build and all of its bug fixes and enhancements is (c) 2013 Stephan Bernsee, created under license from the above.\n\nNote that this version might not work, crash your computer, cause airplanes to fall out of the sky, fry your ears, kill your cat or your speakers, or both. It might cause addiction, loss of hair, loss of sleep, loss of data, loss of faith in the gods of sound or related symptoms. Don't say I didn't warn you. And don't take the blue pill."), CFSTR("Make it so"), CFSTR("Get me outta here"), NULL);
		if (res == 1) {
			system("open http://www.neuronsynth.com &");
			exit(0);
		}
	}
	
	
	// add this to update the value the first time
	postUpdate ();

	return AEffEditor::open (ptr);
}

//-----------------------------------------------------------------------------
void AEffGUIEditor::idle ()
{
#if MAC
	GrafPtr	savePort;
	GetPort (&savePort);
	SetPort ((GrafPtr)GetWindowPort ((WindowRef)systemWindow));

	AEffEditor::idle ();
	if (frame)
		frame->idle ();

	SetPort (savePort);
#else

	#if BEOS
	PlugView *plugView = 0;
	if (frame)
	{
		plugView = (PlugView *) frame->getSystemWindow ();
		if (plugView->LockLooperWithTimeout (0) != B_OK)
			return;
	}
	#else
	if (inIdleStuff)
		return;
	#endif

	AEffEditor::idle ();
	if (frame)
		frame->idle ();
		
	#if BEOS
	if (frame)
		plugView->UnlockLooper ();
	#endif
#endif
}

//-----------------------------------------------------------------------------
long AEffGUIEditor::knobMode = kCircularMode;

//-----------------------------------------------------------------------------
long AEffGUIEditor::setKnobMode (int val) 
{
	AEffGUIEditor::knobMode = val;
	return 1;
}

//-----------------------------------------------------------------------------
bool AEffGUIEditor::onWheel (float distance)
{
	if (frame)
		return frame->onWheel (0, CPoint (), distance);
	
	return false;
}

//-----------------------------------------------------------------------------
void AEffGUIEditor::wait (unsigned long ms)
{
	#if MAC
	unsigned long ticks;
	Delay (ms * 60 / 1000, &ticks);
	
	#elif WINDOWS
	Sleep (ms);

	#elif SGI
	struct timespec sleeptime = {0, ms * 1000000};
	nanosleep (&sleeptime, NULL);

	#elif BEOS
	snooze (ms * 1000);
	#endif
}

//-----------------------------------------------------------------------------
unsigned long AEffGUIEditor::getTicks ()
{
	#if MAC
	return (TickCount () * 1000) / 60;
	
	#elif WINDOWS
	return (unsigned long)GetTickCount ();
	
	#elif MOTIF
	return _getTicks ();

	#elif BEOS
	return (system_time () / 1000);
	#endif

	return 0;
}

//-----------------------------------------------------------------------------
void AEffGUIEditor::doIdleStuff ()
{
	#if !(MAC && !CARBON)
	// get the current time
	unsigned long currentTicks = getTicks ();

	// YG TEST idle ();
	if (currentTicks < lLastTicks)
	{
		#if (MAC && CARBON)
		RunCurrentEventLoop (kEventDurationMillisecond * kIdleRateMin);
		#else
		wait (kIdleRateMin);
		#endif
		currentTicks += kIdleRateMin;
		if (currentTicks < lLastTicks - kIdleRate2)
			return;
	}
	idle (); // TEST

	#if WINDOWS
	if (PeekMessage (&windowsMessage, NULL, WM_PAINT, WM_PAINT, PM_REMOVE))
		DispatchMessage (&windowsMessage);

	#elif MACX
	EventRef event;
	EventTypeSpec eventTypes[] = { {kEventClassWindow, kEventWindowUpdate}, {kEventClassWindow, kEventWindowDrawContent} };
	if (ReceiveNextEvent (GetEventTypeCount (eventTypes), eventTypes, kEventDurationNoWait, true, &event) == noErr)
	{
		SendEventToEventTarget (event, GetEventDispatcherTarget ());
		ReleaseEvent (event);
	}
	#endif

	// save the next time
 	lLastTicks = currentTicks + kIdleRate;
	#endif

	inIdleStuff = true;

	#if !BEOS
	if (effect)
		effect->masterIdle ();
	#endif

	inIdleStuff = false;
}

//-----------------------------------------------------------------------------
long AEffGUIEditor::getRect (ERect **ppErect)
{
	*ppErect = &rect;
	return true;
}

#if MOTIF
//-----------------------------------------------------------------------------
unsigned long _getTicks ()
{
	#if SGI
	long long time;
	syssgi (SGI_GET_UST, &time, 0);
	return time / 1000000;
	
	#elif SUN
	hrtime_t nanosecs = gethrtime ();
	return (unsigned long long)nanosecs / 1000000UL;
	
	#elif LINUX
	// gettimeofday is not what we need here, checkout API for hw time
	struct timeval tv;
	struct timezone tz;
	gettimeofday (&tv, &tz);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	#endif
}
#endif
#if MACX
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
extern "C" {
#include <mach-o/dyld.h>
#include <mach-o/ldsyms.h>
}
#include <CoreFoundation/CFBundle.h>

short localizedResRefNum;
short fixResRefNum;

void* gBundleRef = 0;

// -----------------------------------------------------------------------------
static CFBundleRef _CFXBundleCreateFromImageName (CFAllocatorRef allocator, const char* image_name);
static CFBundleRef _CFXBundleCreateFromImageName (CFAllocatorRef allocator, const char* image_name)
{
	CFURLRef myBundleExecutableURL = CFURLCreateFromFileSystemRepresentation (allocator, (const unsigned char*)image_name, strlen (image_name), false);
	if (myBundleExecutableURL == 0)
		return 0;
		
	CFURLRef myBundleContentsMacOSURL = CFURLCreateCopyDeletingLastPathComponent (allocator, myBundleExecutableURL); // Delete Versions/Current/Executable
	CFRelease (myBundleExecutableURL);
	if (myBundleContentsMacOSURL == 0)
		return 0;

	CFURLRef myBundleContentsURL = CFURLCreateCopyDeletingLastPathComponent (allocator, myBundleContentsMacOSURL); // Delete Current
	CFRelease (myBundleContentsMacOSURL);
	if (myBundleContentsURL == 0)
		return 0;
		
	CFURLRef theBundleURL = CFURLCreateCopyDeletingLastPathComponent (allocator, myBundleContentsURL); // Delete Versions
	CFRelease (myBundleContentsURL);
	if (theBundleURL == 0)
		return 0;

	CFBundleRef result = CFBundleCreate (allocator, theBundleURL);
	CFRelease (theBundleURL);

	return result;
}

// -----------------------------------------------------------------------------
void InitMachOLibrary ();
void InitMachOLibrary ()
{
	const mach_header* header = &_mh_bundle_header;

	const char* imagename = 0;
	/* determine the image name, TODO: ther have to be a better way */
	int cnt = _dyld_image_count();
	for (int idx1 = 1; idx1 < cnt; idx1++) 
	{
		if (_dyld_get_image_header(idx1) == header)
		{
			imagename = _dyld_get_image_name(idx1);
			break;
		}
	}
	if (imagename == 0)
	return;
	/* get the bundle of a header, TODO: ther have to be a better way */
	gBundleRef = (void*)_CFXBundleCreateFromImageName (NULL, imagename);
}

// -----------------------------------------------------------------------------
void ExitMachOLibrary ();
void ExitMachOLibrary ()
{
	if (gBundleRef)
		CFRelease (gBundleRef);
}

#endif
