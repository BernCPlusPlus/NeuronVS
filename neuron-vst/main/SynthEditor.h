///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthEditor.h,v $
// $Revision: 1.11 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SYNTHEDITOR_H
#define SYNTHEDITOR_H

#include "ModuleParams.h"

#include "vstgui.h"
#include "CParam.h"

#include "CBgnd.h"
#include "CSwitch.h"
#include "CScroller.h"
#include "CStick.h"
#include "CShaper.h"
#include "CDial.h"
#include "CDropdown.h"
#include "CArea.h"

#include "SynthCore.h"

///////////////////////////////////////////////////////////////////////////////
// enumeration of all page-branches of the whole page-tree
// this must address the order of array cBranch[]

enum
{
	kBranchRoot,
	kBranchR1Level,
	kBranchR2Level,
	kBranchFreqfx,
	kBranchEqcompr,
	kBranchRingmod,
	kBranchTimefx,
	kBranchFlanger,
	kBranchPhaser,
	kBranchChorus,
	
	kNumBranches
};

extern const long **cBranch[];

#define CID_SWITCH      0x100
#define CID_DISPLAY     0x200
#define CID_SCROLL      0x300
#define CID_STICK       0x400
#define CID_DIAL        0x500
#define CID_SHAPER      0x600
#define CID_DROPDOWN    0x700
#define CID_AREA        0x800



typedef struct _page
{
	CBitmap *bitmap;          // points to a bitmap-resource
	CPoint  offset;           // bitmap position offset
	CBgnd   *bgnd;            // a view for the background
	const long    *controls;  // list of controls for this page 
	int     numsubs;
	struct  _branch *subs;    // points to an array of further branches
	
} td_page;

typedef struct _branch
{
	bool    isvisible;        // true if the branch is visible
	int     pparidx;          // index of the pagenum-parameter
	td_page *page;            // points to an array of pages
	
} td_branch;


class CInput : public CView
{
public:
	
	CInput();
	~CInput();
	
	virtual long notify(CView *sender, const char *message);
	
	CParam        *mParam,*mAS;
	CDisplay      *mSoundNameDisplay;
	ModuleParams  *mMP;
};



class SynthEditor : public AEffGUIEditor, public CControlListener
{
public:
	friend class CInput;
	
	//  SynthEditor(SynthCore *synth);
	SynthEditor(void *synth);
	~SynthEditor();
	bool IsBad();
	
	void BlockEdit(bool block);
	
	virtual long open(void *ptr);
	virtual void close();
	
	
	virtual void valueChanged(CDrawContext* context, CControl* control);
	
private:
	void       *mSynth;
	
	static void stUpdateNames( void *this_p );
	static bool stPagePreCb( float *val, CParam *inParam, void **inInfo );
	static void stPagePstCb( float *val, CParam *inParam, void **inInfo );
	
	void ConfigSwitchGrp( CParam *param, const long *ids );
	void ConfigSwitch(int index, const long *data);
	void ConfigDisplay(int index);
	void ConfigScroller(int index, const long *data);
	void ConfigStick(int index);
	void ConfigDial(int index);
	void ConfigShaperGrp( CParam *param, const long *ids );
	void ConfigShaper(int index, const long *data);
	void ConfigDropdown(int index);
	void ConfigArea(int index);
	
	void BuildTree(td_branch *pact, int index);
	void UnbuildTree(td_branch *pact, int index);
	
	void SetControlsFrame(td_branch *tree, int pagenum, CFrame *frmp);
	void OpenPage(td_branch *tree);
	void ClosePage(td_branch *tree);
	
	bool mError;
	CBitmap   *mBgnd;   // actual and complete background
	td_branch *mTree;   // complete tree of pages
	CParam    **mPgparm;
	CParam::td_notify *mPgntf;
	
	CParam *mActShaper;
	
	CParam::td_notify ntfSound;
	static void       stSound( float *in, CParam *param, void **inf );
	
	CParam            mSndSave;
	CParam::td_notify ntfSndSave;
	static void       stSndSave( float *in, CParam *param, void **inf );
	
	CParam::td_notify ntfR1SwitchCtx;
	CParam::td_notify ntfR2SwitchCtx;
	CParam::td_notify ntfSISwitchCtx;
	static void       stR1SwitchCtx( float *in, CParam *param, void **inf );
	static void       stR2SwitchCtx( float *in, CParam *param, void **inf );
	static void       stSISwitchCtx( float *in, CParam *param, void **inf );
	
	CParam::td_notify ntfR1StickCtx;
	CParam::td_notify ntfR2StickCtx;
	CParam::td_notify ntfSIStickCtx;
	static void       stR1StickCtx( float *in, CParam *param, void **inf );
	static void       stR1Reset( void *this_p );
	static void       stR2StickCtx( float *in, CParam *param, void **inf );
	static void       stR2Reset( void *this_p );
	static void       stSIStickCtx( float *in, CParam *param, void **inf );
	
	CParam::td_notify ntfR1ScrollerCtx;
	CParam::td_notify ntfR2ScrollerCtx;
	static void       stR1ScrollerCtx( float *in, CParam *param, void **inf );
	static void       stR2ScrollerCtx( float *in, CParam *param, void **inf );
	CParam::td_notify ntfShaperFocus;
	static void       stShaperFocus( float *in, CParam *param, void **inf );
	
	CParam::td_notify ntfR1Model;
	CParam::td_notify ntfR2Model;
	static void       stModel( float *in, CParam *param, void **inf );
	
	CParam::td_notify ntfKnob;
	static void       stKnob( float *in, CParam *param, void **inf );
	
	static void stBgClick( void *this_p );
	static void stAbout( void *this_p );
	
	CParam            mSlicerSwitch,mSlicerType;
	CParam::td_notify ntfSlicerSwitch,ntfSlicerType,ntfSlicerVal;
	static void       stSlicerSwitch( float *in, CParam *param, void **inf );
	static void       stSlicerType( float *in, CParam *param, void **inf );
	static void       stSlicerVal( float *in, CParam *param, void **inf );
	
	CInput    mInputSoundName;
	CInput    mInputSoundNumber;
	CInput    mInputR1ModelNumber;
	CInput    mInputR2ModelNumber;
	
	CSwitch         *mSwitch[kNumSwitches];
	CDisplay        *mDisplay[kNumDisplays];
	CScroller       *mScroller[kNumScrollers];
	CStick          *mStick[kNumSticks];
	CDial           *mDial[kNumDials];
	CShaper         *mShaper[kNumShapers];
	CDropdown       *mDropdown[kNumDropdowns];
	CArea           *mArea[kNumAreas];
	
	// Others
	bool mOpened;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthEditor.h,v $
// Revision 1.11  2004/12/02 13:34:25  joffe
// bugfix: editor crash
//
// Revision 1.10  2004/11/23 08:13:12  joffe
// added neuron-vs style slicer switch/type with kb-compatibility
//
// Revision 1.9  2004/11/11 04:09:43  joffe
// shaper-resy select as sndparam, name-update for dropdown
//
// Revision 1.8  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.7  2004/11/03 00:59:35  joffe
// knobselect added
//
// Revision 1.6  2004/10/18 06:41:34  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.5  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.4  2004/08/26 01:17:46  joffe
// remote added, fixes and improvements
//
// Revision 1.3  2004/08/14 06:23:55  joffe
// remote-stuff added, synth-editor splitup
//
// Revision 1.2  2004/08/04 00:32:46  joffe
// some switch-btmaps now smaller, new backrounds, remote displays added,
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
