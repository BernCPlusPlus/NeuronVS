///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: RemoteDriver.h,v $
// $Revision: 1.3 $
//
// (C) J.Fornoff for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef REMOTEDRIVER_H
#define REMOTEDRIVER_H


class RemoteDriver
{
public:
  RemoteDriver();
  ~RemoteDriver();

  bool Open();    // open remotedriver, returns success
  void Close();   // close remotedriver

  void SetLed(bool iLed1, bool iLed2, bool iLed3);
  void SetFirst(bool first=true);
 
  void GrabFocus( void );
  void SetButtonCbfoc( void (*button)(bool, void *), void *parent);
  void SetDialCbfoc( void (*dial)(signed char [4], void *), void *parent);
  void SetStickCbfoc( void (*stick)(unsigned char [2], void *), void *parent);

  void SetAuthCb( void (*authcb[2])(void *), void *parent );

private:
  void *Handle;
};


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: RemoteDriver.h,v $
// Revision 1.3  2004/09/28 02:29:40  joffe
// first blister-show implementation
//
// Revision 1.2  2004/08/26 01:05:20  joffe
// dial, stick and auth added
//
// Revision 1.1  2004/08/14 06:02:12  joffe
// drivers de-globalized, remote-driver added
//
///////////////////////////////////////////////////////////////////////////////
