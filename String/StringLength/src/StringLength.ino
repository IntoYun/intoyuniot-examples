/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 String length()

 Examples of how to use length() in a String.
 Open the Serial Monitor and start sending characters to see the results.

 */

String txtMsg = "";                         // a string for incoming text
int lastStringLength = txtMsg.length();     // previous length of the String

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect.
    }

    // send an intro:
    Serial.println("\n\nString  length():");
    Serial.println();
}

void loop()
{
    // add any incoming characters to the String:
    while (Serial.available() > 0)
    {
        char inChar = Serial.read();
        txtMsg += inChar;
    }

    // print the message and a notice if it's changed:
    if (txtMsg.length() != lastStringLength)
    {
        Serial.println(txtMsg);
        Serial.println(txtMsg.length());
        // if the String's longer than 140 characters, complain:
        if (txtMsg.length() < 140)
        {
            Serial.println("That's a perfectly acceptable text message");
        }
        else
        {
            Serial.println("That's too long for a text message.");
        }
        // note the length for next time through the loop:
        lastStringLength = txtMsg.length();
    }
}
