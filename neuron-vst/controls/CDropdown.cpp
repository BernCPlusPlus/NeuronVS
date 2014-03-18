///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDropdown.cpp,v $
// $Revision: 1.6 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#include "CDropdown.h"

#include <stdio.h>

// create own table of initialization data

typedef struct
{
  int switchid;
  int display;

} data;

const data stData[] =
{
#define CM(p1,p2,p3) {p2,p3},
#include "CDropdown.h"
#undef CM
};




CDropdown::CDropdown (int index, CBitmap *bgnd, bool sub) : COptionMenu(size, 0, index)
{
  mFrame = 0;
  mSwitch = 0;
  mDisplay = 0;
  mParam = 0;
  mOffset = 0.;

  if(!sub)
  {
    if(stData[index].switchid >= 0)
    {
      mSwitch = new CSwitch(stData[index].switchid, bgnd);
      mSwitch->GetPosition(&size);
    }

    if(stData[index].display >= 0)
    {
      mDisplay = new CDisplay(stData[index].display);
    }

    for(int i=0; i<16; i++)
    {
      mSubs[i] = new CDropdown(index,bgnd,true);
      mSubs[i]->mDisplay = mDisplay; // this all menuoption-stuff is total crap...
    }
  }
}


CDropdown::~CDropdown()
{
  if(mFrame) mFrame->removeView(this);

  for(int i=0; i<16; i++)
  {
    delete mSubs[i];
  }

  if(mSwitch) delete mSwitch;
  if(mDisplay) delete mDisplay;
}



void CDropdown::SetFrame(CFrame *frame, CPoint ofs)
{
  if(mSwitch) mSwitch->SetFrame(frame, ofs);
  if(mDisplay) mDisplay->SetFrame(frame, ofs);
  if(frame)
  {
    frame->addView(this);
  }
  else if (mFrame)
  {
    mFrame->removeView(this);
  }
  mFrame = frame;
}




void CDropdown::SetParam( CParam *inParam )
{
  // set new parameter
  mParam = inParam;
  for(int i=0; i<16; i++)
  {
    mSubs[i]->mParam = inParam;
  }
}


void CDropdown::SetOffset( float offset )
{
  // set new parameter
  mOffset = offset;
}


bool CDropdown::addEntry (COptionMenu *subMenu, char *txt)
{
	if (nbEntries >= MAX_ENTRY || !subMenu || !txt)
		return false;

	if (nbEntries >= nbAllocated)
		if (!allocateMenu (32))
			return false;

	entry[nbEntries] = (char*)malloc (256);
	switch (prefixNumbers)
	{
		case 2:
			sprintf (entry[nbEntries], "-M%1d %s", (int)(nbEntries), txt);
			break;

		case 3:
			sprintf (entry[nbEntries], "-M%02d %s", (int)(nbEntries), txt);
			break;

		case 4:
			sprintf (entry[nbEntries], "-M%03d %s", (int)(nbEntries), txt);
			break;

		default:
			sprintf (entry[nbEntries], "-M%s", txt);
	}


	if (nbSubMenus >= nbSubMenuAllocated)
		if (!allocateSubMenu (10))
			return false;

	submenuEntry[nbSubMenus++] = subMenu;
	subMenu->remember ();

	nbEntries++;

	return true;
}

bool CDropdown::addEntry (char *txt, long index)
{
	if (nbEntries >= MAX_ENTRY)
		return false;
	
	if (nbEntries >= nbAllocated)
		if (!allocateMenu (32))
			return false;
		
	entry[nbEntries] = (char*)malloc (256);

	long pos = nbEntries;

	// switch the entries for the insert
	if (index >= 0)
	{
		for (long i = nbEntries; i > index; i--)
			strcpy (entry[i], entry[i - 1]);
		if (index >= nbEntries)
			pos = nbEntries;
		else
			pos = index;	
		if (currentIndex >= index)
			currentIndex++;	
	}

	*entry[pos] = 0;
	if (txt)
	{
		switch (prefixNumbers)
		{
			case 2:
				sprintf (entry[pos], "%1d %s", (int)(index), txt);
				break;

			case 3:
				sprintf (entry[pos], "%02d %s", (int)(index), txt);
				break;

			case 4:
				sprintf (entry[pos], "%03d %s", (int)(index), txt);
				break;

			default:
				strncpy (entry[pos], txt, 256);
		}
	}
	
	nbEntries++;
	
	if (currentIndex < 0)
		currentIndex = 0;
	
	return true;
}


void CDropdown::draw (CDrawContext *pContext)
{

  char txt[256] = "";

  if(mDisplay)
  {
    if (mParam && getEntry((long)mParam->GetVal(),txt) == true)
    {
#if 0
      if(mParam)
        sprintf(txt,"%.2f %.2f",(float)getCurrent(), mParam->GetVal());
      else
        sprintf(txt,"%.2f",(float)getCurrent());
#endif
      mDisplay->SetText(txt);
    }
	  else
    {
      mDisplay->SetText("crap");
    }
  }

}

void CDropdown::setValue (float val)
{
	if ((long)val < 0 || (long)val >= nbEntries)
		return;
	
	currentIndex = (long)val;
	if (style & (kMultipleCheckStyle & ~kCheckStyle))
		check[currentIndex] = !check[currentIndex];
//	CParamDisplay::setValue (val);
	
  if(mParam)
  {
    if(mParam->SetVal((float)getCurrent()+mOffset, NFLG_OTHERS|NFLG_FORCE))
    {
      setDirty ();
    }
  }

	// to force the redraw
//	setDirty ();
}


///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDropdown.cpp,v $
// Revision 1.6  2004/11/16 18:13:15  joffe
// bugfix: mframe initialized
//
// Revision 1.5  2004/10/19 05:53:25  joffe
// save-as added
//
// Revision 1.4  2004/10/05 18:21:40  joffe
// destructor improvements
//
// Revision 1.3  2004/10/05 16:53:07  joffe
// dropdown-menu implementation
//
// Revision 1.2  2004/09/16 05:14:20  joffe
// - new remote page and controls added
// - optionmenues enabled
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
