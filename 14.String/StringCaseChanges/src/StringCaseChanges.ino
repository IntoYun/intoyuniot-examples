/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example


 String Case changes

 Examples of how to change the case of a string

 */


void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    // send an intro:
    Serial.println("\n\nString  case changes:");
    Serial.println();
}

void loop()
{
    // toUpperCase() changes all letters to upper case:
    String stringOne = "<html><head><body>";
    Serial.println(stringOne);
    stringOne.toUpperCase();
    Serial.println(stringOne);

    // toLowerCase() changes all letters to lower case:
    String stringTwo = "</BODY></HTML>";
    Serial.println(stringTwo);
    stringTwo.toLowerCase();
    Serial.println(stringTwo);


    // do nothing while true:
    while (true);
}

