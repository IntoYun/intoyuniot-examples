/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  String substring()

 Examples of how to use substring in a String
.
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
  Serial.println("\n\nString  substring():");
  Serial.println();
}

void loop() 
{
  // Set up a String:
  String stringOne = "Content-Type: text/html";
  Serial.println(stringOne);

  // substring(index) looks for the substring from the index position to the end:
  if (stringOne.substring(19) == "html") 
  {
    Serial.println("It's an html file");
  }
  // you can also look for a substring in the middle of a string:
  if (stringOne.substring(14, 18) == "text") 
  {
    Serial.println("It's a text-based file");
  }

  // do nothing while true:
  while (true);
}
