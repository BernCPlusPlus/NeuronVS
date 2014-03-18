///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CStick.h,v $
// $Revision: 1.4 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that supports switches/buttons for VstGui
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

//               |Position| Assigned Displays (4x Val + Name)              |
//   ID          |Top Left|                                                |

CM(kStickR1,      279, 181, kDisplayR1CtxVal1,     kDisplayR1CtxName1,
                            kDisplayR1CtxVal2,     kDisplayR1CtxName2,
                            kDisplayR1CtxVal3,     kDisplayR1CtxName3,
                            kDisplayR1CtxVal4,     kDisplayR1CtxName4      )

CM(kStickR2,      279, 620, kDisplayR2CtxVal1,     kDisplayR2CtxName1,
                            kDisplayR2CtxVal2,     kDisplayR2CtxName2,
                            kDisplayR2CtxVal3,     kDisplayR2CtxName3,
                            kDisplayR2CtxVal4,     kDisplayR2CtxName4      )

CM(kStickSilver,  203, 401, kDisplaySilverCtxVal1, kDisplaySilverCtxName1,
                            kDisplaySilverCtxVal2, kDisplaySilverCtxName2,
                            kDisplaySilverCtxVal3, kDisplaySilverCtxName3,
                            kDisplaySilverCtxVal4, kDisplaySilverCtxName4  )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CSTICK_H
#define CSTICK_H

#include "vstgui.h"
#include "CParam.h"


class CStick
{
public:

  CStick(int inEnumedId, CBitmap *inBackground);
  ~CStick();

  void SetFrame( CFrame *inFrame, CPoint inOffset );

  void SetView( int inLevel, int inType );
  void SetParam( CParam *inVal1, CParam *inVal2 );
  void SetResetAllCb( void (*callback)(void *), void *parent );

private:

  void *mHandle;
};

// enum all elements

enum
{
#define CM(p1,p2,p3,v1,n1,v2,n2,v3,n3,v4,n4) p1,
#include __FILE__

  kNumSticks
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CStick.h,v $
// Revision 1.4  2004/11/11 03:08:32  joffe
// reset-all callback added
//
// Revision 1.3  2004/09/29 08:19:39  joffe
// scape/sphere bitmap added / page 2 type-button fixed
//
// Revision 1.2  2004/08/14 06:09:20  joffe
// reduced parameter usage
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
