/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Memsic2125

 Read the Memsic 2125 two-axis accelerometer.  Converts the
 pulses output by the 2125 into milli-g's (1/1000 of earth's
 gravity) and prints them over the serial connection to the
 computer.

 The circuit:
 * X output of accelerometer to digital pin 2
 * Y output of accelerometer to digital pin 3
 * +V of accelerometer to +5V
 * GND of accelerometer to ground
 */


// these constants won't change:
const int xPin = D0;		// X output of the accelerometer
const int yPin = D1;		// Y output of the accelerometer

void setup()
{
    // initialize serial communications:
    Serial.begin(115200);
    // initialize the pins connected to the accelerometer
    // as inputs:
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

void loop()
{
    // variables to read the pulse widths:
    int pulseX, pulseY;
    // variables to contain the resulting accelerations
    int accelerationX, accelerationY;

    // read pulse from x- and y-axes:
    pulseX = pulseIn(xPin, HIGH);
    pulseY = pulseIn(yPin, HIGH);

    // convert the pulse width into acceleration
    // accelerationX and accelerationY are in milli-g's:
    // earth's gravity is 1000 milli-g's, or 1g.
    accelerationX = ((pulseX / 10) - 500) * 8;
    accelerationY = ((pulseY / 10) - 500) * 8;

    // print the acceleration
    Serial.print(accelerationX);
    // print a tab character:
    Serial.print("\t");
    Serial.print(accelerationY);
    Serial.println();

    delay(100);
}
