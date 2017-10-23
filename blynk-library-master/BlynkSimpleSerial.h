/**
 * @file       BlynkSimpleSerial.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkSimpleSerial_h
#define BlynkSimpleSerial_h

#include &lt;Adapters/BlynkSerial.h&gt;

#if defined(__SAM3X8E__)
    // For Arduino Due
    typedef BlynkTransportSerialChecked&lt;UARTClass&gt; ArduinoHwSerial;
#elif defined(USBCON)
    // For versions with hw USB, like Micro
    typedef BlynkTransportSerialChecked&lt;Serial_&gt; ArduinoHwSerial;
#else
    // For versions with UART
    typedef BlynkTransportSerial&lt;HardwareSerial&gt; ArduinoHwSerial;
#endif

static ArduinoHwSerial _blynkTransport(Serial);
BlynkSerial&lt;ArduinoHwSerial&gt; Blynk(_blynkTransport);

#include &lt;BlynkWidgets.h&gt;

#endif
