#include <SPI.h>
#include <Ethernet.h>
#include <Phant.h>
 
char server[] = "data.sparkfun.com";
Phant phant("data.sparkfun.com", "public_key", "private_key");
int randNumber;
int randNumber2;
int randNumber3;
int randNumber4;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// the dns server ip
IPAddress dnServer(192, 168, 1, 254);
// the router's gateway address:
IPAddress gateway(192, 168, 1, 254);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(192, 168, 1, 23);

EthernetClient client;

void setup() {
  Serial.begin(9600);
  delay(2000);
  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());
  randomSeed(analogRead(0));
}
 
void loop() {
  randNumber = random(300);
  randNumber2 = random(300);
  randNumber3 = random(300);
  randNumber4 = random(300);

  Serial.println("Starting...");
  httppost();
  Serial.println("disconnecting.");
  client.stop();
  delay(10000);
  
}

void httppost()
{
  //if (!(client.connect(server, 80)))
  if (client.connect(server, 80))
  {
    phant.add("light", "Random Numbers:");
    phant.add("random1", randNumber4);
    phant.add("random2", randNumber3);
    phant.add("room", randNumber2);
    phant.add("temp", randNumber);
    client.println(phant.post());
    
    Serial.println("----POSTED TEST URL:----");
    //Serial.println(phant.url());
        
    //Serial.println("----POSTED POST:----");
    //Serial.println(phant.post());
    
    //client.println(phant.post());
  }
  else
  {
    Serial.println("Nothing happening...");
  }
}
