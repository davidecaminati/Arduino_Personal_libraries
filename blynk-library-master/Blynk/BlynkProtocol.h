/**
 * @file       BlynkProtocol.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Blynk protocol implementation
 *
 */

#ifndef BlynkProtocol_h
#define BlynkProtocol_h

#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;Blynk/BlynkDebug.h&gt;
#include &lt;Blynk/BlynkProtocolDefs.h&gt;
#include &lt;Blynk/BlynkApi.h&gt;

template &lt;class Transp&gt;
class BlynkProtocol
    : public BlynkApi&lt; BlynkProtocol&lt;Transp&gt; &gt;
{
public:
    BlynkProtocol(Transp&amp; transp)
        : conn(transp), authkey(NULL)
        , lastActivityIn(0)
        , lastActivityOut(0)
        , lastHeartbeat(0)
        , currentMsgId(0)
    {}

    bool connect();

    void run(void);

    void sendCmd(uint8_t cmd, uint16_t id, const void* data, size_t length, const void* data2 = NULL, size_t length2 = 0);

private:
    bool readHeader(BlynkHeader&amp; hdr);
    uint16_t getNextMsgId();

protected:
    void begin(const char* auth) {
        BLYNK_LOG(&quot;Blynk v&quot; BLYNK_VERSION);
        this-&gt;authkey = auth;
    }
    void processInput(void);

    Transp&amp; conn;

private:
    const char* authkey;
    unsigned long lastActivityIn;
    unsigned long lastActivityOut;
    unsigned long lastHeartbeat;
    uint16_t currentMsgId;
};

template &lt;class Transp&gt;
bool BlynkProtocol&lt;Transp&gt;::connect()
{
    conn.disconnect();
    if (!conn.connect()) {
        delay(5000);
        return false;
    }

    uint16_t id = getNextMsgId();
    sendCmd(BLYNK_CMD_LOGIN, id, authkey, strlen(authkey), NULL, 0);

#ifdef BLYNK_DEBUG
    const unsigned long t = millis();
#endif

    BlynkHeader hdr;
    if (!readHeader(hdr)) {
        hdr.length = BLYNK_TIMEOUT;
    }

    if (BLYNK_CMD_RESPONSE != hdr.type ||
        id != hdr.msg_id ||
        (BLYNK_SUCCESS != hdr.length &amp;&amp; BLYNK_ALREADY_LOGGED_IN != hdr.length))
    {
        if (BLYNK_TIMEOUT == hdr.length) {
            BLYNK_LOG(&quot;Timeout&quot;);
        } else if (BLYNK_INVALID_TOKEN == hdr.length) {
            BLYNK_LOG(&quot;Invalid auth token&quot;);
        } else {
            BLYNK_LOG(&quot;Connect failed (code: %d)&quot;, hdr.length);
            // Send some invalid headers to server for disconnection
            hdr.type = 255;
            hdr.msg_id = 0;
            hdr.length = 0;
            for (int i=0; i&lt;10; i++) {
                conn.write(&amp;hdr, sizeof(hdr));
            }
        }
        conn.disconnect();
        delay(5000);
        return false;
    }

    lastHeartbeat = lastActivityIn = lastActivityOut = millis();
    BLYNK_LOG(&quot;Ready!&quot;);
#ifdef BLYNK_DEBUG
    BLYNK_LOG(&quot;Roundtrip: %dms&quot;, lastActivityIn-t);
#endif

    return true;
}

template &lt;class Transp&gt;
void BlynkProtocol&lt;Transp&gt;::run(void)
{
    if (!conn.connected()) {
        if (!connect()) {
            return;
        }
    }

    if (conn.available() &gt; 0) {
        //BLYNK_LOG(&quot;Available: %d&quot;, conn.available());
        //const unsigned long t = micros();
        processInput();
        //BLYNK_LOG(&quot;Proc time: %d&quot;, micros() - t);
    }

    const unsigned long t = millis();

    if (t - lastActivityIn &gt; (1000UL * BLYNK_HEARTBEAT + BLYNK_TIMEOUT_MS*3)) {
#ifdef BLYNK_DEBUG
        BLYNK_LOG(&quot;Heartbeat timeout (last in: %lu)&quot;, lastActivityIn);
#else
        BLYNK_LOG(&quot;Heartbeat timeout&quot;);
#endif
        conn.disconnect();
    } else if ((t - lastActivityIn &gt; 1000UL * BLYNK_HEARTBEAT ||
               t - lastActivityOut &gt; 1000UL * BLYNK_HEARTBEAT) &amp;&amp;
               t - lastHeartbeat     &gt; BLYNK_TIMEOUT_MS)
    {
        // Send ping if we didn't both send and receive something for BLYNK_HEARTBEAT seconds
#ifdef BLYNK_DEBUG
        BLYNK_LOG(&quot;Heartbeat&quot;);
#endif

        sendCmd(BLYNK_CMD_PING, 0, NULL, 0, NULL, 0);
        lastActivityOut = lastHeartbeat = t;
    }
}

template &lt;class Transp&gt;
BLYNK_FORCE_INLINE
void BlynkProtocol&lt;Transp&gt;::processInput(void)
{
    BlynkHeader hdr;
    if (!readHeader(hdr))
        return;

    switch (hdr.type)
    {
    case BLYNK_CMD_RESPONSE: {
        if (BLYNK_NO_LOGIN == hdr.length) {
            conn.disconnect();
            return;
        }
        // TODO: return code may indicate App presence
    } break;
    case BLYNK_CMD_PING: {
        sendCmd(BLYNK_CMD_RESPONSE, hdr.msg_id, NULL, BLYNK_SUCCESS);
    } break;
    case BLYNK_CMD_HARDWARE: {
        if (hdr.length &gt; BLYNK_MAX_READBYTES) {
            BLYNK_LOG(&quot;Packet size (%u) &gt; max allowed (%u)&quot;, hdr.length, BLYNK_MAX_READBYTES);
            conn.disconnect();
            return;
        }

        uint8_t inputBuffer[hdr.length+1]; // Add 1 to zero-terminate
        if (hdr.length != conn.read(inputBuffer, hdr.length)) {
            BLYNK_LOG(&quot;Can't read body&quot;);
            return;
        }
        inputBuffer[hdr.length] = '\0';

#ifdef BLYNK_DEBUG
        BLYNK_DBG_DUMP(&quot;&gt;&quot;, inputBuffer, hdr.length);
#endif

        currentMsgId = hdr.msg_id;
        this-&gt;processCmd(inputBuffer, hdr.length);
        currentMsgId = 0;
    } break;
    default:
        BLYNK_LOG(&quot;Invalid header type: %d&quot;, hdr.type);
        conn.disconnect();
        return;
    }

    lastActivityIn = millis();
}

template &lt;class Transp&gt;
bool BlynkProtocol&lt;Transp&gt;::readHeader(BlynkHeader&amp; hdr)
{
    if (sizeof(hdr) != conn.read(&amp;hdr, sizeof(hdr))) {
        return false;
    }
    hdr.msg_id = ntohs(hdr.msg_id);
    hdr.length = ntohs(hdr.length);
#ifdef BLYNK_DEBUG
    BLYNK_LOG(&quot;&gt;msg %d,%u,%u&quot;, hdr.type, hdr.msg_id, hdr.length);
#endif
    return true;
}

template &lt;class Transp&gt;
void BlynkProtocol&lt;Transp&gt;::sendCmd(uint8_t cmd, uint16_t id, const void* data, size_t length, const void* data2, size_t length2)
{
    if (!conn.connected()) {
#ifdef BLYNK_DEBUG
        BLYNK_LOG(&quot;Cmd not sent&quot;);
#endif
        return;
    }
    if (0 == id) {
        id = getNextMsgId();
    }
    BlynkHeader hdr;
    hdr.type = cmd;
    hdr.msg_id = htons(id);
    hdr.length = htons(length+length2);
    size_t wlen = 0;
#ifdef BLYNK_DEBUG
    BLYNK_LOG(&quot;&lt;msg %d,%u,%u&quot;, cmd, id, length+length2);
#endif
    wlen += conn.write(&amp;hdr, sizeof(hdr));

    if (cmd != BLYNK_CMD_RESPONSE) {
        if (length) {
#ifdef BLYNK_DEBUG
            BLYNK_DBG_DUMP(&quot;&lt;&quot;, data, length);
#endif
            wlen += conn.write(data, length);
        }
        if (length2) {
#ifdef BLYNK_DEBUG
            BLYNK_DBG_DUMP(&quot;&lt;&quot;, data2, length2);
#endif
            wlen += conn.write(data2, length2);
        }

        if (wlen != sizeof(hdr)+length+length2) {
            BLYNK_LOG(&quot;Sent %u/%u&quot;, wlen, sizeof(hdr)+length+length2);
            conn.disconnect();
            return;
        }
    }
    lastActivityOut = millis();

#ifdef BLYNK_DEBUG
    BLYNK_LOG(&quot;Sent.&quot;);
#endif
}

template &lt;class Transp&gt;
uint16_t BlynkProtocol&lt;Transp&gt;::getNextMsgId()
{
    static uint16_t last = 0;
    if (currentMsgId != 0)
        return currentMsgId;
    if (++last == 0)
        last = 1;
    return last;
}

#endif
