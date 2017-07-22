/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  This example reads three analog sensors (potentiometers are easiest)
 and sends their values serially. The Processing and Max/MSP programs at the bottom
 take those three values and use them to change the background color of the screen.

 The circuit:
 * potentiometers attached to analog inputs 0, 1, and 2
*/

const int redPin = A0;		// sensor to control red color
const int greenPin = A1;	// sensor to control green color
const int bluePin = A2;	  
  
void setup()
{
    Serial.begin(115200);
    pinMode(redPin,AN_INPUT);
    pinMode(greenPin,AN_INPUT);
    pinMode(bluePin,AN_INPUT);
}

void loop()
{
    Serial.print(analogRead(redPin));
    Serial.print(",");
    Serial.print(analogRead(greenPin));
    Serial.print(",");
    Serial.println(analogRead(bluePin));
}
