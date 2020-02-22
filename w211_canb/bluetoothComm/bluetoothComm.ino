/*
 * for bluetooth testing purposes only
 */

#include "BluetoothComm.h"

BluetoothComm bluetooth;

void setup()
{
  bluetooth.init(BLUETOOTH_RX, BLUETOOTH_TX);
  Serial.begin(115200);
  bluetooth.begin(115200);
#ifdef DEBUG
  bluetooth.setSerial(&Serial);
#endif
}

void loop()
{
  while (bluetooth.available())
    Serial.write(bluetooth.read());

  while (Serial.available() > 0)
    bluetooth.write(Serial.read());

  if (millis() % 10000 == 0)
  {
    if (random(2))
      bluetooth.nextTrack();
    else
      bluetooth.prevTrack();
      
    //bluetooth.nextTrack();
    //bluetooth.prevTrack();
    //bluetooth.pausePlay();
    //bluetooth.stop();
    //bluetooth.test();
  }
}
