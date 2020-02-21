#include "BluetoothComm.h"

// just wrappers for the SoftwareSerial class
int BluetoothComm::init(int8_t rxPin, int8_t txPin)
{
  module = new SoftwareSerial(rxPin, txPin, false);
  return (module ? 0 : 1);
}
void BluetoothComm::begin(uint32_t baud)
{
  module->begin(baud);
}
size_t BluetoothComm::write(uint8_t byte)
{
  return module->write(byte);
}
size_t BluetoothComm::write(const uint8_t* buffer, size_t size)
{
  return module->write(buffer, size);
}
int BluetoothComm::available()
{
  return module->available();
}
int BluetoothComm::read()
{
  return module->read();
}

// saves a reference to the Serial interface for debugging purposes
void BluetoothComm::setSerial(Stream *s)
{
  serial = s;
}

// presses the "previous track" media button for a short while, then releases
void BluetoothComm::prevTrack()
{  
  module->write(PREV_TRACK, sizeof(PREV_TRACK));
#ifdef DEBUG
  this->serial->println("\"prev\" command sent");
#endif
  delay(BLUETOOTH_KEY_DELAY);
  module->write(RELEASE_KEYS, sizeof(RELEASE_KEYS));
#ifdef DEBUG
  this->serial->println("keys released");
#endif
}
