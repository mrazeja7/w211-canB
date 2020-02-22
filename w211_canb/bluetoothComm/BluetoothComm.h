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
  
  void pausePlay();
  void prevTrack();
  void nextTrack();
  void stop();
  void test();

  void setSerial(Stream *s);
  
private:
  SoftwareSerial *module;
  Stream *serial;
};
