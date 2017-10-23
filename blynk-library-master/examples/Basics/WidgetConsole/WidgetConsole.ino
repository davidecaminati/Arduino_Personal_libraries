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
 * You can send/receive any data using WidgetConsole object.
 *
 * App dashboard setup:
 *   Console widget on V1
 *
 **************************************************************/

#define BLYNK_PRINT Serial
#include &lt;SPI.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;BlynkSimpleEthernet.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

// Attach virtual serial console to virtual pin 1
WidgetConsole console(1);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
}

BLYNK_WRITE(1)
{
  BLYNK_LOG(&quot;Hey! I got a new message!&quot;);

  // Send it back
  console.println(&quot;I got:&quot;);
  console.write(param.getBuffer(), param.getLength());
  console.flush();
}

void loop()
{
  Blynk.run();
}

