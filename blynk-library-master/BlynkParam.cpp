/**
 * @file       BlynkParam.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Feb 2015
 * @brief      Container for handler parameters
 *
 */

#include &lt;Blynk/BlynkParam.h&gt;

BlynkParam::iterator BlynkParam::operator[](int index) const
{
    const iterator e = end();
    for (iterator it = begin(); it &lt; e; ++it) {
        if (!index--) {
            return it;
        }
    }
    return iterator::invalid();
}

BlynkParam::iterator BlynkParam::operator[](const char* key) const
{
    const iterator e = end();
    for (iterator it = begin(); it &lt; e; ++it) {
        if (!strcmp(it.asStr(), key)) {
            return ++it;
        }
        ++it;
        if (it &gt;= e) break;
    }
    return iterator::invalid();
}


void BlynkParam::add(const void* b, size_t l)
{
    if (len + l &gt; buff_size)
        return;
    memcpy(buff+len, b, l);
    len += l;
}

void BlynkParam::add(const char* str)
{
    add(str, strlen(str)+1);
}

#if defined(__AVR__)

    #include &lt;stdlib.h&gt;

    void BlynkParam::add(int value)
    {
        char str[2 + 8 * sizeof(value)];
        itoa(value, str, 10);
        add(str);
    }

    void BlynkParam::add(unsigned int value)
    {
        char str[1 + 8 * sizeof(value)];
        utoa(value, str, 10);
        add(str);
    }

    void BlynkParam::add(long value)
    {
        char str[2 + 8 * sizeof(value)];
        ltoa(value, str, 10);
        add(str);
    }

    void BlynkParam::add(unsigned long value)
    {
        char str[1 + 8 * sizeof(value)];
        ultoa(value, str, 10);
        add(str);
    }

    void BlynkParam::add(float value)
    {
        char str[33];
        dtostrf(value, 5, 3, str);
        add(str);
    }

    void BlynkParam::add(double value)
    {
        char str[33];
        dtostrf(value, 5, 3, str);
        add(str);
    }

#else

    #include &lt;stdio.h&gt;

    void BlynkParam::add(int value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%i&quot;, value)+1;
    }

    void BlynkParam::add(unsigned int value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%u&quot;, value)+1;
    }

    void BlynkParam::add(long value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%li&quot;, value)+1;
    }

    void BlynkParam::add(unsigned long value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%lu&quot;, value)+1;
    }

    void BlynkParam::add(float value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%2.3f&quot;, value)+1;
    }

    void BlynkParam::add(double value)
    {
        len += snprintf(buff+len, buff_size-len, &quot;%2.3f&quot;, value)+1;
    }

#endif

