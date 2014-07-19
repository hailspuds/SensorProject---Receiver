#include <SPI.h>
#include <Ethernet.h>
#include <Phant.h>
#include <VirtualWire.h>

//Include header file where the public and private keys are set
#include "HeaderKey.h"

//Set up for Phant/Ethernet
const char public_key[] = PHANT_PUBLIC_KEY;
const char private_key[] = PHANT_PRIVATE_KEY;

char server[] = "data.sparkfun.com";
Phant phant("data.sparkfun.com", public_key, private_key);

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// the dns server ip
IPAddress dnServer(192, 168, 1, 254);
// the router's gateway address:
IPAddress gateway(192, 168, 1, 254);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(192, 168, 1, 23);

EthernetClient client;

//Set up for VirtualWire
int receive_pin = 2;
int numbers[6];


void setup() {
  Serial.begin(9600);
  delay(2000);
  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());

  Serial.println("Setting up receiver");
  //Set up radio
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(1200);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  Serial.println("Receiver ready!");

  //Get Seed Value for Random
  //randomSeed(analogRead(0));
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // check to see if anything has been received
  {
    for (int i = 0; i < 6; i++)
    {
      numbers[i] = word(buf[i*2+1], buf[i*2]);

      if (i == 0)
      {
        Serial.print("Sensor ID = ");
        phant.add("sensorid", numbers[i]);
      }

      if (i == 1)
      {
        Serial.print("Light = ");
        phant.add("light", numbers[i]);
      }

      if (i == 2)
      {
        Serial.print("Temp = ");
        phant.add("temp", numbers[i]);
      }

      if (i == 3)
      {
        Serial.print("Random 1 = ");
        phant.add("random1", numbers[i]);
      }

      if (i == 4)
      {
        Serial.print("Random 2 = ");
        phant.add("random1", numbers[i]);
      }

      if (i == 5)
      {
        Serial.print("Count = ");
        phant.add("count", numbers[i]);
      }    

      Serial.println(numbers[i], DEC);
    }
    Serial.println();    

    Serial.println("Starting HTTP...");
    httppost();
    Serial.println("Disconnecting HTTP...");
    client.stop();  
  }
}

void httppost()
{  
  if (client.connect(server, 80))
  {
    //Serial.println("----POSTED TEST URL:----");
    //Serial.println(phant.url());
    //Serial.println("------------------------");

    client.println(phant.post());

    Serial.println("----POSTED POST:----");
    Serial.println(phant.post());

    //client.println(phant.post());
  }
  else
  {
    Serial.println("Nothing happening...");
  }
}

