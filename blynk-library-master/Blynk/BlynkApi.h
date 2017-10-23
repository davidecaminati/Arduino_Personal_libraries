/**
 * @file       BlynkApi.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      High-level functions
 *
 */

#ifndef BlynkApi_h
#define BlynkApi_h

#include &lt;Blynk/BlynkConfig.h&gt;
#include &lt;Blynk/BlynkDebug.h&gt;
#include &lt;Blynk/BlynkParam.h&gt;
#include &lt;Blynk/BlynkHandlers.h&gt;
#include &lt;Blynk/BlynkProtocolDefs.h&gt;

/**
* A test class. A more elaborate class description.
*/
template &lt;class Proto&gt;
class BlynkApi
{
public:
    BlynkApi() {
        Init();
    }

    template &lt;typename T&gt;
    void virtualWrite(int pin, const T&amp; data) {
        char mem[64];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(&quot;vw&quot;);
        cmd.add(pin);
        cmd.add(data);
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength());
    }

    void virtualWrite(int pin, const void* buff, size_t len) {
        char mem[8];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(&quot;vw&quot;);
        cmd.add(pin);
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength(), buff, len);
    }

    void virtualWrite(int pin, const BlynkParam&amp; param) {
        virtualWrite(pin, param.getBuffer(), param.getLength());
    }

    void tweet(const char* msg) {
        size_t len = strlen(msg);
        if (len &lt; 140) {
            static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_TWEET, 0, msg, len);
        }
    }

#if defined(BLYNK_HAS_CALL_BLYNK_READ)

    void call_BLYNK_READ(int pin) {
        if (WidgetReadHandler handler = GetReadHandler(pin)) {
            BlynkReq req = { 0, BLYNK_SUCCESS, (uint8_t)pin };
            handler(req);
        }
    }

#endif

#if defined(BLYNK_HAS_VIRTUAL_READ)

    void virtualRead(int pin) {
        char mem[8];
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add(&quot;vr&quot;);
        cmd.add(pin);
        static_cast&lt;Proto*&gt;(this)-&gt;sendCmd(BLYNK_CMD_HARDWARE, 0, cmd.getBuffer(), cmd.getLength());
    }

#endif

#if defined(BLYNK_HAS_DELAY)

    void delay(unsigned long ms) {
        uint16_t start = (uint16_t)micros();
        while (ms &gt; 0) {
            static_cast&lt;Proto*&gt;(this)-&gt;run();
            yield();
            if (((uint16_t)micros() - start) &gt;= 1000) {
                ms--;
                start += 1000;
            }
        }
    }

#endif

protected:
    void Init();
    void processCmd(const void* buff, size_t len);

};


#endif
