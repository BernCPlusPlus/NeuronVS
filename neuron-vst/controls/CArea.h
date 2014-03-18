///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CArea.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// first: macro defines

#ifdef CM   // ControlMacro defined

CM(kAreaAbout,  0,575, 225, 40 )

#undef CM
#endif


///////////////////////////////////////////////////////////////////////////////
// second:our class and standard defines

#ifndef CAREA_H
#define CAREA_H

#include "vstgui.h"


class CArea : public CView
{
public:

	CArea(int inEnumedId);
  ~CArea();

  void SetFrame( CFrame *inFrame, CPoint ofs );
  void SetMouseClickCb( void (*callback)(void *), void *parent );

private:
	virtual void mouse(CDrawContext *, CPoint &);

  CFrame  *mFrame;
  void    (*mMouseClick)(void *parent);
  void    *mMouseClickParent;
};

// enum the IDs

enum
{
#define CM(p1,p2,p3,p4,p5) p1,
#include __FILE__

  kNumAreas
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CArea.h,v $
// Revision 1.1  2004/11/06 05:53:15  joffe
// about-page added
//
///////////////////////////////////////////////////////////////////////////////
