// enables 'verbose mode' of the BT module
#define DEBUG 1

#define BLUETOOTH_RX D1
#define BLUETOOTH_TX D2

// the duration of the media keypresses (in ms) - after this time is elapsed, the module sends a HID report where no keys are pressed (thus simulating a key release)
#define BLUETOOTH_KEY_DELAY 75

// Raw HID report data for all the buttons this module uses
constexpr static byte PAUSE_PLAY[]   = {0xFD, 0x03, 0x03, 0x80, 0x00};
constexpr static byte PREV_TRACK[]   = {0xFD, 0x03, 0x03, 0x00, 0x02};
constexpr static byte NEXT_TRACK[]   = {0xFD, 0x03, 0x03, 0x00, 0x01};
constexpr static byte STOP[]         = {0xFD, 0x03, 0x03, 0x00, 0x04};
constexpr static byte RELEASE_KEYS[] = {0xFD, 0x03, 0x03, 0x00, 0x00};
constexpr static byte TEST[] = {'h', 'e', 'l', 'l', 'o'};
