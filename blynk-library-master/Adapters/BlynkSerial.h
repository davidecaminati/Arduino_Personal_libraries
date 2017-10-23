/**
 * @file       BlynkSerial.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSerial_h
#define BlynkSerial_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION &quot;Serial&quot;
#endif

#include &lt;BlynkApiArduino.h&gt;
#include &lt;Blynk/BlynkProtocol.h&gt;

template &lt;class T&gt;
class BlynkTransportSerial
{
public:
    BlynkTransportSerial(T&amp; stream)
        : stream(stream), conn(0)
    {}

    void begin(uint32_t baud) {
        stream.begin(baud);
    }

    bool connect() {
        BLYNK_LOG(&quot;Connecting...&quot;);
        return conn = true;
    }
    void disconnect() { conn = false; }

    size_t read(void* buf, size_t len) {
        return stream.readBytes((char*)buf, len);
    }
    size_t write(const void* buf, size_t len) {
        return stream.write((const uint8_t*)buf, len);
    }
    void flush()    { stream.flush(); }
    bool connected() { return conn; }
    int available() { return stream.available(); }

protected:
    T&amp;     stream;
    bool   conn;
};

template &lt;class T&gt;
class BlynkTransportSerialChecked
    : public BlynkTransportSerial&lt;T&gt;
{
public:
    BlynkTransportSerialChecked(T&amp; stream)
        : BlynkTransportSerial&lt;T&gt;(stream)
    {}

    void begin(uint32_t baud) {
        this-&gt;stream.begin(baud);
        while (!this-&gt;stream) {
            // wait for serial port to connect. Needed for Leonardo only
        }
    }

    int connected() { return this-&gt;conn &amp;&amp; this-&gt;stream; }
};

template &lt;class T&gt;
class BlynkSerial
    : public BlynkProtocol&lt;T&gt;
{
    typedef BlynkProtocol&lt;T&gt; Base;
public:
    BlynkSerial(T&amp; transp)
        : Base(transp)
    {}

    void begin(const char* auth, uint32_t baud = 9600) {
        Base::begin(auth);
        this-&gt;conn.begin(baud);
    }

};

#endif
