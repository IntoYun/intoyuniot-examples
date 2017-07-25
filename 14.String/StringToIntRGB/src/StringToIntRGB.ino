/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Serial RGB controller

 Reads a serial input string looking for three comma-separated
 integers with a newline at the end. Values should be between
 0 and 255. The sketch uses those values to set the color
 of an RGB LED attached to pins 9 - 11.

 The circuit:
 * Common-anode RGB LED cathodes attached to analog pins 0- 2
 * LED anode connected to pin D7

 To turn on any given channel, set the pin LOW.
 To turn off, set the pin HIGH. The higher the analogWrite level,
 the lower the brightness.

 */

String inString = "";    // string to hold input
int currentColor = 0;
int red, green, blue = 0;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect.
    }

    // send an intro:
    Serial.println("\n\nString toInt() RGB:");
    Serial.println();
    // set LED cathode pins as outputs:
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    // turn on pin 3 to power the LEDs:
    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);
}

void loop()
{
    int inChar;

    // Read serial input:
    if (Serial.available() > 0)
    {
        inChar = Serial.read();
    }

    if (isDigit(inChar))
    {
        // convert the incoming byte to a char
        // and add it to the string:
        inString += (char)inChar;
    }

    // if you get a comma, convert to a number,
    // set the appropriate color, and increment
    // the color counter:
    if (inChar == ',')
    {
        // do something different for each value of currentColor:
        switch (currentColor)
        {
            case 0:    // 0 = red
                red = inString.toInt();
                // clear the string for new input:
                inString = "";
                break;

            case 1:    // 1 = green:
                green = inString.toInt();
                // clear the string for new input:
                inString = "";
                break;
        }
        currentColor++;
    }
    // if you get a newline, you know you've got
    // the last color, i.e. blue:
    if (inChar == '\n')
    {
        blue = inString.toInt();

        // set the levels of the LED.
        // subtract value from 255 because a higher
        // analogWrite level means a dimmer LED, since
        // you're raising the level on the anode:
        analogWrite(D0,  255 - red);
        analogWrite(D1, 255 - green);
        analogWrite(D2, 255 - blue);

        // print the colors:
        Serial.printf("Red: %d",", Green: %d",", Blue: %d \r\n",red,green,blue);

        // clear the string for new input:
        inString = "";
        // reset the color counter:
        currentColor = 0;
    }

}
