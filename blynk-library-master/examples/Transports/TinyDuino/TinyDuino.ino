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
 * This example shows how to use TinyCircuits CC3000 shield
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include &lt;SPI.h&gt;
#include &lt;Adafruit_CC3000.h&gt;
#include &lt;BlynkSimpleTinyDuino.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, &quot;ssid&quot;, &quot;pass&quot;, WLAN_SEC_WPA2);
}

void loop()
{
  Blynk.run();
}

