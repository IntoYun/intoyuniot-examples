/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  Mega multple serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).


 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:
*/


void setup() 
{
    // initialize both serial ports:
    Serial.begin(115200);
    Serial.begin(115200);
}

void loop() 
{
    // read from port 1, send to port 0:
    if (Serial.available()) 
    {
        int inByte = Serial.read();
        Serial.write(inByte);
    }

    // read from port 0, send to port 1:
    if (Serial.available()) 
    {
        int inByte = Serial.read();
        Serial.write(inByte);
    }
}

