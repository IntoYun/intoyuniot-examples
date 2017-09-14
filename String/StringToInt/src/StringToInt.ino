/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example


 String to Integer conversion

 Reads a serial input string until it sees a newline, then converts
 the string to a number if the characters are digits.

 The circuit:
 No external components needed.

 */

String inString = "";    // string to hold input

void setup()
{
    // Open Serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect.
    }

    // send an intro:
    Serial.println("\n\nString toInt():");
    Serial.println();
}

void loop()
{
    // Read serial input:
    while (Serial.available() > 0)
    {
        int inChar = Serial.read();
        if (isDigit(inChar))
        {
            // convert the incoming byte to a char
            // and add it to the string:
            inString += (char)inChar;
        }
        // if you get a newline, print the string,
        // then the string's value:
        if (inChar == '\n')
        {
            Serial.print("Value:");
            Serial.println(inString.toInt());
            Serial.print("String: ");
            Serial.println(inString);
            // clear the string for new input:
            inString = "";
        }
    }
}

