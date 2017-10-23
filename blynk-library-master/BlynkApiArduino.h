/**
 * @file       BlynkApiArduino.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkApiArduino_h
#define BlynkApiArduino_h

#include &lt;Blynk/BlynkApi.h&gt;
#include &lt;Arduino.h&gt;

#if   defined(__AVR_ATmega168__)
    #define BLYNK_INFO_CPU      &quot;ATmega168&quot;
#elif defined(__AVR_ATmega328P__)
    #define BLYNK_INFO_CPU      &quot;ATmega328P&quot;
#elif defined(__AVR_ATmega1280__)
    #define BLYNK_INFO_CPU      &quot;ATmega1280&quot;
#elif defined(__AVR_ATmega1284__)
    #define BLYNK_INFO_CPU      &quot;ATmega1284&quot;
#elif defined(__AVR_ATmega2560__)
    #define BLYNK_INFO_CPU      &quot;ATmega2560&quot;
#elif defined(__AVR_ATmega32U4__)
    #define BLYNK_INFO_CPU      &quot;ATmega32U4&quot;
#elif defined(__SAM3X8E__)
    #define BLYNK_INFO_CPU      &quot;AT91SAM3X8E&quot;
#endif

#ifndef BLYNK_INFO_DEVICE
    #define BLYNK_INFO_DEVICE  &quot;Arduino&quot;
#endif

template&lt;class Proto&gt;
void BlynkApi&lt;Proto&gt;::Init()
{
}

template&lt;class Proto&gt;
BLYNK_FORCE_INLINE
void BlynkApi&lt;Proto&gt;::processCmd(const void* buff, size_t len)
{
    BlynkParam param((void*)buff, len);
    BlynkParam::iterator it = param.begin();
    if (it &gt;= param.end())
        return;
    const char* cmd = it.asStr();

    if (!strcmp(cmd, &quot;info&quot;)) {
        static const char profile[] BLYNK_PROGMEM =
            BLYNK_PARAM_KV(&quot;ver&quot;    , BLYNK_VERSION)
            BLYNK_PARAM_KV(&quot;h-beat&quot; , TOSTRING(BLYNK_HEARTBEAT))
            BLYNK_PARAM_KV(&quot;buff-in&quot;, TOSTRING(BLYNK_MAX_READBYTES))
#ifdef BLYNK_INFO_DEVICE
            BLYNK_PARAM_KV(&quot;dev&quot;    , BLYNK_INFO_DEVICE)
#endif
#ifdef BLYNK_INFO_CPU
            BLYNK_PARAM_KV(&quot;cpu&quot;    , BLYNK_INFO_CPU)
#endif
#ifdef BLYNK_INFO_CONNECTION
            BLYNK_PARAM_KV(&quot;con&quot;    , BLYNK_INFO_CONNECTION)
#endif
        ;
        const size_t profile_len = sizeof(profile)-1;

#ifdef BLYNK_HAS_PROGMEM
        char mem[profile_len];
        memcpy_P(mem, profile, profile_len);
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, mem, profile_len);
#else
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, profile, profile_len);
#endif
        return;
    }

    if (++it &gt;= param.end())
        return;
    unsigned pin = it.asInt();

    if (!strcmp(cmd, &quot;dr&quot;)) {
        char mem[16];
        BlynkParam rsp(mem, 0, sizeof(mem));
        rsp.add(&quot;dw&quot;);
        rsp.add(pin);
        rsp.add(digitalRead(pin));
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, rsp.getBuffer(), rsp.getLength());
    } else if (!strcmp(cmd, &quot;ar&quot;)) {
        char mem[16];
        BlynkParam rsp(mem, 0, sizeof(mem));
        rsp.add(&quot;aw&quot;);
        rsp.add(pin);
        rsp.add(analogRead(pin));
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, rsp.getBuffer(), rsp.getLength());
    } else if (!strcmp(cmd, &quot;vr&quot;)) {
        if (WidgetReadHandler handler = GetReadHandler(pin)) {
            BlynkReq req = { 0, BLYNK_SUCCESS, (uint8_t)pin };
            handler(req);
        }
    } else {

        if (!strcmp(cmd, &quot;vw&quot;)) {
            ++it;
            if (WidgetWriteHandler handler = GetWriteHandler(pin)) {
                BlynkReq req = { 0, BLYNK_SUCCESS, (uint8_t)pin };
                char* start = (char*)it.asStr();
                BlynkParam param2(start, len - (start - (char*)buff));
                handler(req, param2);
            }
            return;
        }

        if (!strcmp(cmd, &quot;pm&quot;)) {
            while (it &lt; param.end()) {
                ++it;
                //BLYNK_LOG(&quot;pinMode %u -&gt; %s&quot;, pin, it.asStr());
                if (!strcmp(it.asStr(), &quot;in&quot;)) {
                    pinMode(pin, INPUT);
                } else if (!strcmp(it.asStr(), &quot;out&quot;) || !strcmp(it.asStr(), &quot;pwm&quot;)) {
                    pinMode(pin, OUTPUT);
                } else if (!strcmp(it.asStr(), &quot;pu&quot;)) {
                    pinMode(pin, INPUT_PULLUP);
                } else {
#ifdef BLYNK_DEBUG
                    BLYNK_LOG(&quot;Invalid pinMode %u -&gt; %s&quot;, pin, it.asStr());
#endif
                }
                ++it;
            }
        }

        // Should be 1 parameter (value)
        if (++it &gt;= param.end())
            return;

        if (!strcmp(cmd, &quot;dw&quot;)) {
            //BLYNK_LOG(&quot;digitalWrite %d -&gt; %d&quot;, pin, it.asInt());
            pinMode(pin, OUTPUT);
            digitalWrite(pin, it.asInt() ? HIGH : LOW);
        } else if (!strcmp(cmd, &quot;aw&quot;)) {
            //BLYNK_LOG(&quot;analogWrite %d -&gt; %d&quot;, pin, it.asInt());
            analogWrite(pin, it.asInt());
        } else {
            BLYNK_LOG(&quot;Invalid HW cmd: %s&quot;, cmd);
        }
    }
}

#endif
