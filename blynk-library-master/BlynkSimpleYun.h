/**
 * @file       BlynkSimpleYun.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkSimpleYun_h
#define BlynkSimpleYun_h

#ifndef BLYNK_INFO_DEVICE
#define BLYNK_INFO_DEVICE  &quot;Arduino Yun&quot;
#endif

#include &lt;Blynk/BlynkProtocol.h&gt;
#include &lt;Adapters/BlynkArduinoClient.h&gt;
#include &lt;YunClient.h&gt;

typedef BlynkArduinoClient BlynkArduinoClientYun;

class BlynkYun
    : public BlynkProtocol&lt; BlynkArduinoClientYun &gt;
{
    typedef BlynkProtocol&lt; BlynkArduinoClientYun &gt; Base;
public:
    BlynkYun(BlynkArduinoClientYun&amp; transp)
        : Base(transp)
    {}

    void begin(const char* auth,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Bridge init...&quot;);
        Bridge.begin();
        this-&gt;conn.begin(domain, port);
    }

    void begin(const char* auth,
               IPAddress ip,
               uint16_t port)
    {
        Base::begin(auth);
        BLYNK_LOG(&quot;Bridge init...&quot;);
        Bridge.begin();
        this-&gt;conn.begin(ip, port);
    }

};

static YunClient _blynkYunClient;
static BlynkArduinoClient _blynkTransport(_blynkYunClient);
BlynkYun Blynk(_blynkTransport);

#include &lt;BlynkWidgets.h&gt;

#endif
