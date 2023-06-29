int res = 0; /* declaring the variable that will store the value of photoresistor*/
int sensor =A0;/* assigning Arduino pin for photoresistor*/
int led= 5;/* assigning Arduino pin for LED*/
void setup() {
    Serial.begin(9600); /*setting the baud rate for serial communication*/
    pinMode(5, OUTPUT); /* assigning mode to LED pin */
}

void loop() {
    // put your main code here, to run repeatedly:
    res = analogRead(sensor); /* getting the value of photoresistor*/

    Serial.println(res); /* displaying the photoresistor value on serial monitor */

    if(res > 50) { /* when the value of sensor is greater than 100 */
        Serial.println(" High intensity ");
        digitalWrite(5,LOW); /* keep the LED off*/
    }
    else { /* otherwise turn the light on */
        Serial.println(" Low Intensity ");
        digitalWrite(5,HIGH); /* turn the LED on*/
    }

 /*
    // to control LED brightness
    int brightness = potentiometerValue;
    analogWrite(led, brightness);
 */
    delay(1000);
}
