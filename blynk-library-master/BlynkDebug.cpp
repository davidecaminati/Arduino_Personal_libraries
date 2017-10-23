/**
 * @file       BlynkDebug.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Debug utilities for Arduino
 */

#include &lt;Blynk/BlynkDebug.h&gt;
#include &lt;Arduino.h&gt;

size_t BlynkFreeRam()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &amp;v - (__brkval == 0 ? (int) &amp;__heap_start : (int) __brkval);
}

void BlynkReset()
{
    void(*resetFunc)(void) = 0;
    resetFunc();
}

void BlynkFatal()
{
    pinMode(LED_BUILTIN, OUTPUT);
    const int rate = 250;
    int i = 10000/rate;
    while (i-- &gt; 0) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(rate);
    }
    BLYNK_LOG(&quot;Resetting&quot;);
    delay(100);
    BlynkReset();
}
