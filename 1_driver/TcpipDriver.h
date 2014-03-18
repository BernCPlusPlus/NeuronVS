///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: TcpipDriver.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TCPIPDRIVER_H
#define TCPIPDRIVER_H


#define SOCK_UDP               0
#define SOCK_TCP               1

#define READSOCK_CONNECT       0
#define READSOCK_DISCONNECT    1
#define READSOCK_TCPDATA       2
#define READSOCK_UDPDATA       3


typedef unsigned short ushort;

typedef struct
{
  void    *handle;        // handle for internal use
  int     size;           // size of data buffer
  char    *data;          // pointer to rx/tx data

} conn_data;


extern class TcpipDriver
{
  public:

  TcpipDriver();
  ~TcpipDriver();

  bool Open       // open a tcp/ip socket, returns success
  (
    unsigned short inPort,    // portnumber of socket
    int            inType,    // SOCK_xxx value
    void (*callback)          // pointer to callback function
    (
      conn_data *inConnData,  // ptr to connection data struct deliverd by call
      int       inMode,       // READSOCK_xxx reason of callback
      void      *this_p       // pointer to calling class-instance
    ),
    void  *inParent,          // pointer to calling class-instance for callback()
    char  ** const ioErrmsg=0 // plain text error-message on fault
  );

  void Close      // close tcp/ip socket(s)
  (
    long  inPort,   // portnumber of socket, -1 for all
    long  inType    // SOCK_xxx value, -1 for all types
  );

  int Read        // read rcvd. message, call it out from 'callback'
  (               // returns number of bytes read, -1 on error
    char *outBuf, // buffer to read to
    int  inSize   // size of buffer
  );
  
  private:

  void *Handle;

} gTcpipDriver;


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: TcpipDriver.h,v $
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
