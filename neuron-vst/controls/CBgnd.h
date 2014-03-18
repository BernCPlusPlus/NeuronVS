///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CBgnd.h,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that draws backgrounds
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

// bitmap page offsets

#define RS1LVL_X    21
#define RS1LVL_Y    446

#define RS2LVL_X    460
#define RS2LVL_Y    446

#define FREQFX_X    145 -119
#define FREQFX_Y    363

#define TIMEFX_X    655 -119
#define TIMEFX_Y    363


//                                |       Position        |dig|      | align |
//   ID                           |Top  Left  Height Width|its| font |  X  Y |

CM(kBgndResys,        IDB_RESYS,             0,        0 )

CM(kBgndRes1Lvl1,     IDB_RESYLVL1,   RS1LVL_Y, RS1LVL_X )
CM(kBgndRes1Lvl2,     IDB_RESYLVL2,   RS1LVL_Y, RS1LVL_X )
CM(kBgndRes1Lvl3,     IDB_RESYLVL3,   RS1LVL_Y, RS1LVL_X )

CM(kBgndRes2Lvl1,     IDB_RESYLVL1,   RS2LVL_Y, RS2LVL_X )
CM(kBgndRes2Lvl2,     IDB_RESYLVL2,   RS2LVL_Y, RS2LVL_X )
CM(kBgndRes2Lvl3,     IDB_RESYLVL3,   RS2LVL_Y, RS2LVL_X )


CM(kBgndSilver,       IDB_SILVER,            0,        0 )

CM(kBgndEqShelf,      IDB_EQSHELF,    FREQFX_Y, FREQFX_X )
CM(kBgndEqBand,       IDB_EQBAND,     FREQFX_Y, FREQFX_X )
CM(kBgndCompr,        IDB_COMPR,      FREQFX_Y, FREQFX_X )
CM(kBgndDistort,      IDB_DISTORT,    FREQFX_Y, FREQFX_X )
CM(kBgndRingMod1,     IDB_RINGMOD1,   FREQFX_Y, FREQFX_X )
CM(kBgndRingMod2,     IDB_RINGMOD2,   FREQFX_Y, FREQFX_X )
CM(kBgndDecimat,      IDB_DECIMAT,    FREQFX_Y, FREQFX_X )
CM(kBgndSpWarp,       IDB_SPWARP,     FREQFX_Y, FREQFX_X )

CM(kBgndStereoSpr,    IDB_STEREOSPR,  TIMEFX_Y, TIMEFX_X )
CM(kBgndLrDelay,      IDB_LRDELAY,    TIMEFX_Y, TIMEFX_X )
CM(kBgndFlanger1,     IDB_FLANGER1,   TIMEFX_Y, TIMEFX_X )
CM(kBgndFlanger2,     IDB_FLANGER2,   TIMEFX_Y, TIMEFX_X )
CM(kBgndPhaser1,      IDB_PHASER1,    TIMEFX_Y, TIMEFX_X )
CM(kBgndPhaser2,      IDB_PHASER2,    TIMEFX_Y, TIMEFX_X )
CM(kBgndChorus1,      IDB_CHORUS1,    TIMEFX_Y, TIMEFX_X )
CM(kBgndChorus2,      IDB_CHORUS2,    TIMEFX_Y, TIMEFX_X )


CM(kBgndRemote,       IDB_REMOTE,            0,        0 )


CM(kBgndAbout,        IDB_ABOUT,             0,        0 )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CBGND_H
#define CBGND_H

#include "vstgui.h"


extern bool gCBgndBlockDirty;

class CBgnd
{
public:

  CBgnd(int inEnumedId, CBitmap **oBgnd, CPoint &oOfs );
  ~CBgnd();

  void SetFrame( CFrame *iFrame );
  void SetDirty( bool iDirty = true );
  void SetMouseClickCb(void (*callback)(void *), void *parent);

private:

  void *mHandle;

};

// enum all elements

enum
{
#define CM(p1,p2,p3,p4) p1,
#include __FILE__

  kNumBgnds
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CBgnd.h,v $
// Revision 1.3  2004/11/06 05:53:15  joffe
// about-page added
//
// Revision 1.2  2004/08/14 06:06:21  joffe
// backround-bitmap mouseclick-callback added
//
// Revision 1.1  2004/07/23 18:17:52  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
