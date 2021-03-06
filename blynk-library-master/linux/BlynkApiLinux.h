/**
 * @file       BlynkApiLinux.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkApiLinux_h
#define BlynkApiLinux_h

#include &lt;Blynk/BlynkApi.h&gt;

#define _POSIX_C_SOURCE 200809L
#include &lt;time.h&gt;
#include &lt;unistd.h&gt;

#ifndef BLYNK_INFO_DEVICE
    #define BLYNK_INFO_DEVICE  &quot;Linux&quot;
#endif

static
void delay(unsigned long ms)
{
    usleep(ms * 1000);
}

static
unsigned long millis(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &amp;ts );
    return ( ts.tv_sec * 1000 + ts.tv_nsec / 1000000L );
}

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

        char mem_dyn[32];
        BlynkParam profile_dyn(mem_dyn, 0, sizeof(mem_dyn));
        profile_dyn.add_key(&quot;conn&quot;, &quot;Socket&quot;);

        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, profile, profile_len, profile_dyn.getBuffer(), profile_dyn.getLength());
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
        rsp.add(0); // TODO
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, rsp.getBuffer(), rsp.getLength());
    } else if (!strcmp(cmd, &quot;ar&quot;)) {
        char mem[16];
        BlynkParam rsp(mem, 0, sizeof(mem));
        rsp.add(&quot;aw&quot;);
        rsp.add(pin);
        rsp.add(0); // TODO
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
                BLYNK_LOG(&quot;pinMode %u -&gt; %s&quot;, pin, it.asStr());
#ifdef BLYNK_DEBUG
                    BLYNK_LOG(&quot;Invalid pinMode %u -&gt; %s&quot;, pin, it.asStr());
#endif

                ++it;
            }
        }

        // Should be 1 parameter (value)
        if (++it &gt;= param.end())
            return;

        if (!strcmp(cmd, &quot;dw&quot;)) {
            BLYNK_LOG(&quot;digitalWrite %d -&gt; %d&quot;, pin, it.asInt());
            // TODO: digitalWrite(pin, it.asInt() ? HIGH : LOW);
        } else if (!strcmp(cmd, &quot;aw&quot;)) {
            BLYNK_LOG(&quot;analogWrite %d -&gt; %d&quot;, pin, it.asInt());
            // TODO: analogWrite(pin, it.asInt());
        } else {
            BLYNK_LOG(&quot;Invalid HW cmd: %s&quot;, cmd);
        }
    }
}

#endif
