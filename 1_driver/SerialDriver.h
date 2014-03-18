///////////////////////////////////////////////////////////////////////////////
//
// $RCSfile: SerialDriver.h,v $
// $Revision: 1.1 $
//
// (C) J.Fornoff, J.Pogadl for Hartmann Music
//
// View Change Log at end of file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SERIALDRIVER_H
#define SERIALDRIVER_H

extern class SerialDriver
{
  public:
    SerialDriver();
    ~SerialDriver();

    bool Open       // open serialdriver, returns success
    (               
      char *inDevname,          // name of the device to open
      long inBaudrate,          // baudrate to set
      char ** const ioErrmsg=0  // plain text error-message on fault
    );                          

    void Close();   // close the instance of the driver
                    
    void SetGetBuffer     // set callback-function that receives
    (                     //   data in a buffer
      void (*GetBuffer)   // callback-fn pointer
      (
        char *inBuf,      // receive-buffer
        short inNumBytes, // number of bytes in buffer
        void  *inPparent  // parent instance
      ),
      void *inParent      // set parent instance
    );                    

    void SendByte         // send byte to serialport
    (
      char inByte         // byte to send
    );

    void SendBuffer       // send buffer to serialport
    (
      char *inBuf,        // buffer to send
      short inNumBytes    // number of bytes to send
    );

  private:
    void *Handle;

} gSerialDriver;


#endif  // XXXX_H

///////////////////////////////////////////////////////////////////////////////
//
// $Log: SerialDriver.h,v $
// Revision 1.1  2004/07/23 18:17:49  joffe
// initial revision
//
///////////////////////////////////////////////////////////////////////////////
