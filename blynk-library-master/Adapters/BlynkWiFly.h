/**
 * @file       BlynkWiFly.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkWiFly_h
#define BlynkWiFly_h

#ifndef BLYNK_INFO_DEVICE
#define BLYNK_INFO_DEVICE  &quot;WiFly&quot;
#endif

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION &quot;RN-XV&quot;
#endif

#include &lt;BlynkApiArduino.h&gt;
#include &lt;Blynk/BlynkProtocol.h&gt;
#include &lt;Adapters/BlynkArduinoClient.h&gt;

class BlynkTransportWiFly
{
public:
    BlynkTransportWiFly()
        : client(NULL)
    {}

    void begin_domain(const char* d,  uint16_t p) {
        if (client)
            delete client;
        client = new WiFlyClient(d, p);
    }

    void begin_addr(IPAddress a, uint16_t p) {
        if (client)
            delete client;
        uint32_t addr = a;
        client = new WiFlyClient((uint8_t*)addr, p);
    }

    bool connect() {
        if (!client)
            return 0;
        if (client-&gt;_domain) {
            BLYNK_LOG(&quot;Connecting to %s:%d&quot;, client-&gt;_domain, client-&gt;_port);
        } else if (client-&gt;_ip) {
            BLYNK_LOG(&quot;Connecting to %d.%d.%d.%d:%d&quot;,
                client-&gt;_ip[0], client-&gt;_ip[1], client-&gt;_ip[2], client-&gt;_ip[3], client-&gt;_port);
        }
        return client-&gt;connect();
    }
    void disconnect() { client-&gt;stop(); }

    size_t read(void* buf, size_t len) {
        return client-&gt;readBytes((char*)buf, len);
    }
    size_t write(const void* buf, size_t len) {
        return client-&gt;write((const uint8_t*)buf, len);
    }

    void flush()	{ client-&gt;flush(); }
    bool connected() { return client-&gt;connected(); }
    int available() { return client-&gt;available(); }

private:
    WiFlyClient* client;
};

class BlynkWiFly
    : public BlynkProtocol&lt;BlynkTransportWiFly&gt;
{
    typedef BlynkProtocol&lt;BlynkTransportWiFly&gt; Base;
public:
    BlynkWiFly(BlynkTransportWiFly&amp; transp)
        : Base(transp)
    {}

    void begin( const char* auth,
                const char* ssid,
                const char* pass,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        WiFly.begin();
        if (!WiFly.join(ssid, pass)) {
            BLYNK_FATAL(&quot;WiFly: Association failed.&quot;);
        }
        this-&gt;conn.begin_domain(domain, port);
    }

    void begin( const char* auth,
                const char* ssid,
                const char* pass,
                IPAddress addr,
                uint16_t port)
    {
        Base::begin(auth);
        WiFly.begin();
        if (!WiFly.join(ssid, pass)) {
            BLYNK_FATAL(&quot;WiFly: Association failed.&quot;);
        }
        this-&gt;conn.begin_addr(addr, port);
    }

};

#endif
