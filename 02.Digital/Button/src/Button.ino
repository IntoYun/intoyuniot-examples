/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.

 The circuit:
 * buildin LED attached from pin D7 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most IntoRobot there is already an LED on the board
 attached to pin D7.
 
 This example code is in the public domain.
*/

// constants won't change. They're used here to
// set pin numbers:
//模组请修改引脚
const int buttonPin = D2;     // the number of the pushbutton pin
const int ledPin =  D7;      // the number of the  buildin LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() 
{
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}

void loop() 
{
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) 
    {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
    }
    else 
    {
        // turn LED off:
        digitalWrite(ledPin, LOW);
    }
}
