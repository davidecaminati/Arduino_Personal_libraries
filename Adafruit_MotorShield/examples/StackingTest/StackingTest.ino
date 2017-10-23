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

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// On the top shield, connect two steppers, each with 200 steps
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper3 = AFMStop.getStepper(200, 2);

// On the bottom shield connect a stepper to port M3/M4 with 200 steps
Adafruit_StepperMotor *myStepper1 = AFMSbot.getStepper(200, 2);
// And a DC Motor to port M1
Adafruit_DCMotor *myMotor1 = AFMSbot.getMotor(1);

void setup() {
  while (!Serial);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println(&quot;MMMMotor party!&quot;);

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
   
  // turn on the DC motor
  myMotor1-&gt;setSpeed(200);
  myMotor1-&gt;run(RELEASE);
}

int i;
void loop() {
  myMotor1-&gt;run(FORWARD);
  
  for (i=0; i&lt;255; i++) {
    myMotor1-&gt;setSpeed(i);  
    myStepper1-&gt;onestep(FORWARD, INTERLEAVE);
    myStepper2-&gt;onestep(BACKWARD, DOUBLE);
    myStepper3-&gt;onestep(FORWARD, MICROSTEP);
    delay(3);
 }
 
 for (i=255; i!=0; i--) {
    myMotor1-&gt;setSpeed(i);  
    myStepper1-&gt;onestep(BACKWARD, INTERLEAVE);
    myStepper2-&gt;onestep(FORWARD, DOUBLE);
    myStepper3-&gt;onestep(BACKWARD, MICROSTEP);
    delay(3);
 }
 
  myMotor1-&gt;run(BACKWARD);
  
  for (i=0; i&lt;255; i++) {
    myMotor1-&gt;setSpeed(i);  
    myStepper1-&gt;onestep(FORWARD, DOUBLE);
    myStepper2-&gt;onestep(BACKWARD, INTERLEAVE);
    myStepper3-&gt;onestep(FORWARD, MICROSTEP);
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    myMotor1-&gt;setSpeed(i);  
    myStepper1-&gt;onestep(BACKWARD, DOUBLE);
    myStepper2-&gt;onestep(FORWARD, INTERLEAVE);
    myStepper3-&gt;onestep(BACKWARD, MICROSTEP);
    delay(3);
 }
}