/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
This application example code is in the public domain.
This example is modified from arduino example


Fading

This example shows how to fade an LED using the analogWrite() function.

The circuit:
* LED attached from analog pin 0 to ground.

*/



int ledPin = A0;    // LED connected to analog pin 0

void setup() 
{
  pinMode(ledPin,OUTPUT);
}

void loop() 
{
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) 
  {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) 
  {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

