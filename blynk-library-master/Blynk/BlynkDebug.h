/**
 * @file       BlynkDebug.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Debug utilities
 *
 */

#ifndef BlynkDebug_h
#define BlynkDebug_h

#include &lt;Blynk/BlynkConfig.h&gt;
#include &lt;stddef.h&gt;
#ifdef ESP8266
    #include &quot;ets_sys.h&quot;
    #include &quot;os_type.h&quot;
    #include &quot;mem.h&quot;
#else
    #include &lt;inttypes.h&gt;
#endif

#if defined(ARDUINO)
    #if ARDUINO &gt;= 100
        #include &quot;Arduino.h&quot;
    #else
        #include &quot;WProgram.h&quot;
    #endif
#endif

// General defines

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define BLYNK_ATTR_PACKED __attribute__ ((__packed__))
#define BLYNK_FORCE_INLINE __attribute__((always_inline))
#define BLYNK_NORETURN __attribute__ ((noreturn))

#if defined(__AVR__)
    #include &lt;avr/pgmspace.h&gt;
    #define BLYNK_HAS_PROGMEM
    #define BLYNK_PROGMEM PROGMEM
    #define BLYNK_PSTR(s) PSTR(s)
#else
    #define BLYNK_PROGMEM
    #define BLYNK_PSTR(s) s
#endif

// Diagnostic defines

size_t BlynkFreeRam();
void BlynkReset();
void BlynkFatal() BLYNK_NORETURN;

#define BLYNK_FATAL(msg, ...){ BLYNK_LOG(msg, ##__VA_ARGS__); BlynkFatal(); }
#define BLYNK_LOG_RAM()      { BLYNK_LOG(&quot;Free RAM: %d&quot;, BlynkFreeRam()); }
#define BLYNK_LOG_FN()       BLYNK_LOG(&quot;%s@%d&quot;, __FUNCTION__, __LINE__);

#ifdef BLYNK_PRINT

    #if defined(ARDUINO) || defined(SPARK)
        #include &lt;stdio.h&gt;
        #include &lt;stdarg.h&gt;

        #define BLYNK_DBG_DUMP(msg, addr, len) { BLYNK_PRINT.print(msg); BLYNK_PRINT.write((uint8_t*)addr, len); BLYNK_PRINT.println(); }
        #define BLYNK_DBG_BREAK()    { for(;;); }
#if defined(__SAM3X8E__)
        #define BLYNK_LOG(msg, ...)  blynk_dbg_print(msg, ##__VA_ARGS__)
#else
        #define BLYNK_LOG(msg, ...)  blynk_dbg_print(BLYNK_PSTR(msg), ##__VA_ARGS__)
#endif
        #define BLYNK_ASSERT(expr)   { if(!(expr)) { BLYNK_LOG(&quot;Assertion %s failed.&quot;, #expr); BLYNK_DBG_BREAK() } }

        static
        void blynk_dbg_print(const BLYNK_PROGMEM char *fmt, ...)
        {
            va_list ap;
            va_start(ap, fmt);
            char buff[128];
            BLYNK_PRINT.print('[');
            BLYNK_PRINT.print(millis());
            BLYNK_PRINT.print(F(&quot;] &quot;));
#if defined(__AVR__)
            vsnprintf_P(buff, sizeof(buff), fmt, ap);
#else
            vsnprintf(buff, sizeof(buff), fmt, ap);
#endif
            BLYNK_PRINT.println(buff);
            va_end(ap);
        }

    #elif defined(LINUX)

        #include &lt;assert.h&gt;
        #include &lt;stdio.h&gt;
        #include &lt;string.h&gt;
        #include &lt;errno.h&gt;
        #include &lt;signal.h&gt;

        #define BLYNK_DBG_DUMP(msg, addr, len) { fprintf(BLYNK_PRINT, msg); fwrite(addr, len, 1, BLYNK_PRINT); fputc('\n', BLYNK_PRINT); }
        #define BLYNK_DBG_BREAK()    raise(SIGTRAP);
        #define BLYNK_LOG(msg, ...)  { fprintf(BLYNK_PRINT, &quot;[%ld] &quot; msg &quot;\n&quot;, millis(), ##__VA_ARGS__); }
        #define BLYNK_ASSERT(expr)   assert(expr)

    #elif defined(WINDOWS)

        #include &lt;windows.h&gt;
        #include &lt;stdio.h&gt;

        #define BLYNK_DBG_DUMP(msg, addr, len)
        #define BLYNK_DBG_BREAK()    DebugBreak();
        #define BLYNK_LOG(...)       { char buff[1024]; snprintf(buff, sizeof(buff), __VA_ARGS__); OutputDebugString(buff); }
        #define BLYNK_ASSERT(expr)   { if(!(expr)) { BLYNK_DBG_BREAK() } }

    #elif defined(ESP8266)

        #define BLYNK_DBG_DUMP(msg, addr, len) { ets_uart_printf(msg); uart0_tx_buffer(addr, len); ets_uart_printf(&quot;\n&quot;); }
        #define BLYNK_DBG_BREAK()    abort()
        #define BLYNK_LOG(msg, ...)  ets_uart_printf(&quot;[%ld] &quot; msg &quot;\n&quot;, millis(), ##__VA_ARGS__)
        #define BLYNK_ASSERT(expr)   { if(!(expr)) { BLYNK_DBG_BREAK() } }

    #else

        #warning Could not detect platform
        #define BLYNK_DBG_DUMP(msg, addr, len)
        #define BLYNK_DBG_BREAK()    { *(char*)(NULL) = 0xFF; } // SEGV!!!
        #define BLYNK_LOG(...)
        #define BLYNK_ASSERT(expr)   { if(!(expr)) { BLYNK_DBG_BREAK() } }

    #endif

#else

    #define BLYNK_DBG_BREAK()
    #define BLYNK_LOG(msg, ...)
    #define BLYNK_ASSERT(expr)

#endif

#endif
