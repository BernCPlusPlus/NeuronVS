///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SynthEditor.cpp,v $
// $Revision: 1.19 $
//
// (C) J.Pogadl, J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#define EDIT_WIDTH  800
#define EDIT_HEIGHT 652

#include "SynthEditor.h"

#include "CParam.h"
#include "SoundParams.h"

#include "resource.h"

#include <stdio.h>


#define IS_CID_SWITCH      0x0000 + CID_SWITCH
#define IS_CID_DISPLAY     0x0000 + CID_DISPLAY
#define IS_CID_SCROLL      0x0000 + CID_SCROLL
#define IS_CID_STICK       0x0000 + CID_STICK
#define IS_CID_DIAL        0x0000 + CID_DIAL
#define IS_CID_SHAPER      0x0000 + CID_SHAPER
#define IS_CID_DROPDOWN    0x0000 + CID_DROPDOWN
#define IS_CID_AREA        0x0000 + CID_AREA


///////////////////////////////////////////////////////////////////////////////
// construct the editor

SynthEditor::SynthEditor(void *synth)
: AEffGUIEditor((SynthCore*)synth) 
{
	// mark editor as closed
	mError = false;
	mOpened = false;
	mSynth = synth;
	//	mOpenCount = 0;
	
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	
	CParam *sdp = M_SYNTH->snddat->mParam;
	
	// init the size of the plugin
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = EDIT_WIDTH;
	rect.bottom = EDIT_HEIGHT;
	
	// create page tree 
	mTree = new td_branch;
	mPgntf = new CParam::td_notify[kNumBranches];
	mPgparm = new CParam *[kNumBranches];
	mActShaper = sdp + ShaperResySelect;
	
	// set up the parameters that handle page-switching
	mPgparm[kBranchRoot] = new CParam;
	mPgparm[kBranchR1Level] = sdp + R1ParamLevel;
	mPgparm[kBranchR2Level] = sdp + R2ParamLevel;
	mPgparm[kBranchFreqfx] = sdp + CurFreqFX;
	mPgparm[kBranchTimefx] = sdp + CurTimeFX;
	mPgparm[kBranchEqcompr] = new CParam;
	mPgparm[kBranchRingmod] = new CParam;
	mPgparm[kBranchFlanger] = new CParam;
	mPgparm[kBranchPhaser] = new CParam;
	mPgparm[kBranchChorus] = new CParam;
	
	// build the tree
	memset(mSwitch,0,sizeof(mSwitch));
	memset(mDisplay,0,sizeof(mDisplay));
	memset(mScroller,0,sizeof(mScroller));
	memset(mStick,0,sizeof(mStick));
	memset(mShaper,0,sizeof(mShaper));
	memset(mDial,0,sizeof(mDial));
	memset(mDropdown,0,sizeof(mDropdown));
	memset(mArea,0,sizeof(mArea));
	
	BuildTree(mTree,kBranchRoot);
	
	// slicer workaround
	ntfSlicerSwitch.clear();
	ntfSlicerSwitch.inf[0] = this;
	ntfSlicerSwitch.PstCbFn = stSlicerSwitch;
	ntfSlicerType.clear();
	ntfSlicerType.inf[0] = this;
	ntfSlicerType.PstCbFn = stSlicerType;
	ntfSlicerVal.clear();
	ntfSlicerVal.inf[0] = this;
	ntfSlicerVal.PstCbFn = stSlicerVal;
	M_SYNTH->snddat->mParam[SlicerSwitchType].AddNotify(&ntfSlicerVal,true);
}


///////////////////////////////////////////////////////////////////////////////
// destroy the editor

SynthEditor::~SynthEditor()
{
	if(mOpened) close();
	
	UnbuildTree(mTree,kBranchRoot);
	
	mPgparm[kBranchR1Level] = 0;
	mPgparm[kBranchR2Level] = 0;
	mPgparm[kBranchFreqfx] = 0;
	mPgparm[kBranchTimefx] = 0;
	
	for(int i=0; i<kNumBranches; i++)
	{
		if(mPgparm[i]) delete mPgparm[i];
	}
	delete mPgparm;
	delete mPgntf;
	delete mTree;
}


///////////////////////////////////////////////////////////////////////////////
//

bool SynthEditor::IsBad()
{
	return mError;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::BlockEdit(bool block)
{
	if(mTree && mOpened)
	{
		if(block)
		{
			ClosePage(mTree);
		}
		else
		{
			OpenPage(mTree);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// open the editor

// SMB NEW: static int gResult=0;

long SynthEditor::open(void *ptr)
{
	
	// Steinberg says: !!! always call this !!!
	AEffGUIEditor::open(ptr);
	
	
	// init background frame
	CRect size(0, 0, EDIT_WIDTH, EDIT_HEIGHT);
	frame = new CFrame(size, ptr, this);
	mBgnd = new CBitmap(*frame, EDIT_WIDTH, EDIT_HEIGHT);
	CDrawContext      *srccon = new CDrawContext(frame,0);
	COffscreenContext *dstcon = new COffscreenContext(srccon,mBgnd,true);
	dstcon->setFillColor(kGreyCColor);
	dstcon->floodFill(CPoint(0,0));
	delete dstcon;
	delete srccon;
	frame->setBackground(mBgnd);
	
	SynthCore *M_SYNTH = (SynthCore*)mSynth;
	M_SYNTH->params->SetUpdateNamesCb(stUpdateNames,this);
	
	// set editor opened flag
	OpenPage(mTree);
	mOpened = true;
	return true;
}


///////////////////////////////////////////////////////////////////////////////
// close the editor

void SynthEditor::close()
{
	// clear opened flag
	mOpened = false;
	
	ClosePage(mTree);
	
	// destroy background frame
	frame->setBackground(0);
	if(mBgnd) mBgnd->forget(); // sdkdoc says forget() destroys itself
	if(frame) {
		delete frame;
		frame = 0;
	}
	//for(int scheis=0; scheis<7; scheis++) dspl[scheis]->SetFrame(frame,CPoint(0,0));
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::BuildTree(td_branch *pact, int index)
{
	int numpages,ki,pi,j,cid,cvl;
	const long **pagelist = cBranch[index];
	const long *pagedat;
	CBitmap *bgndbmp = 0;
	CPoint  bgndofs;
	
	// count number of pages and alloc
	for(numpages=0; pagelist[numpages] && numpages<100; numpages++);
	pact->page = new td_page[numpages];
	pact->isvisible = false;
	
	for(pi=0; pi<numpages; pi++)
	{
		// pagedat[0] is the bgnd id
		pagedat = pagelist[pi];
		if(*pagedat>=0)
		{
			pact->page[pi].bgnd = new CBgnd(*pagedat,&bgndbmp,bgndofs);
			if(pact->page[pi].bgnd)
			{
				pact->page[pi].bgnd->SetMouseClickCb(stBgClick,this);
			}
			else
			{
				mError = true;
			}
			pact->page[pi].bitmap = bgndbmp;
			pact->page[pi].offset = bgndofs;
		}
		else
		{
			pact->page[pi].bgnd = 0;
			pact->page[pi].bitmap = 0;
			pact->page[pi].offset = CPoint(0,0);
		}
		pagedat++;
		
		// count sub-pages
		for(j=0; pagedat[j]>=0 && j<100; j++);
		pact->page[pi].numsubs = j;
		pact->page[pi].subs = j ? new struct _branch[j] : 0;
		
		// now create sub-pages if any
		for(j=0; j<pact->page[pi].numsubs; j++,pagedat++)
		{  
			BuildTree(pact->page[pi].subs+j, *pagedat);
		}
		pact->page[pi].controls = ++pagedat;
		
		for(ki=0; ki<1000; ki++)
		{
			cid = *pagedat;   // get CID_xxx
			if(cid<0) break;  // on val<0 exit loop
			// else we have a CID_xxx
			pagedat++;
			for(j=0; j<100 && *pagedat!=-1; j++)
			{
				cvl = *pagedat;
				switch(cid)
				{
					case IS_CID_SWITCH:
						if(cvl>=0)
						{
							if(!mSwitch[cvl]) mSwitch[cvl] = new CSwitch(cvl,bgndbmp);
							if(!mSwitch[cvl]) mError = true;
						}
						else
						{
							cvl = pagedat[-1];
						}
						ConfigSwitch(cvl, pagedat);
						break;
						
					case IS_CID_DISPLAY:
						if(!mDisplay[cvl]) mDisplay[cvl] = new CDisplay(cvl);
						if(!mDisplay[cvl]) mError = true;
						ConfigDisplay(cvl);
						break;
						
					case IS_CID_SCROLL:
						if(cvl>=0)
						{
							if(!mScroller[cvl]) mScroller[cvl] = new CScroller(cvl);
							if(!mScroller[cvl]) mError = true;
						}
						else
						{
							cvl = pagedat[-1];
						}
						ConfigScroller(cvl, pagedat);
						break;
						
					case IS_CID_STICK:
						if(!mStick[cvl]) mStick[cvl] = new CStick(cvl,bgndbmp);
						if(!mStick[cvl]) mError = true;
						ConfigStick(cvl);
						break;
						
					case IS_CID_DIAL:
						if(!mDial[cvl]) mDial[cvl] = new CDial(cvl);
						if(!mDial[cvl]) mError = true;
						ConfigDial(cvl);
						break;
						
					case IS_CID_SHAPER:
						if(cvl>=0)
						{
							if(!mShaper[cvl]) mShaper[cvl] = new CShaper(cvl);
							if(!mShaper[cvl]) mError = true;
						}
						else
						{
							cvl = pagedat[-1];
						}
						ConfigShaper(cvl, pagedat);
						break;
						
					case IS_CID_DROPDOWN:
						if(!mDropdown[cvl]) 
						{
							mDropdown[cvl] = new CDropdown(cvl,bgndbmp);
							if(!mDropdown[cvl])
							{
								mError = true;
							}
							else
							{
								mDropdown[cvl]->setFontColor (kTransparentCColor);
								mDropdown[cvl]->setTransparency(true);
								mDropdown[cvl]->setTextTransparency(true);
							}
						}
						ConfigDropdown(cvl);
						break;
						
					case IS_CID_AREA:
						if(!mArea[cvl]) mArea[cvl] = new CArea(cvl);
						if(!mArea[cvl]) mError = true;
						ConfigArea(cvl);
						break;
				}
				pagedat++;
			}
			pagedat++;
		}
	}
	
	// set up the pagenum reference
	pact->pparidx = index;
	CParam *par = mPgparm[index];
	CParam::td_notify *ntf = &mPgntf[index];
	
	par->mMax=ntf->max = (float)(numpages-1);
	ntf->PreCbFn = stPagePreCb;
	ntf->PstCbFn = stPagePstCb;
	ntf->inf[0] = this;
	ntf->inf[1] = pact;
	par->AddNotify(ntf);
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::UnbuildTree(td_branch *pact, int index)
{
	int numpages,ki,pi,j,cid,cvl;
	const long **pagelist = cBranch[index];
	const long *pagedat;
	//CBitmap *bgndbmp = 0;
	CPoint  bgndofs;
	
	// remove the page-switch notifyer
	CParam *par = mPgparm[index];
	CParam::td_notify *ntf = &mPgntf[index];
	par->RmvNotify(ntf);
	
	// count number of pages and destroy
	for(numpages=0; pagelist[numpages] && numpages<100; numpages++);
	
	for(pi=0; pi<numpages; pi++)
	{
		// pagedat[0] is the bgnd id
		pagedat = pagelist[pi];
		if(*pagedat>=0)
		{
			if(pact->page[pi].bgnd)
			{
				// crashes on mac? 
				delete pact->page[pi].bgnd;
			}
		}
		pagedat++;
		
		// now delete sub-pages if any
		for(j=0; j<pact->page[pi].numsubs; j++,pagedat++)
		{  
			UnbuildTree(pact->page[pi].subs+j, *pagedat);
		}
		
		if(pact->page[pi].numsubs)
		{
			delete pact->page[pi].subs;
		}
		
		for(ki=0; ki<1000; ki++)
		{
			cid = *pagedat;   // get CID_xxx
			if(cid<0) break;  // on val<0 exit loop
			// else we have a CID_xxx
			pagedat++;
			for(j=0; j<100 && *pagedat!=-1; j++)
			{
				cvl = *pagedat;
				switch(cid)
				{
					case IS_CID_SWITCH:
						if(mSwitch[cvl]) delete mSwitch[cvl];
						if(!mSwitch[cvl]) mError = true;
						break;
						
					case IS_CID_DISPLAY:
						if(mDisplay[cvl]) delete mDisplay[cvl];
						break;
						
					case IS_CID_SCROLL:
						if(mScroller[cvl]) delete mScroller[cvl];
						break;
						
					case IS_CID_STICK:
						if(mStick[cvl]) delete mStick[cvl];
						break;
						
					case IS_CID_DIAL:
						if(mDial[cvl]) delete mDial[cvl];
						break;
						
					case IS_CID_SHAPER:
						if(mShaper[cvl]) delete mShaper[cvl];
						break;
						
					case IS_CID_DROPDOWN:
						if(mDropdown[cvl]) delete mDropdown[cvl];
						break;
						
					case IS_CID_AREA:
						if(mArea[cvl]) delete mArea[cvl];
						break;
				}
				pagedat++;
			}
			pagedat++;
		}
	}
	
	// delete page(s)
	delete pact->page;
}


///////////////////////////////////////////////////////////////////////////////
//

void SynthEditor::SetControlsFrame(td_branch *tree, int pagenum, CFrame *frmp)
{
	// activate all controls
	const long *pgdat = tree->page[pagenum].controls;
	CPoint ofs = tree->page[pagenum].offset;
	long cid;
	int i,j;
	
	for(i=0; i<1000; i++)
	{
		cid = *pgdat;     // get CID_xxx
		if(cid<0) break;  // on val<0 exit loop
		pgdat++;
		for(j=0; j<100 && *pgdat!=-1; j++)
		{
			if(*pgdat>=0)
			{
				switch(cid)
				{
					case IS_CID_SWITCH:   mSwitch[*pgdat]->SetFrame(frmp,ofs);   break;
					case IS_CID_DISPLAY:
						switch(*pgdat)
					{
						case kDisplayR1ModelNumber:
							mDisplay[*pgdat]->SetFrame(frmp,ofs,&mInputR1ModelNumber);
							break;
						case kDisplayR2ModelNumber:
							mDisplay[*pgdat]->SetFrame(frmp,ofs,&mInputR2ModelNumber);
							break;
						case kDisplaySoundName:
							mDisplay[*pgdat]->SetFrame(frmp,ofs,&mInputSoundName);
							break;
						case kDisplaySoundNumber:
							mDisplay[*pgdat]->SetFrame(frmp,ofs,&mInputSoundNumber);
							break;
						default:
							mDisplay[*pgdat]->SetFrame(frmp,ofs);
							break;
					}
						break;
					case IS_CID_SCROLL:   mScroller[*pgdat]->SetFrame(frmp,ofs); break;
					case IS_CID_STICK:    mStick[*pgdat]->SetFrame(frmp,ofs);    break;
					case IS_CID_DIAL:     mDial[*pgdat]->SetFrame(frmp,ofs);     break;
					case IS_CID_SHAPER:   mShaper[*pgdat]->SetFrame(frmp,ofs);   break;
					case IS_CID_DROPDOWN: mDropdown[*pgdat]->SetFrame(frmp,ofs); break;
					case IS_CID_AREA:     mArea[*pgdat]->SetFrame(frmp,ofs);     break;
				}
			}
			pgdat++;
		}
		pgdat++;
	}
}


///////////////////////////////////////////////////////////////////////////////
// open editor page

void SynthEditor::OpenPage(td_branch *tree)
{
	int pagenum = (int)mPgparm[tree->pparidx]->GetVal();
	int i;
	CRect crb;
	
	// setup according background
	CBitmap *srcbmp = tree->page[pagenum].bitmap;
	if(srcbmp)
	{
		CRect cre = CRect(0,0,EDIT_WIDTH,EDIT_HEIGHT);
		CPoint cop = tree->page[pagenum].offset;
		crb = CRect(0,0,srcbmp->getWidth(),srcbmp->getHeight());
		CDrawContext      *srccon = new CDrawContext(frame,0);
		COffscreenContext *dstcon = new COffscreenContext(srccon,mBgnd,true);
		srcbmp->draw(dstcon,cre,cop);
		crb.offset(-cop.x,-cop.y);
		delete dstcon;
		delete srccon;
	}
	
	// add background to frame
	tree->isvisible = true;
	if(tree->page[pagenum].bgnd)
	{
		tree->page[pagenum].bgnd->SetFrame(frame);
	}
	
	// activate all controls
	SetControlsFrame(tree, pagenum, frame);
	
	// after the controls activate sub-pages
	for(i=0; i<tree->page[pagenum].numsubs; i++)
	{
		OpenPage(tree->page[pagenum].subs+i);
	}
	
	// paint according background
	srcbmp = tree->page[pagenum].bitmap;
	if(srcbmp)
	{
		CPoint cop = tree->page[pagenum].offset;
		crb = CRect(0,0,srcbmp->getWidth(),srcbmp->getHeight());
		crb.offset(-cop.x,-cop.y);
		gCBgndBlockDirty = true;
		frame->invalidate(crb);
		gCBgndBlockDirty = false;
		if(tree->page[pagenum].bgnd)
		{
			tree->page[pagenum].bgnd->SetDirty(true);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// close editor page

void SynthEditor::ClosePage(td_branch *tree)
{
	int pagenum = (int)mPgparm[tree->pparidx]->GetVal();
	int i;
	CRect crb;
	
	// close sub-pages
	tree->isvisible = false;
	for(i=tree->page[pagenum].numsubs-1; i>=0; i--)
	{
		ClosePage(tree->page[pagenum].subs+i);
	}
	
	// deactivate all controls
	SetControlsFrame(tree, pagenum, 0);
	
	// deactivate background
	CPoint ofs = tree->page[pagenum].offset;
	
	// remove background
	if(tree->page[pagenum].bgnd)
	{
		tree->page[pagenum].bgnd->SetFrame(0);
	}
}


///////////////////////////////////////////////////////////////////////////////
// 

void SynthEditor::valueChanged (CDrawContext* context, CControl* control)
{
}


///////////////////////////////////////////////////////////////////////////////
// TODO: move this away from here
///////////////////////////////////////////////////////////////////////////////
// 

CInput::CInput() : CView(size)
{
	mSoundNameDisplay = 0;
}


///////////////////////////////////////////////////////////////////////////////
// 

CInput::~CInput()
{
}


///////////////////////////////////////////////////////////////////////////////
// 

long CInput::notify(CView *sender, const char *message)
{
	switch((int)message)
	{
		case VNTF_MOUSE:  // next ::mouse() is an alien
			break;
			
		default:
			if(mParam)
			{
				CParam *par = mParam;
				if(mSoundNameDisplay)
				{
					char txt[17];
					float val;
					bool ended = false;
					int i;
					
					txt[16] = 0;
					
					for(i=0; i<16; i++)
					{
						if(ended)
						{
							val = 32.;
							txt[i] = 32;
						}
						else
						{
							val = (float)message[i];
							txt[i] = message[i];
							if(!val)
							{
								val = 32.;
								txt[i] = 32;
								ended = true;
							}
						}
						
						par[i].SetVal(val,NFLG_ALL);
					}
					mMP->SetSoundName((int)mAS->GetVal());
					mSoundNameDisplay->SetText(txt);
				}
				else
				{
					int in;
					
					sscanf(message,"%i",&in);
					mParam->SetVal((float)in,NFLG_ALL);
				}
			}
	}
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: SynthEditor.cpp,v $
// Revision 1.19  2004/12/02 15:26:11  joffe
// bugfix: editor crash
//
// Revision 1.18  2004/11/23 10:16:13  joffe
// remote void prg-change draw
//
// Revision 1.17  2004/11/23 09:09:16  joffe
// version info changed
//
// Revision 1.16  2004/11/23 08:13:12  joffe
// added neuron-vs style slicer switch/type with kb-compatibility
//
// Revision 1.15  2004/11/17 16:22:19  joffe
// statics moved out of function-bodies
//
// Revision 1.14  2004/11/11 04:09:43  joffe
// shaper-resy select as sndparam, name-update for dropdown
//
// Revision 1.13  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.12  2004/11/03 00:59:35  joffe
// knobselect added
//
// Revision 1.11  2004/10/19 06:24:18  joffe
// save-as mac adaptions
//
// Revision 1.10  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.9  2004/10/18 06:41:34  joffe
// - doubleclick-edit added
// - save added (w/o ok/cancel messagebox)
//
// Revision 1.8  2004/10/06 01:07:36  joffe
// unbuild page tree / destructor revised
//
// Revision 1.7  2004/10/05 18:21:41  joffe
// destructor improvements
//
// Revision 1.6  2004/10/05 16:53:09  joffe
// dropdown-menu implementation
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
