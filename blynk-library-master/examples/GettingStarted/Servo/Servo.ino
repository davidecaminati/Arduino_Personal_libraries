/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social groups:              http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * Rotate a servo using a slider!
 *
 * App dashboard setup:
 *   Slider widget (0...180) on V3
 *
 **************************************************************/

#include &lt;SPI.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;BlynkSimpleEthernet.h&gt;
#include &lt;Servo.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

Servo servo;

void setup()
{
  Blynk.begin(auth);
  servo.attach(9);
}

BLYNK_WRITE(3)
{
  servo.write(param[0].asInt());
}

void loop()
{
  Blynk.run();
}
