/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Input Pullup Serial

 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a
 digital input on pin 2 and prints the results to the serial monitor.

 The circuit:
 * Momentary switch attached from pin 2 to ground
 * Built-in LED on pin 13

 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
 20K-ohm resistor is pulled to 5V. This configuration causes the input to
 read HIGH when the switch is open, and LOW when it is closed.
*/

void setup() 
{
    //start serial connection
    Serial.begin(115200);
    //configure pin2 as an input and enable the internal pull-up resistor
    pinMode(D2, INPUT_PULLUP);
    pinMode(D7, OUTPUT);
}

void loop() 
{
    //read the pushbutton value into a variable
    int sensorVal = digitalRead(D2);
    //print out the value of the pushbutton
    Serial.println(sensorVal);

    // Keep in mind the pullup means the pushbutton's
    // logic is inverted. It goes HIGH when it's open,
    // and LOW when it's pressed. Turn on pin 13 when the
    // button's pressed, and off when it's not:
    if (sensorVal == HIGH) 
    {
        digitalWrite(D7, LOW);
    }
    else 
    {
        digitalWrite(D7, HIGH);
    }
}
