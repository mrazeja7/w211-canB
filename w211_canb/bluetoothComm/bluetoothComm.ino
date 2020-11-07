/*
 * for bluetooth testing purposes only
 */
#define DEBUG 1
#define BT_TEST 1
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

#ifdef BT_TEST
  Serial.write("A random media key will be pressed every 10 seconds. You can also enter a string to send via keyboard keys: \n");
#endif
}

void loop()
{
#ifdef BT_TEST
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
#endif
    //bluetooth.test();
  }
}
