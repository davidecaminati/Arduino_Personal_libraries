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
 * This example shows how to use Adafruit CC3000 breakout
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * For this example you need Adafruit_CC3000_Library library:
 *   https://github.com/adafruit/Adafruit_CC3000_Library
 *
 * 1. Update pin definitions according to your setup.
 * 2. Change WiFi ssid, pass, and Blynk auth token
 * 3. Run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

// These are the interrupt and control pins for Ð¡Ð¡3000
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

#include &lt;SPI.h&gt;
#include &lt;Adafruit_CC3000.h&gt;
#include &lt;BlynkSimpleCC3000.h&gt;

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

