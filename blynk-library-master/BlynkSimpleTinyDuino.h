/**
 * @file       BlynkSimpleTinyDuino.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 */

#ifndef BlynkSimpleTinyDuino_h
#define BlynkSimpleTinyDuino_h

#ifndef BLYNK_INFO_DEVICE
#define BLYNK_INFO_DEVICE  &quot;TinyDuino&quot;
#endif

#include &lt;Adapters/BlynkCC3000.h&gt;
#include &lt;Adafruit_CC3000.h&gt;

// Pin definitions for the TinyCircuits WiFi TinyShield
#define ADAFRUIT_CC3000_IRQ  2
#define ADAFRUIT_CC3000_VBAT A3
#define ADAFRUIT_CC3000_CS   8

// Use hardware SPI for the remaining pins (on an UNO, SCK = 13, MISO = 12, and MOSI = 11)
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

static BlynkTransportCC3000 _blynkTransport(cc3000);
BlynkCC3000 Blynk(cc3000, _blynkTransport);

#include &lt;BlynkWidgets.h&gt;

#endif
