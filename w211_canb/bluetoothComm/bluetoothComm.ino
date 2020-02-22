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
    int r = random(4);
    switch(r)
    {
      case 0:
        bluetooth.nextTrack();
        break;
      case 1:
        bluetooth.prevTrack();
        break;
      case 2:
        bluetooth.pausePlay();
        break;
      case 3:
        bluetooth.stop();
        break;
      default: break;
    }
    //bluetooth.test();
  }
}
