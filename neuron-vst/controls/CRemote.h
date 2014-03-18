///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: CRemote.h,v $
// $Revision: 1.2 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
// This is a control that supports switches/buttons for VstGui
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CREMOTE_H
#define CREMOTE_H

#include "CParam.h"


class CRemote
{
public:

  CRemote();
  ~CRemote();
  bool IsBad();

  void SetParamStick( int index, CParam *inVal[2] );
  void SetParamDials( int index, CParam *inVal[4] );
  void SetRemoteFocus(void);
  void SetAuthCb( void (*authcb[2])(void *), void *parent );

private:

  void *mHandle;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: CRemote.h,v $
// Revision 1.2  2004/08/26 00:48:08  joffe
// remote-auth added and setparm interface changed
//
// Revision 1.1  2004/08/14 06:09:42  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
