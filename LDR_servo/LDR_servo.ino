#include<Servo.h> //include the servo library

Servo servo1; //create a servo object called servo1
int pos = 0;    // variable to store the servo position
int motorspeed = 1;
void setup() {
  Serial.begin(9600);
  servo1.attach(9); // set the servo pin, pin 9, as an servo output pin
  pinMode(A0,INPUT);
  pinMode(9,OUTPUT);
}

void loop (){
  //read the light value from photresistor
  int lightValue =  analogRead(A0);
  Serial.println("Light Intensity is");
  Serial.println(lightValue);

  lightValue = map(lightValue,0,1023,0,180);
  Serial.println("anlge is");
  Serial.println(lightValue);
  
  servo1.write(lightValue);

  delay(200);
}
