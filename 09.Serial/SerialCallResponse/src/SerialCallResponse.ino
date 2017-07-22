/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  Serial Call and Response

 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and
 sends three sensor values whenever it gets a byte in.

   The circuit:
 * potentiometers attached to analog inputs 0 and 1
 * pushbutton attached to digital I/O 2
*/

int firstSensor = 0;    // first analog sensor
int secondSensor = 0;   // second analog sensor
int thirdSensor = 0;    // digital sensor
int inByte = 0;         // incoming serial byte


void establishContact() 
{
  while (Serial.available() <= 0) 
  {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}


void setup()
{
    // start serial port at 115200 bps:
    Serial.begin(115200);
    while (!Serial) 
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    pinMode(D7, INPUT);   // digital sensor is on digital pin 2
    establishContact();  // send a byte to establish contact until receiver responds
    pinMode(A0,AN_INPUT);
	pinMode(A1,AN_INPUT);
}

void loop()
{
    // if we get a valid byte, read analog ins:
    if (Serial.available() > 0) 
    {
        // get incoming byte:
        inByte = Serial.read();
        // read first analog input, divide by 4 to make the range 0-255:
        firstSensor = analogRead(A0) / 4;
        // delay 10ms to let the ADC recover:
        delay(10);
        // read second analog input, divide by 4 to make the range 0-255:
        secondSensor = analogRead(A1) / 4;
        // read  switch, map it to 0 or 255L
        thirdSensor = map(digitalRead(D7), 0, 1, 0, 255);
        // send sensor values:
        Serial.write(firstSensor);
        Serial.write(secondSensor);
        Serial.write(thirdSensor);
    }
}


