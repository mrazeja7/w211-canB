// MCP2515 library verbose mode
#define DEBUG_MODE 1

#include "mcp_can.h"
#include <SPI.h>

byte data[] = {0xAA, 0x55, 0x01, 0x10, 0xFF, 0x12, 0x34, 0x56};  // CAN test message

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
  Serial.println("10 second grace period starting; start programming firmware now!");
  delay(10000);
  Serial.println("Grace period over.");
  
  int canStatus = CAN_FAIL;

  // my own values
  // if ( (canStatus = CAN0.begin(MCP_ANY, CAN_83K33BPS, MCP_16MHZ)) != CAN_OK)

  // angelovAlex's suggested values from this MBWorld post: https://mbworld.org/forums/audio-electronics/580108-w211-can-b-hacking-2.html#post7038959
  if ( (canStatus = CAN0.begin(MCP_ANY, CAN_83K33BPS_AA, MCP_16MHZ)) != CAN_OK)
  {
    Serial.print("MCP2515 init error: ");
    Serial.println(canStatus, HEX);
  } 
   
  if ( (canStatus = CAN0.setMode(MCP_NORMAL)) != CAN_OK)
  {
    Serial.print("MCP2515 setMode error: ");
    Serial.println(canStatus, HEX);
  }
    
  Serial.println("MCP2515 init ok");

  pinMode(CAN0_INT, INPUT); // configure pin for interrupt input
}

unsigned long nonUseful = 0;
int lastPressed = 0;

// return value indicates whether a command should be sent over bluetooth; if so, it specifies which one
int parseButtons(unsigned char *rxBuf, unsigned char len)
{
  switch (rxBuf[1])
  {
    // arrow buttons
    case 0x01:
      Serial.print(" - up arrow pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;
    case 0x02:
      Serial.print(" - down arrow pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;
    case 0x03:
      Serial.print(" - up+down arrows pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;

    // volume buttons
    case 0x10:
      Serial.print(" - \"+\" button pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;
    case 0x20:
      Serial.print(" - \"-\" button pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;
    case 0x30:
      Serial.print(" - \"+\"+\"-\" buttons pressed");
      lastPressed = rxBuf[0] << 1 | rxBuf[1];
      break;
      
    case 0x00: // buttons released
      Serial.print(" - buttons released - the last pressed button was ");
      Serial.print(lastPressed, HEX);

      // if the lastPressed variable equals zero here, a debouncing issue occurred -> don't send a command
      if (lastPressed)
      {
        int tmp = lastPressed;
        lastPressed = 0;
        return tmp;
      }
  }
  return 0;
}

void loop()
{  
  if(!digitalRead(CAN0_INT))
  {
    memset(rxBuf, 0, 8);
    int msgTime = millis();
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    if (rxId != 0x2C && rxId != 0x1CA) // filter out everything except lower center panel and steering wheel buttons
    {
      nonUseful++;
      return;
    }
    
    if((rxId & 0x80000000) == 0x80000000) // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "%d:\tEID: 0x%.8lX\tlen: %1d\tData:", msgTime, (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "%d:\tSID: 0x%.3lX\tlen: %1d\tData:", msgTime, rxId, len);
  
    Serial.print(msgString);

    /* remote request frame - will never be used in this project    
    if((rxId & 0x40000000) == 0x40000000) 
    {
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } 
    */
    
    for(byte i = 0; i<len; i++)
    {
      sprintf(msgString, " 0x%.2X", rxBuf[i]);
      Serial.print(msgString);
    }

    // parse steering wheel buttons
    if (rxBuf[0] == 0x03)
    {
        int msg = parseButtons(rxBuf, len);
        if (msg)
        {
          // handle bluetooth communication here
        }
    }
        
    Serial.println();
  }

  if (millis() % 10000 == 0)
  {
    Serial.print(nonUseful);
    Serial.println(" non-useful messages in the past 10 seconds");
    nonUseful = 0;
    delayMicroseconds(980);
  }

/*
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
*/
}
