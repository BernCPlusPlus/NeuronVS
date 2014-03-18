///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CDropdown.h,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// Dropdown list control.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

//                                |                      |                |
//   ID                           |      Switch ID       |   Display ID   |

CM(kDropdownBlenderType,            kSwitchBlenderType,    kDisplayBlenderType)

CM(kDropdownFilterType,             kSwitchFilterType,     kDisplayFilterType)

CM(kDropdownR1ModelSelect,          kSwitchR1ModelSelect,  -1 )
CM(kDropdownR2ModelSelect,          kSwitchR2ModelSelect,  -1 )

CM(kDropdownMpSndLoad,              kSwitchMpSndLoad,      -1 )
CM(kDropdownMpSndSaveAs,            kSwitchMpSndSaveAs,    -1 )

CM(kDropdownKnob1Select,            kSwitchKnob1Select,    kDisplayKnob1Select)
CM(kDropdownKnob2Select,            kSwitchKnob2Select,    kDisplayKnob2Select)
CM(kDropdownKnob3Select,            kSwitchKnob3Select,    kDisplayKnob3Select)
CM(kDropdownKnob4Select,            kSwitchKnob4Select,    kDisplayKnob4Select)

CM(kDropdownDestAftertouch,         kSwitchDestAftertouch, kDisplayDestAftertouch)
CM(kDropdownDestModulation,         kSwitchDestModulation, kDisplayDestModulation)
CM(kDropdownDestBreath,             kSwitchDestBreath,     kDisplayDestBreath)
CM(kDropdownDestCC03,               kSwitchDestCC03,       kDisplayDestCC03)
CM(kDropdownDestFoot,               kSwitchDestFoot,       kDisplayDestFoot)
CM(kDropdownDestExpression,         kSwitchDestExpression, kDisplayDestExpression)

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CDROPDOWN_H
#define CDROPDOWN_H

#include "vstgui.h"
#include "CSwitch.h"
#include "CDisplay.h"


class CDropdown : public COptionMenu
{
public:

	CDropdown (int inEnumedId, CBitmap *inBackground, bool sub=false);
  ~CDropdown();

  void SetFrame(CFrame *frame, CPoint ofs);
  void SetParam( CParam *inParam );
  void SetOffset( float offset );

  virtual bool addEntry(COptionMenu *subMenu, char *txt);
  virtual bool addEntry(char *txt, long index);
  virtual	void draw(CDrawContext *pContext);
  virtual void setValue (float val);


  CDropdown *mSubs[16]; // todo: more stylish please

private:

  CFrame    *mFrame;
  CSwitch   *mSwitch;
  CDisplay  *mDisplay;
  CParam    *mParam;
  float     mOffset;

};

// enum the IDs

enum
{
#define CM(p1,p2,p3) p1,
#include __FILE__

  kNumDropdowns
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CDropdown.h,v $
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
