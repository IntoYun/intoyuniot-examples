/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

   Wire Slave Sender

 Demonstrates use of the Wire library
 Sends data as an I2C/TWI slave device
 Refer to the "Wire Master Reader" example for use with this

*/

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
	Wire.write("hello "); // respond with message of 6 bytes
	// as expected by master
}

void setup()
{
	Wire.begin(2);                // join i2c bus with address #2
	Wire.onRequest(requestEvent); // register event
}

void loop()
{
	delay(100);
}