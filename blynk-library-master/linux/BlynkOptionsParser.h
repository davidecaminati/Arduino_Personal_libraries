
#include &lt;getopt.h&gt;
#include &lt;Blynk/BlynkDebug.h&gt;

static
void parse_options(int argc, char* argv[],
                   const char*&amp; auth,
                   const char*&amp; serv,
                   const char*&amp; port)
{
    static struct option long_options[] = {
        {&quot;token&quot;,   required_argument,   0, 't'},
        {&quot;server&quot;,  required_argument,   0, 's'},
        {&quot;port&quot;,    required_argument,   0, 'p'},
        {0, 0, 0, 0}
    };

    // Set default values
    auth = NULL;
    serv = BLYNK_DEFAULT_DOMAIN;
    port = TOSTRING(BLYNK_DEFAULT_PORT);

    const char* usage =
        &quot;Usage: blynk [options]\n&quot;
        &quot;\n&quot;
        &quot;Options:\n&quot;
        &quot;  -t auth, --token=auth    Your auth token\n&quot;
        &quot;  -s addr, --server=addr   Server name (default: &quot; BLYNK_DEFAULT_DOMAIN &quot;)\n&quot;
        &quot;  -p num,  --port=num      Server port (default: &quot; TOSTRING(BLYNK_DEFAULT_PORT) &quot;)\n&quot;
        &quot;\n&quot;;

    int rez;
    while (-1 != (rez = getopt_long(argc, argv,&quot;t:s:p:&quot;, long_options, NULL))) {
        switch (rez) {
        case 't': auth = optarg; break;
        case 's': serv = optarg; break;
        case 'p': port = optarg; break;
        default : printf(usage); exit(1);
        };
    };

    // Check mandatory options
    if (!auth) {
    	printf(usage);
        exit(1);
    }
}
