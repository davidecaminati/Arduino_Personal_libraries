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
 * This example shows how to use CC3000 on WildFire board
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * For this example you need a WildFire device,
 * and also to install &quot;Combined Arduino Support Package&quot;.
 * Please find more information here:
 *   http://shop.wickeddevice.com/resources/wildfire
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include &lt;SPI.h&gt;
#include &lt;WildFire.h&gt;
#include &lt;WildFire_CC3000.h&gt;
#include &lt;BlynkSimpleWildFire.h&gt;

WildFire wildfire;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Serial.begin(9600);
  wildfire.begin();
  Blynk.begin(auth, &quot;ssid&quot;, &quot;pass&quot;, WLAN_SEC_WPA2);
}

void loop()
{
  Blynk.run();
}

