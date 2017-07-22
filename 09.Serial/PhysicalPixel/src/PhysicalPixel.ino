/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  Physical Pixel

 An example of using the IntoRobot board to receive data from the
 computer.  In this case, the IntoRobot boards turns on an LED when
 it receives the character 'H', and turns off the LED when it
 receives the character 'L'.

 The data can be sent from the IntoRobot serial monitor, or another
 program like Processing (see code below), Flash (via a serial-net
 proxy), PD, or Max/MSP.

 The circuit:
 * LED connected from digital pin D7 to ground
*/

const int ledPin = D7; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

void setup() 
{
    // initialize serial communication:
    Serial.begin(115200);
	while(!Serial);
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
}

void loop() 
{
    // see if there's incoming serial data:
    if (Serial.available() > 0) 
    {
        // read the oldest byte in the serial buffer:
        incomingByte = Serial.read();
        // if it's a capital H (ASCII 72), turn on the LED:
        if (incomingByte == 'H') 
        {
            digitalWrite(ledPin, HIGH);
        }
        // if it's an L (ASCII 76) turn off the LED:
        if (incomingByte == 'L') 
        {
            digitalWrite(ledPin, LOW);
        }
    }
}


