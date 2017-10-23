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
 * This example shows how to monitor a button state
 * using interrupts mechanism.
 *
 * App dashboard setup:
 *   LED widget on V1
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

  // Make pin 2 HIGH by default
  pinMode(2, INPUT_PULLUP);
  // Attach INT to our handler
  attachInterrupt(0, checkPin, CHANGE);
}

void checkPin()
{
  // Invert state, since button is &quot;Active LOW&quot;
  int state = !digitalRead(2);
  Blynk.virtualWrite(1, state);
}

void loop()
{
  Blynk.run();
}

