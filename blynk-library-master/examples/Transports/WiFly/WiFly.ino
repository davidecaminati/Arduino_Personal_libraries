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
 * This example shows how to use WiFly RN-XV
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * For this example you need WiFly_Shield library
 * https://github.com/sparkfun/WiFly-Shield/tree/master/Libraries/WiFly_Shield
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include &lt;SPI.h&gt;
#include &lt;WiFly.h&gt;
#include &lt;BlynkSimpleWiFly.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, &quot;ssid&quot;, &quot;pass&quot;);
}

void loop()
{
  Blynk.run();
}

