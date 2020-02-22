# w211-canB
my first try at carhacking.

The goal is to tap into a Mercedes-Benz W211 E class's CAN B bus to use the steering wheel buttons to control audio playback (fwd, back, pause) via a CH-06 bluetooth module connected to a cell phone.

Another goal is to operate the motorised door to the CD changer compartment in the center console, which stops working once a the original head unit is removed.

Hardware used:

NodeMCU v3 (ESP8266, WiFi) ~~Chinese Arduino Nano knock-off (CH340G)~~

MCP2515 ISP-CAN interface

HC-06 serial-Bluetooth interface flashed with firmware from an RN-42 Bluetooth HID module
