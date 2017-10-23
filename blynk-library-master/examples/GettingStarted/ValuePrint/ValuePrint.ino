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
 * You can use this sketch as a debug tool that prints all incoming values
 * sent by a widget connected to a Virtual Pin 1 in the Blynk App.
 *
 * App dashboard setup:
 *   Slider widget (0...100) on V1
 *
 **************************************************************/

#define BLYNK_PRINT Serial
#include &lt;SPI.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;BlynkSimpleEthernet.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
}

// This function will be called every time
// when App writes value to Virtual Pin 1
BLYNK_WRITE(1)
{
  BLYNK_DBG_DUMP(&quot;Got a value: &quot;, param.getBuffer(), param.getLength());
}

void loop()
{
  Blynk.run();
}
