/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  Dimmer

 Demonstrates the sending data from the computer to the IntoRobot board,
 in this case to control the brightness of an LED.  The data is sent
 in individual bytes, each of which ranges from 0 to 255.  IntoRobot
 reads these bytes and uses them to set the brightness of the LED.

 The circuit:
 LED attached from digital pin D7 to ground.
 Serial connection to Processing, Max/MSP, or another serial application
*/

const int ledPin = D7;  // the pin that the LED is attached to

void setup()
{
    // initialize the serial communication:
    Serial.begin(115200);
    // initialize the ledPin as an output:
    pinMode(ledPin, OUTPUT);
}

void loop() 
{
    byte brightness;

    // check if data has been sent from the computer:
    if (Serial.available()) 
    {
        // read the most recent byte (which will be from 0 to 255):
        brightness = Serial.read();
        // set the brightness of the LED:
        analogWrite(ledPin, brightness);
    }
}
