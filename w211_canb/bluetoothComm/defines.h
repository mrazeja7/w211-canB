// enables 'verbose mode' of the BT module
#define DEBUG 1

#define BLUETOOTH_RX D2
#define BLUETOOTH_TX D1

// the duration of the media keypresses - after this time is elapsed, the module sends a HID report where no keys are pressed (thus simulating a key release)
#define BLUETOOTH_KEY_DELAY 100

// Raw HID report data for all the buttons this module uses
constexpr static byte PAUSE_PLAY[]   = {0xFD, 0x03, 0x03, 0x80, 0x00};
constexpr static byte PREV_TRACK[]   = {0xFD, 0x03, 0x03, 0x00, 0x02};
constexpr static byte NEXT_TRACK[]   = {0xFD, 0x03, 0x03, 0x00, 0x01};
constexpr static byte RELEASE_KEYS[] = {0xFD, 0x03, 0x03, 0x00, 0x00};