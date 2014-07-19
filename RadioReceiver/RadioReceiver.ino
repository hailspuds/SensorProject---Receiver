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
int numbers[6]; // Change 3 to number of integers you wish to send.

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("Setting up receiver");
  
  // Initialise the IO and ISR
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(1200);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  Serial.println("Receiver ready!");
  
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // check to see if anything has been received
  {
    for (int i = 0; i < 6; i++)
    {
      numbers[i] = word(buf[i*2+1], buf[i*2]);
      //Serial.print("numbers[");
      //Serial.print(i, DEC);
      //Serial.print("]=");
      //Serial.print(numbers[i], DEC);
      
      if (i == 0)
      {
        Serial.print("Sensor ID = ");
      }
      
      if (i == 1)
      {
        Serial.print("Light = ");
      }
      
      if (i == 2)
      {
        Serial.print("Temp = ");
      }
      
      if (i == 3)
      {
        Serial.print("Random 1 = ");
      }
      
      if (i == 4)
      {
        Serial.print("Random 2 = ");
      }
      
      if (i == 5)
      {
        Serial.print("Count = ");
      }    
      
      Serial.println(numbers[i], DEC);
    }
    Serial.println();
  }
  
  delay(50);
} 
