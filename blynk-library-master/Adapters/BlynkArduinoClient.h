/**
 * @file       BlynkParam.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkArduinoClient_h
#define BlynkArduinoClient_h

#include &lt;BlynkApiArduino.h&gt;
#include &lt;Client.h&gt;
#include &lt;Blynk/BlynkDebug.h&gt;

class BlynkArduinoClient
{
public:
    BlynkArduinoClient(Client&amp; client)
        : client(client), domain(NULL), port(0)
    {}

    void begin(IPAddress a, uint16_t p) {
        domain = NULL;
        port = p;
        addr = a;
    }

    void begin(const char* d, uint16_t p) {
        domain = d;
        port = p;
    }

    bool connect() {
        if (domain) {
            BLYNK_LOG(&quot;Connecting to %s:%d&quot;, domain, port);
            return (1 == client.connect(domain, port));
        } else if (addr) {
            BLYNK_LOG(&quot;Connecting to %d.%d.%d.%d:%d&quot;, addr[0], addr[1], addr[2], addr[3], port);
            return (1 == client.connect(addr, port));
        }
        return 0;
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
    Client&amp;     client;
    IPAddress   addr;
    const char* domain;
    uint16_t    port;
};

#endif
