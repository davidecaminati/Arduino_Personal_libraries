/**
 * @file       BlynkSimpleWifi.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSimpleWifi_h
#define BlynkSimpleWifi_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION  &quot;HDG204&quot;
#endif

#include &lt;Blynk/BlynkProtocol.h&gt;
#include &lt;Adapters/BlynkArduinoClient.h&gt;
#include &lt;WiFi.h&gt;

class BlynkWifi
    : public BlynkProtocol&lt;BlynkArduinoClient&gt;
{
    typedef BlynkProtocol&lt;BlynkArduinoClient&gt; Base;
public:
    BlynkWifi(BlynkArduinoClient&amp; transp)
        : Base(transp)
    {}

    void wifi_conn(const char* ssid, const char* pass)
    {
        int status = WL_IDLE_STATUS;
         // check for the presence of the shield:
         if (WiFi.status() == WL_NO_SHIELD) {
             BLYNK_FATAL(&quot;WiFi shield not present&quot;);
         }

         // attempt to connect to Wifi network:
         while (status != WL_CONNECTED) {
             BLYNK_LOG(&quot;Attempting to connect to SSID: %s&quot;, ssid);
             status = WiFi.begin((char*)ssid, pass);
         }
         BLYNK_LOG(&quot;Connected to wifi&quot;);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        wifi_conn(ssid, pass);
        this-&gt;conn.begin(domain, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               IPAddress ip,
               uint16_t port)
    {
        Base::begin(auth);
        wifi_conn(ssid, pass);
        this-&gt;conn.begin(ip, port);
    }

};

static WiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkWifi Blynk(_blynkTransport);

#include &lt;BlynkWidgets.h&gt;

#endif
