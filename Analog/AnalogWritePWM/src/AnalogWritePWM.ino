/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example
 analogWrite()

 This sketch fades LEDs up and down one at a time on analog pins 0 through 8.

 The circuit:
 * LEDs attached from analog pins 0 through 8 to ground.

 */

// These constants won't change.  They're used to give names
// to the pins used:
//不同板子请修改其引脚

const int lowestPin = D0;
const int highestPin = D1;


void setup()
{
    // set analog pins 0 through 8 as outputs:
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++)
    {
        pinMode(thisPin, OUTPUT);
    }
}

void loop()
{
    // iterate over the pins:
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++)
    {
        // fade the LED on thisPin from off to brightest:
        for (int brightness = 0; brightness < 255; brightness++)
        {
            analogWrite(thisPin, brightness);
            delay(2);
        }
        // fade the LED on thisPin from brithstest to off:
        for (int brightness = 255; brightness >= 0; brightness--)
        {
            analogWrite(thisPin, brightness);
            delay(2);
        }
        // pause between LEDs:
        delay(100);
    }
}

