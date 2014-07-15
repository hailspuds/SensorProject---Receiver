// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
int receive_pin = 2;


void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(1200);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  char sz[] = "";
  char *p = sz;
  char *str;
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen))
  {
    int i;
    for (int i=0;i<buflen;i++)
    {
      if (buf[i] == '#')
      {
        //Serial.print(" DINGDINGDING "); 
      }

      Serial.write(buf[i]);
      Serial.print("");
    }
    
    ///TESTING BLOCK
    Serial.println("");
    Serial.println("***");
    while ((str = strtok_r(p, "#", &p)) != NULL) // delimiter is the semicolon
    {
      Serial.println(str);
    }
    Serial.println("****");
    /// END TEST BLOCk
 
    Serial.println("");
  }
}

