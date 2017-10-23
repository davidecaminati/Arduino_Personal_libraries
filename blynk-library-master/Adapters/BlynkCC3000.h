/**
 * @file       BlynkCC3000.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkCC3000_h
#define BlynkCC3000_h

#define BLYNK_INFO_CONNECTION &quot;CC3000&quot;

#include &lt;BlynkApiArduino.h&gt;
#include &lt;Blynk/BlynkProtocol.h&gt;
#include &lt;Adafruit_CC3000.h&gt;

class BlynkTransportCC3000
{
public:
    BlynkTransportCC3000(Adafruit_CC3000&amp; cc3000)
        : cc3000(cc3000), addr(0), port(0)
    {}

    void begin(uint32_t a, uint16_t p) {
        port = p;
        addr = a;
    }

    bool connect() {
        uint8_t* a = (uint8_t*)&amp;addr;
        BLYNK_LOG(&quot;Connecting to %d.%d.%d.%d:%d&quot;, a[3], a[2], a[1], a[0], port);
        client = cc3000.connectTCP(addr, port);
        return client.connected();
    }

    void disconnect() { client.stop(); }

    size_t read(void* buf, size_t len) {
        return client.readBytes((char*)buf, len);
    }
    size_t write(const void* buf, size_t len) {
        return client.write((const uint8_t*)buf, len);
    }

    void flush() { client.flush(); }
    bool connected() { return client.connected(); }
    int available() { return client.available(); }

private:
    Adafruit_CC3000&amp; cc3000;
    Adafruit_CC3000_Client client;
    uint32_t    addr;
    uint16_t    port;
};

class BlynkCC3000
    : public BlynkProtocol&lt;BlynkTransportCC3000&gt;
{
    typedef BlynkProtocol&lt;BlynkTransportCC3000&gt; Base;
public:
    BlynkCC3000(Adafruit_CC3000&amp; cc3000, BlynkTransportCC3000&amp; transp)
        : Base(transp), cc3000(cc3000)
    {}

    void wifi_begin (const char* ssid,
                     const char* pass,
                     uint8_t secmode)
    {
        if (!cc3000.begin())
        {
            BLYNK_FATAL(&quot;Couldn't begin()! Check your wiring?&quot;);
        }

#if !defined(CC3000_TINY_DRIVER) &amp;&amp; defined(BLYNK_DEBUG)
        uint8_t major, minor;
        if(!cc3000.getFirmwareVersion(&amp;major, &amp;minor))
        {
            if(major != 0x1 || minor &lt; 0x13) {
                BLYNK_LOG(&quot;CC3000 upgrade needed?&quot;);
            }
        }
#endif
        /*if (!cc3000.deleteProfiles())
        {
            BLYNK_FATAL(&quot;Fail deleting old profiles&quot;);
        }*/
        BLYNK_LOG(&quot;Connecting to %s...&quot;, ssid);
        if (!cc3000.connectToAP(ssid, pass, secmode))
        {
            BLYNK_FATAL(&quot;Failed to connect to AP&quot;);
        }
        BLYNK_LOG(&quot;Getting IP address...&quot;);
        while (!cc3000.checkDHCP())
        {
            delay(100);
        }
#ifdef BLYNK_PRINT
        uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
        if(!cc3000.getIPAddress(&amp;ipAddress, &amp;netmask, &amp;gateway, &amp;dhcpserv, &amp;dnsserv))
        {
            BLYNK_FATAL(&quot;Unable to get the IP Address&quot;);
        }
        uint8_t* addr = (uint8_t*)&amp;ipAddress;
        BLYNK_LOG(&quot;IP:  %d.%d.%d.%d&quot;, addr[3], addr[2], addr[1], addr[0]);
        addr = (uint8_t*)&amp;gateway;
        BLYNK_LOG(&quot;GW:  %d.%d.%d.%d&quot;, addr[3], addr[2], addr[1], addr[0]);
        addr = (uint8_t*)&amp;dnsserv;
        BLYNK_LOG(&quot;DNS: %d.%d.%d.%d&quot;, addr[3], addr[2], addr[1], addr[0]);
#endif
    }

    void begin( const char* auth,
                const char* ssid,
                const char* pass,
                uint8_t secmode,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        wifi_begin(ssid, pass, secmode);
        uint32_t ip = 0;
        BLYNK_LOG(&quot;Looking for %s&quot;, domain);
        while (ip == 0) {
            if (!cc3000.getHostByName((char*)domain, &amp;ip)) {
                BLYNK_LOG(&quot;Couldn't locate server&quot;);
                delay(500);
            }
        }

        this-&gt;conn.begin(ip, port);
    }

    void begin( const char* auth,
                const char* ssid,
                const char* pass,
                uint8_t secmode,
                IPAddress addr,
                uint16_t port)
    {
        Base::begin(auth);
        wifi_begin(ssid, pass, secmode);
        this-&gt;conn.begin(cc3000.IP2U32(addr[0],addr[1],addr[2],addr[3]), port);
    }
private:
    Adafruit_CC3000&amp; cc3000;
};

#endif
