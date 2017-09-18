/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Conditionals - If statement

 This example demonstrates the use of if() statements.
 It reads the state of a potentiometer (an analog input) and turns on an LED
 only if the LED goes above a certain threshold level. It prints the analog value
 regardless of the level.

 The circuit:
 * potentiometer connected to analog pin 0.
 Center pin of the potentiometer goes to the analog pin.
 side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 13 to ground

 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.
 */

// These constants won't change:
const int analogPin = A0;    // pin that the sensor is attached to
const int ledPin = D7;       // pin that the LED is attached to
const int threshold = 400;   // an arbitrary threshold level that's in the range of the analog input

void setup()
{
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize serial communications:
    Serial.begin(115200);
    pinMode(analogPin,AN_INPUT);
}

void loop()
{
    // read the value of the potentiometer:
    int analogValue = analogRead(analogPin);

    // if the analog value is high enough, turn on the LED:
    if (analogValue > threshold)
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }

    // print the analog value:
    Serial.println(analogValue);
    delay(1);        // delay in between reads for stability
}

