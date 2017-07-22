/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  Wire Master Reader

 Demonstrates use of the Wire library
 Reads data from an I2C/TWI slave device
 Refer to the "Wire Slave Sender" example for use with this

*/

void setup()
{
	Wire.begin();        // join i2c bus (address optional for master)
	Serial.begin(115200);  // start serial for output
}

void loop()
{
	Wire.requestFrom(2, 6);    // request 6 bytes from slave device #2

	while (Wire.available())   // slave may send less than requested
	{
		char c = Wire.read(); // receive a byte as character
		Serial.print(c);         // print the character
	}

	delay(500);
}
