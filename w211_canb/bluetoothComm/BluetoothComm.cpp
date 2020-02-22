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
#ifdef DEBUG
  this->serial->println("Serial interface set");
#endif
}

// presses the "previous track" media button for a short while, then releases
void BluetoothComm::prevTrack()
{  
  size_t res = module->write(PREV_TRACK, sizeof(PREV_TRACK));
#ifdef DEBUG
  this->serial->println("\"prev\" command sent...");
#endif
  delay(BLUETOOTH_KEY_DELAY);
  module->write(RELEASE_KEYS, sizeof(RELEASE_KEYS));
#ifdef DEBUG
  this->serial->println("keys released...");
#endif
}

void BluetoothComm::nextTrack()
{  
  size_t res = module->write(NEXT_TRACK, sizeof(NEXT_TRACK));
#ifdef DEBUG
  this->serial->println("\"next\" command sent...");
#endif
  delay(BLUETOOTH_KEY_DELAY);
  module->write(RELEASE_KEYS, sizeof(RELEASE_KEYS));
#ifdef DEBUG
  this->serial->println("keys released...");
#endif
}

void BluetoothComm::pausePlay()
{  
  size_t res = module->write(PAUSE_PLAY, sizeof(PAUSE_PLAY));
#ifdef DEBUG
  this->serial->println("\"pause/play\" command sent...");
#endif
  delay(BLUETOOTH_KEY_DELAY);
  module->write(RELEASE_KEYS, sizeof(RELEASE_KEYS));
#ifdef DEBUG
  this->serial->println("keys released...");
#endif
}

void BluetoothComm::stop()
{  
  size_t res = module->write(STOP, sizeof(STOP));
#ifdef DEBUG
  this->serial->println("\"stop\" command sent...");
#endif
  delay(BLUETOOTH_KEY_DELAY);
  module->write(RELEASE_KEYS, sizeof(RELEASE_KEYS));
#ifdef DEBUG
  this->serial->println("keys released...");
#endif
}

void BluetoothComm::test()
{  
  size_t res = module->write(TEST, sizeof(TEST));
#ifdef DEBUG
  this->serial->print("command sent...");
  this->serial->println(res);
#endif
}
