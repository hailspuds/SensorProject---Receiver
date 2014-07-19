# Simple Radio Receiver

This is a really simple project using the [VirtualWire](http://www.airspayce.com/mikem/arduino/VirtualWire/) class to send a simple signal from a Transmitter ([see project here](https://github.com/hailspuds/SensorProject---Transmitter)) to a receiver, then to Sparkfun's Phant data storage service via the Arduino.

This should work as is. My code is released under the MIT licence.

The only thing you need to do is change the file ```HeaderKey.h.sample.h``` to ```HeaderKey.h``` and then paste your public and private key in:

~~~
#define PHANT_PUBLIC_KEY "FILL-IN-PUBLIC-KEY-HERE";
#define PHANT_PRIVATE_KEY "FILL-IN-PRIVATE-KEY-HERE";
~~~


#### Thanks

The demo/example Sketch for VirtualWire uses a text string. While this works well, I ran into problems converting and processing the string to then send to Phant. In the end, I changed the code on the Transmitter side to send an array of integers (or numbers). I found [this thread on The Arduino forums](http://forum.arduino.cc/index.php/topic,16717.0.html) which helped with that immensely. So a big thanks to the user [hari](http://forum.arduino.cc/index.php?&action=profile;u=18935) for showing me the way.

Just in case, I have [mirrored hari's very useful post here.](hari_code_mirror.md)

Also, a massive thanks to Mike McCauley for the ever wonderful [VirtualWire library](http://www.airspayce.com/mikem/arduino/VirtualWire/). Without it, I'd be stuffed.