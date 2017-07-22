/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  Graph

 A simple example of communication from the IntoRobot board to the computer:
 the value of analog input 0 is sent out the serial port.  We call this "serial"
 communication because the connection appears to both the IntoRobot and the
 computer as a serial port, even though it may actually use
 a USB cable. Bytes are sent one after another (serially) from the IntoRobot
 to the computer.

 You can use the IntoRobot serial monitor to view the sent data, or it can
 be read by Processing, PD, Max/MSP, or any other program capable of reading
 data from a serial port.  The Processing code below graphs the data received
 so you can see the value of the analog input changing over time.

 The circuit:
 Any analog input sensor is attached to analog in pin A0.

 This example code is in the public domain.
 */

void setup() 
{
    // initialize the serial communication:
    Serial.begin(115200);
    pinMode(A0,AN_INPUT);
}

void loop() 
{
    // send the value of analog input 0:
    Serial.println(analogRead(A0));
    // wait a bit for the analog-to-digital converter
    // to stabilize after the last reading:
    delay(200);
}
