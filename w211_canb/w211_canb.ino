#include "mcp_can.h"
#include <SPI.h>

// CAN TX Variables
unsigned long prevTX = 0;                                        // Variable to store last execution time
const unsigned int invlTX = 1000;                                // One second interval constant
byte data[] = {0xAA, 0x55, 0x01, 0x10, 0xFF, 0x12, 0x34, 0x56};  // Generic CAN data to send

// CAN RX Variables
long unsigned int rxId;
unsigned char len;
unsigned char rxBuf[8];

// Serial Output String Buffer
char msgString[128];

// CAN0 INT and CS
//#define CAN0_INT 2 // nano D2
//MCP_CAN CAN0(10); // nano D10
#define CAN0_INT 2 // NodeMCU D4 
MCP_CAN CAN0(15); // NodeMCU D8


void setup()
{
  Serial.begin(115200);

   //if (CAN0.begin(MCP_ANY, CAN_83K33BPS_AA, MCP_16MHZ) == CAN_OK) // angelovAlex's suggested values from this MBWorld post: https://mbworld.org/forums/audio-electronics/580108-w211-can-b-hacking-2.html#post7038959
  if (CAN0.begin(MCP_ANY, CAN_83K33BPS, MCP_16MHZ) == CAN_OK) // my own values
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  // Since we do not set NORMAL mode, we are in loopback mode by default.
  //CAN0.setMode(MCP_NORMAL);

  pinMode(CAN0_INT, INPUT);                           // Configuring pin for /INT input
  
  Serial.println("MCP2515 Library Loopback Example...");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                          // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)             // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "EID: 0x%.8lX\tlen: %1d\tData:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "SID: 0x%.3lX\tlen: %1d\tData:", rxId, len);
  
    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){            // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }
        
    Serial.println();
  }
  
  if(millis() - prevTX >= invlTX){                    // Send this at a one second interval. 
    prevTX = millis();
    data[7] = data[7]+1;
    byte sndStat = CAN0.sendMsgBuf(0x100, 8, data);
    
    if(sndStat == CAN_OK)
      Serial.println("Message Sent Successfully!");
    else
    {
      Serial.print("Error Sending Message...");
      Serial.println(sndStat);
    }

  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
