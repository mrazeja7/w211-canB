/*
 * Essentially just a very simple wrapper for the SoftwareSerial library that includes pre-made commands
 * and debug outputs.
 */
 
#include <SoftwareSerial.h>
#include "defines.h"

class BluetoothComm
{
public:
  BluetoothComm() {}
  int init(int8_t rxPin, int8_t txPin);
  void begin(uint32_t baud);
  size_t write(uint8_t byte);
  size_t write(const uint8_t* buffer, size_t size);
  int available();
  int read();

  int releaseKeys();
  int pausePlay();
  int prevTrack();
  int nextTrack();
  int stop();
  void test();

  void setSerial(Stream *s);
  
private:
  int sendBtCommand(const byte *cmd, size_t len, bool release);
  SoftwareSerial *module;
  Stream *serial;
  
#ifdef DEBUG
  #define DEBUG_LEN 64
  char debugMsg[DEBUG_LEN];
#endif  
};
