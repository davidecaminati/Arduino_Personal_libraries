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
 * Control a color gradient on NeoPixel strip using a slider!
 *
 * For this example you need NeoPixel library:
 *   https://github.com/adafruit/Adafruit_NeoPixel
 *
 * App dashboard setup:
 *   Slider widget (0...500) on V1
 *
 **************************************************************/

#define BLYNK_PRINT Serial
#include &lt;SPI.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;BlynkSimpleEthernet.h&gt;
#include &lt;Adafruit_NeoPixel.h&gt;

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
  strip.begin();
  strip.show();
}

BLYNK_WRITE(1)
{
  int shift = param[0].asInt();
  for(int i=0; i&lt; strip.numPixels(); i++)
  {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) &amp; 255));
  }
  strip.show();
}

void loop()
{
  Blynk.run();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos &lt; 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos &lt; 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
