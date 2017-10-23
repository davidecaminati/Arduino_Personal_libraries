/**
 * @file       BlynkEthernet.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkEthernet_h
#define BlynkEthernet_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION &quot;W5000&quot;
#endif

#include &lt;BlynkApiArduino.h&gt;
#include &lt;Blynk/BlynkProtocol.h&gt;
#include &lt;Adapters/BlynkArduinoClient.h&gt;
#include &lt;Ethernet.h&gt;

static const byte _blynkEthernetMac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

class BlynkEthernet
    : public BlynkProtocol&lt;BlynkArduinoClient&gt;
{
    typedef BlynkProtocol&lt;BlynkArduinoClient&gt; Base;
public:
    BlynkEthernet(BlynkArduinoClient&amp; transp)
        : Base(transp)
    {}

    // DHCP with domain
    void begin( const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t port      = BLYNK_DEFAULT_PORT,
                const byte mac[]   = _blynkEthernetMac)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Getting IP...&quot;);
        if (!Ethernet.begin((byte*)mac)) {
            BLYNK_FATAL(&quot;DHCP Failed!&quot;);
        }
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(domain, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

    // Static IP with domain
    void begin( const char* auth,
                const char* domain,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                const byte mac[]= _blynkEthernetMac)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Using static IP&quot;);
        Ethernet.begin((byte*)mac, local);
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(domain, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

    // Static IP with domain, gateway, etc
    void begin( const char* auth,
                const char* domain,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                IPAddress gateway,
                IPAddress subnet,
                const byte mac[]= _blynkEthernetMac)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Using static IP&quot;);
        Ethernet.begin((byte*)mac, local, dns, gateway, subnet);
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(domain, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

    // DHCP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                const byte mac[] = _blynkEthernetMac)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Getting IP...&quot;);
        if (!Ethernet.begin((byte*)mac)) {
            BLYNK_FATAL(&quot;DHCP Failed!&quot;);
        }
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(addr, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

    // Static IP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                IPAddress local,
                const byte mac[] = _blynkEthernetMac)
    {
        BLYNK_LOG(&quot;Using static IP&quot;);
        Base::begin(auth);
        Ethernet.begin((byte*)mac, local);
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(addr, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

    // Static IP with server IP, DNS, gateway, etc
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                IPAddress gateway,
                IPAddress subnet,
                const byte mac[] = _blynkEthernetMac)
    {
        BLYNK_LOG(&quot;Using static IP&quot;);
        Base::begin(auth);
        Ethernet.begin((byte*)mac, local, dns, gateway, subnet);
        // give the Ethernet shield a second to initialize:
        delay(1000);
        this-&gt;conn.begin(addr, port);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG(&quot;My IP: %d.%d.%d.%d&quot;, myip[0], myip[1], myip[2], myip[3]);
    }

};

#endif
