Geeko,

I modified that code to send an array of integers.  You can modify the number of elements and assign whatever values to them.  Don't forget to change the loop bounds if you change the number of array elements.

I commented out vw_set_tx_pin(3) and vw_set_rx_pin(2) because I do not have a Mega.  

I use the default Digital pin 12 for transmit, and pin 11 for receive.

I lowered speed too just to make sure it works, you're welcome to experiment and set them higher.

PS: I learned a new command while helping you: word(hi,low) combines two bytes into an integer.  A bit easier to read than bitshifts.

Good luck with your project!

**Code:**

~~~
// TRANSMITTER

#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder

int numbers[3]; // Change 3 to number of integers you wish to send.

void setup()
{
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for RF Link module
  vw_setup(1000);                 // Bits per sec
  //vw_set_tx_pin(3);                // pin 3 is used as the transmit data out into the TX Link module, change this to suit your needs.

  // Initialize to some sample values
  numbers[0] = 32767;
  numbers[1] = -2;
  numbers[2] = 0;
}

void loop()
{
  vw_send( (uint8_t *)numbers, sizeof(numbers));
  vw_wait_tx();  // Wait for message to finish
  delay(1000);

  numbers[0]--;  // decrement
  numbers[1]++;  // increment
  numbers[2]++;  // increment
} 
~~~


**Code:**

~~~
// RECEIVER

#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder

int numbers[3]; // Change 3 to number of integers you wish to send.

void setup()
{
  Serial.begin(4800);

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true);    // Required for RX Link Module
  vw_setup(1000);                   // Bits per sec
  //vw_set_rx_pin(2);           // We will be receiving on pin 23 (Mega) ie the RX pin from the module connects to this pin.
  vw_rx_start();                      // Start the receiver

  Serial.println("Receiver ready!");
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // check to see if anything has been received
  {
    Serial.print(buflen, DEC);
    Serial.println(" bytes received!");
  
    for (int i = 0; i < buflen; i++)
    {
      Serial.print("buf[");
      Serial.print(i, DEC);
      Serial.print("]=");
      Serial.print(buf[i], DEC);
      Serial.print("  ");
    }
    Serial.println();

    //memcpy(buf, numbers, buflen);
    for (int i = 0; i < 3; i++)
    {
      numbers[i] = word(buf[i*2+1], buf[i*2]);
      Serial.print("numbers[");
      Serial.print(i, DEC);
      Serial.print("]=");
      Serial.print(numbers[i], DEC);
      Serial.print("  ");
    }
    Serial.println();
  }
  
  delay(50);
} 
~~~

Last Edit: March 19, 2010, 09:35:19 pm by hwiguna 