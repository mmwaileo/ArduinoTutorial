//Includes the Arduino Stepper Library
#include <Stepper.h>

/*When using the Stepper library:
   * pins must be mapped to a 1-3-2-4 sequence to work correctly
   * only full-step drive is possible
 */
 
/* Since we drive the motor in the  full step mode (control sequence with four steps), 
 * each step corresponds to a rotation of 11.25 degrees according to the data sheet. 
 * This corresponds to 32 steps per 360° (360° / 11.25° = 32). 
 * In addition, the manufacturer specified a gear ratio of 64:1 for this type of motor. 
 * Normally, this gear ratio must be multiplied by the 32 steps. 
 * If you examine the 28BYJ-48 in more detail, the actual gear ratio is approximately 63.68395:1. 
 * Therefore we set the final number of steps to 2038 (32 * 63.68395=2037.8864).
 */
// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
}

/*In the loop function, we start to drive the motor. First, we set the speed to one revolutions per minute . 
 * Next, we tell the stepper motor to do 2038 steps. As one revolution corresponds to 2038 steps, 
 * the motor’s shaft should move a full revolution in approximately one minute. Next, we set a delay of one second. 
 * Then, we do the same thing again. But this time, we set the speed to 6 rounds per minute 
 * and move the shaft in the other direction (by setting a negative number of steps). 
 * As the the shaft moves six times faster now, the motor should finish a full revolution in about 10 seconds (60s/6=10s).
*/
void loop() {
   /*
    * set speed = 1: 2038 steps per min.  steps per second = 2038/60= 33.97 steps/ per second
    * In 2038 steps turn 360°. Per step Revolution = 360/2038 = 0.177°/step. Use 60 secs to turn 360°.
    * 
    */
  myStepper.setSpeed(1);
  myStepper.step(stepsPerRevolution);
  delay(1000);
   /*
    * set speed = 6. steps per min = 2038*6 steps per min.  steps per second = 2038*6/60 steps/ per second.   
    * In 2038 steps turn 360°. step = -stepsPerRevolution = -2038.  in (2038 * 60/(2038*6))= 10 seconds
    */
  myStepper.setSpeed(6);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
