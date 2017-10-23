/**
 * @file       BlynkSimpleEthernet.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSimpleEthernet_h
#define BlynkSimpleEthernet_h

#include &lt;Adapters/BlynkEthernet.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;EthernetClient.h&gt;

static EthernetClient _blynkEthernetClient;
static BlynkArduinoClient _blynkTransport(_blynkEthernetClient);
BlynkEthernet Blynk(_blynkTransport);

#include &lt;BlynkWidgets.h&gt;

#endif
