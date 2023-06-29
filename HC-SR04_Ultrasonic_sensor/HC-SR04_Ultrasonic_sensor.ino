// (For the programming code, first we need to define the Trigger Pin and Echo Pin that connected to Arduino board. 
// In this project EchoPin is attached to D2 and TrigPin to D3. 
// Then define variables for the distance (int) and duration (long).)

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO Wifi R2");
}
void loop() {
  /*In the loop first you have to make sure that the trigPin is clear so we have to set that pin on a LOW State for just 2 µs)
   *Clears the trigPin condition*/
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /*Now for generating the ultrasound wave we have to set the trigPin on HIGH State for 10 µs.
   *That will send out an 8 cycle sonic burst which will travel at the speed sound (340 m/s or 0.034 cm/µs) and it will be received in the Echo Pin. */

   /*The Echo Pin will output the time in microseconds the sound wave traveled , distance = time * speed)
   *(For example, travel time about 588 microseconds. distance in cm = 588 * 0.034,
   *But the travel time you get from the Echo pin will be double that number because the sound wave needs to travel forward and bounce backward. 
   *So in order to get the distance we need to divide it by 2.)*/
   
  //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  /* Reads the echoPin, returns the sound wave travel time in microseconds
   * Using the pulseIn()function you have to read the travel time and put that value into the variable “duration”. 
   * This function has 2 parameters, the first one is the name of the echo pin 
   * and for the second one you can write either HIGH or LOW. 
   * In this case, we need this set to it HIGH, as the HC-SR04 sensors sets the Echo pin to High after sending the 8 cycle ultrasonic burst from the transmitter. 
   * This actually starts the timing and once we receive the reflected sound wave the Echo pin will go to Low which stops the timing. 
   * HIGH means that the pulseIn() function will wait for the pin to go HIGH caused by the bounced sound wave and it will start timing, 
   * then it will wait for the pin to go LOW when the sound wave will end which will stop the timing. 
   * At the end the function will return the length of the pulse(travel time) in microseconds. 
   * For getting the distance we will multiply the duration by 0.034 and divide it by 2 as we explained this equation previously. */
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}
