/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
http://www.sparkfun.com/commerce/categories.php?c=80

The circuit:
analog 0: accelerometer self test
analog 1: z-axis
analog 2: y-axis
analog 3: x-axis
analog 4: ground
analog 5: vcc

 */


// these constants describe the pins. They won't change:
const int groundpin = D0;             // analog input pin 4 -- ground
const int powerpin = D1;              // analog input pin 5 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

void setup()
{
    // initialize the serial communications:
    Serial.begin(115200);

    // Provide ground and power by using the analog inputs as normal
    // digital pins.  This makes it possible to directly connect the
    // breakout board to the Arduino.  If you use the normal 5V and
    // GND pins on the Arduino, you can remove these lines.
    pinMode(groundpin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    pinMode(xpin,AN_INPUT);
    pinMode(ypin,AN_INPUT);
    pinMode(zpin,AN_INPUT);
    digitalWrite(groundpin, LOW);
    digitalWrite(powerpin, HIGH);

}

void loop()
{
    // print the sensor values:
    Serial.print(analogRead(xpin));
    // print a tab between values:
    Serial.print("\t");
    Serial.print(analogRead(ypin));
    // print a tab between values:
    Serial.print("\t");
    Serial.print(analogRead(zpin));
    Serial.println();
    // delay before next reading:
    delay(100);
}
