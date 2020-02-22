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

// generic function that sends a command. Debug information available if needed
int BluetoothComm::sendBtCommand(const byte *cmd, size_t len, bool release = true)
{
  size_t res = this->module->write(cmd, len);
  int ret = (len == res ? 0 : 1);
  
#ifdef DEBUG
  memset(debugMsg, 0, DEBUG_LEN);
  sprintf(debugMsg, "%u out of %u bytes written, status = %s", res, len, (ret ? "fail" : "ok"));
  this->serial->print(debugMsg);
#endif

  if (release)
  {
    delay(BLUETOOTH_KEY_DELAY);
    len = sizeof(RELEASE_KEYS);
    res = this->module->write(RELEASE_KEYS, len);
    
#ifdef DEBUG
    this->serial->print(", key release ");
    this->serial->println((len == res ? "ok" : "fail"));
#endif
    ret += (len == res ? 0 : 1);
  }
  
  return ret;
}

// releases any keys that are pressed
int BluetoothComm::releaseKeys()
{
#ifdef DEBUG
  this->serial->print("releasing keys... ");
#endif
  return this->sendBtCommand(RELEASE_KEYS, sizeof(RELEASE_KEYS), false);
}

// presses the "previous track" media button for a short while, then releases
int BluetoothComm::prevTrack()
{  
#ifdef DEBUG
  this->serial->print("previous track... ");
#endif
  return this->sendBtCommand(PREV_TRACK, sizeof(PREV_TRACK), true);
}

int BluetoothComm::nextTrack()
{  
#ifdef DEBUG
  this->serial->print("next track... ");
#endif
  return this->sendBtCommand(NEXT_TRACK, sizeof(NEXT_TRACK), true);
}

int BluetoothComm::pausePlay()
{  
#ifdef DEBUG
  this->serial->print("pause/play... ");
#endif
  return this->sendBtCommand(PAUSE_PLAY, sizeof(PAUSE_PLAY), true);
}

int BluetoothComm::stop()
{  
#ifdef DEBUG
  this->serial->print("stop... ");
#endif
  return this->sendBtCommand(STOP, sizeof(STOP), true);
}

void BluetoothComm::test()
{  
  size_t res = module->write(TEST, sizeof(TEST));
#ifdef DEBUG
  this->serial->print("\"hello\" sent, res = ");
  this->serial->println(res);
#endif
}
