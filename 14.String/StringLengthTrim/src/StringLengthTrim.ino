/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  String length() and trim()

 Examples of how to use length() and trim() in a String

*/

void setup() 
{
  // Open Serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. 
  }

  // send an intro:
  Serial.println("\n\nString  length() and trim():");
  Serial.println();
}

void loop() 
{
  // here's a String with empty spaces at the end (called white space):
  String stringOne = "Hello!       ";
  Serial.print(stringOne);
  Serial.print("<--- end of string. Length: ");
  Serial.println(stringOne.length());

  // trim the white space off the string:
  stringOne.trim();
  Serial.print(stringOne);
  Serial.print("<--- end of trimmed string. Length: ");
  Serial.println(stringOne.length());

  // do nothing while true:
  while (true);
}
