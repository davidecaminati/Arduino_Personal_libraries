/**
 * @file       BlynkSocket.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 */

#ifndef BlynkSocket_h
#define BlynkSocket_h

#include &lt;sys/socket.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;netinet/in.h&gt;
#include &lt;netinet/tcp.h&gt;
#include &lt;netdb.h&gt;
#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;errno.h&gt;
#include &lt;arpa/inet.h&gt;

#include &lt;Blynk/BlynkProtocol.h&gt;

class BlynkTransportSocket
{
public:
    BlynkTransportSocket()
        : sockfd(-1)
    {}

    void begin(const char* d, const char* p) {
        this-&gt;domain = d;
        this-&gt;port = p;
    }

    bool connect()
    {
        BLYNK_LOG(&quot;Connecting to %s:%s&quot;, domain, port);

        struct addrinfo hints;
        struct addrinfo *res;  // will point to the results

        memset(&amp;hints, 0, sizeof hints); // make sure the struct is empty
        hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

        // get ready to connect
        getaddrinfo(BLYNK_DEFAULT_DOMAIN, TOSTRING(BLYNK_DEFAULT_PORT), &amp;hints, &amp;res);

        if ((sockfd = ::socket(res-&gt;ai_family, res-&gt;ai_socktype, res-&gt;ai_protocol)) &lt; 0)
        {
            BLYNK_LOG(&quot;Can't create socket&quot;);
            return false;
        }

        if (::connect(sockfd, res-&gt;ai_addr, res-&gt;ai_addrlen) &lt; 0)
        {
            BLYNK_LOG(&quot;Can't connect to %s&quot;, BLYNK_DEFAULT_DOMAIN);
            return false;
        }

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&amp;tv,sizeof(struct timeval));

        int one = 1;
        setsockopt(sockfd, SOL_TCP, TCP_NODELAY, &amp;one, sizeof(one));

        freeaddrinfo(res); // TODO: Leak here

        return true;
    }

    void disconnect()
    {
        if (sockfd != -1) {
            while (::close(sockfd) &lt; 0) {
                usleep(10000);
            }
            sockfd = -1;
        }
    }

    size_t read(void* buf, size_t len) {
        return ::read(sockfd, buf, len);
    }

    size_t write(const void* buf, size_t len) {
        return ::write(sockfd, buf, len);
    }

    void flush()    { }
    bool connected() { return sockfd &gt;= 0; }
    int available() { return BLYNK_MAX_READBYTES; }

protected:
    int    sockfd;
    const char* domain;
    const char* port;
};

class BlynkSocket
    : public BlynkProtocol&lt;BlynkTransportSocket&gt;
{
    typedef BlynkProtocol&lt;BlynkTransportSocket&gt; Base;
public:
    BlynkSocket(BlynkTransportSocket&amp; transp)
        : Base(transp)
    {}

    void begin(const char* auth,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               const char* port   = TOSTRING(BLYNK_DEFAULT_PORT))
    {
        Base::begin(auth);
        this-&gt;conn.begin(domain, port);
    }

};

#endif
