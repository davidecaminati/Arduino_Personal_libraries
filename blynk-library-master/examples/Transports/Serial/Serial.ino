/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social groups:              http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how to use ordinary Arduino Serial
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * 1. Edit auth token and upload this sketch.
 *
 * 2. Run the script (script located in &quot;scripts&quot; folder of library root,
 *    e.g. 'blynk-library/scripts') for redirecting traffic to server:
 *
 *      for Windows:         scripts/blynk-ser.bat
 *      for Linux and OSX:   ./scripts/blynk-ser.sh (may need to run with sudo)
 *
 *    You can specify port, baud rate, and server endpoint like this:
 *      ./blynk-ser.sh -c &lt;serial port&gt; -b &lt;baud rate&gt; -s &lt;server address&gt; -p &lt;server port&gt;
 *
 *    For instance :
 *      ./blynk-ser.sh -c /dev/ttyACM0 -b 9600 -s cloud.blynk.cc -p 8442
 *
 *    Run blynk-ser.sh -h for more information
 *
 *    Be sure to select the right serial port (there may be multiple).
 *
 *    Attention!
 *        Arduino IDE may complain with &quot;programmer is not responding&quot;.
 *        You need to terminate script before uploading new sketch.
 *
 * 3. Start blynking! :)
 *
 **************************************************************/

#include &lt;BlynkSimpleSerial.h&gt;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = &quot;YourAuthToken&quot;;

void setup()
{
  Blynk.begin(auth);
  // Default baud rate is 9600. You could specify it like this:
  //Blynk.begin(auth, 57600);
}

void loop()
{
  Blynk.run();
}

