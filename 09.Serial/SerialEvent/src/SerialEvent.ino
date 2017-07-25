/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.
 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

/*
   SerialEvent occurs whenever a new data comes in the
   hardware serial RX.  This routine is run between each
   time loop() runs, so using delay inside loop can delay
   response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
    while (Serial.available())
    {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n')
        {
            stringComplete = true;
        }
    }
}


void setup()
{
    // initialize serial:
    Serial.begin(115200);
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
}

void loop()
{
    serialEvent();
    // print the string when a newline arrives:
    if (stringComplete)
    {
        Serial.println(inputString);
        // clear the string:
        inputString = "";
        stringComplete = false;
    }
}


