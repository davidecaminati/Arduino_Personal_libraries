/**
 * @file       WidgetConsole.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 */

#ifndef WidgetConsole_h
#define WidgetConsole_h

#include &lt;Print.h&gt;
#include &lt;Blynk/BlynkApi.h&gt;

class WidgetConsole
    : public Print
{
public:
    WidgetConsole(int pin)
        : mPin(pin), mOutQty(0)
    {}

    virtual ~WidgetConsole() {}

    virtual size_t write(uint8_t byte) {
        mOutBuf[mOutQty++] = byte;
        if (mOutQty &gt;= sizeof(mOutBuf)) {
            flush();
        }
        return 1;
    }

    void flush() {
        if (mOutQty) {
            Blynk.virtualWrite(mPin, mOutBuf, mOutQty);
            mOutQty = 0;
        }
    }

    using Print::write;

private:
    uint8_t mPin;
    uint8_t mOutBuf[32];
    uint8_t mOutQty;
};

#endif
