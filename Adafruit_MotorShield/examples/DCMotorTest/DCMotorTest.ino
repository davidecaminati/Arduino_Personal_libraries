/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
----&gt;	http://www.adafruit.com/products/1438
*/

#include &lt;Wire.h&gt;
#include &lt;Adafruit_MotorShield.h&gt;
#include &quot;utility/Adafruit_PWMServoDriver.h&quot;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println(&quot;Adafruit Motorshield v2 - DC Motor test!&quot;);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor-&gt;setSpeed(150);
  myMotor-&gt;run(FORWARD);
  // turn on motor
  myMotor-&gt;run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print(&quot;tick&quot;);

  myMotor-&gt;run(FORWARD);
  for (i=0; i&lt;255; i++) {
    myMotor-&gt;setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor-&gt;setSpeed(i);  
    delay(10);
  }
  
  Serial.print(&quot;tock&quot;);

  myMotor-&gt;run(BACKWARD);
  for (i=0; i&lt;255; i++) {
    myMotor-&gt;setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor-&gt;setSpeed(i);  
    delay(10);
  }

  Serial.print(&quot;tech&quot;);
  myMotor-&gt;run(RELEASE);
  delay(1000);
}