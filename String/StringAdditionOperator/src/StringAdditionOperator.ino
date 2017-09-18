/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Adding Strings together

 Examples of how to add strings together
 You can also add several different data types to string, as shown here:

 */

// declare three strings:
String stringOne, stringTwo, stringThree;

void setup()
{
    // initialize serialUSB and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect.
    }

    stringOne = String("You added ");
    stringTwo = String("this string");
    stringThree = String ();
    // send an intro:
    Serial.println("\n\nAdding strings together (concatenation):\r\n");
}

void loop()
{
    // adding a constant integer to a string:
    stringThree =  stringOne + (uint8_t)123;
    Serial.println(stringThree);    // prints "You added 123"

    // adding a constant long interger to a string:
    stringThree = stringOne + "123456789";
    Serial.println(stringThree);    // prints " You added 123456789"

    // adding a constant character to a string:
    stringThree =  stringOne + 'A';
    Serial.println(stringThree);    // prints "You added A"

    // adding a constant string to a string:
    stringThree =  stringOne +  "abc";
    Serial.println(stringThree);    // prints "You added abc"

    stringThree = stringOne + stringTwo;
    Serial.println(stringThree);    // prints "You added this string"

    // adding a variable integer to a string:
    int sensorValue = analogRead(A0);
    stringOne = "Sensor value: ";
    stringThree = stringOne  + String(sensorValue);
    Serial.println(stringThree);    // prints "Sensor Value: 401" or whatever value analogRead(A0) has

    // adding a variable long integer to a string:
    long currentTime = millis();
    stringOne = "millis() value: ";
    stringThree = stringOne + String(currentTime);
    Serial.println(stringThree);    // prints "The millis: 345345" or whatever value currentTime has

    // do nothing while true:
    while (true);
}
