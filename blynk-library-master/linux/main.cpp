/**
 * @file       main.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 */

//#define BLYNK_DEBUG
#define BLYNK_PRINT stdout
#ifdef RASPBERRY
 #include &lt;BlynkApiWiringPi.h&gt;
#else
 #include &lt;BlynkApiLinux.h&gt;
#endif
#include &lt;BlynkSocket.h&gt;
#include &lt;BlynkOptionsParser.h&gt;

static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);

BLYNK_WRITE(1)
{
  BLYNK_LOG(&quot;Got a value: %s&quot;, param[0].asStr());
}

int main(int argc, char* argv[])
{
    const char *auth, *serv, *port;
    parse_options(argc, argv, auth, serv, port);

    Blynk.begin(auth, serv, port);

    while(true) {
        Blynk.run();
    }

    return 0;
}
