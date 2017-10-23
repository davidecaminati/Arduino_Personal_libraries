/**
 * @file       BlynkParam.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Container for handler parameters
 *
 */

#ifndef BlynkParam_h
#define BlynkParam_h

#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;Blynk/BlynkConfig.h&gt;
#include &lt;Blynk/BlynkDebug.h&gt;

#define BLYNK_PARAM_KV(k, v) k &quot;\0&quot; v &quot;\0&quot;

class BlynkParam
{
public:
    class iterator
    {
    public:
        iterator(char* c) : ptr(c) {}
        static iterator invalid() { return iterator(NULL); }

        operator const char* () const   { return asStr(); }
        operator int () const           { return asInt(); }
        const char* asStr() const       { return ptr; }
        int         asInt() const       { return atoi(ptr); }
        bool isValid() const            { return ptr != NULL; }

        bool operator &lt;  (const iterator&amp; it) const { return ptr &lt; it.ptr; }
        bool operator &gt;= (const iterator&amp; it) const { return ptr &gt;= it.ptr; }

        iterator&amp; operator ++() {
            ptr += strlen(ptr)+1;
            return *this;
        }
    private:
        const char* ptr;
    };

public:
    explicit
    BlynkParam(void* addr, size_t length)
        : buff((char*)addr), len(length), buff_size(length)
    {}

    explicit
    BlynkParam(void* addr, size_t length, size_t buffsize)
        : buff((char*)addr), len(length), buff_size(buffsize)
    {}

    iterator begin() const { return iterator(buff); }
    iterator end() const   { return iterator(buff+len); }

    iterator operator[](int index) const;
    iterator operator[](const char* key) const;

    uint8_t* getBuffer() const { return (uint8_t*)buff; }
    size_t getLength() const { return len; }

    // Modification
    void add(int value);
    void add(unsigned int value);
    void add(long value);
    void add(unsigned long value);
    void add(float value);
    void add(double value);
    void add(const char* str);
    void add(const void* b, size_t l);

    template &lt;typename TV&gt;
    void add_key(const char* key, const TV&amp; val) {
        add(key);
        add(val);
    }

private:
    char*	buff;
    size_t	len;
    size_t	buff_size;
};

#endif
