/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  I2C Digital Potentiometer

 Demonstrates use of the Wire library
 Controls AD5171 digital potentiometer via I2C/TWI

*/

void setup()
{
	Wire.begin(); // join i2c bus (address optional for master)
}

byte val = 0;

void loop()
{
	Wire.beginTransmission(44); // transmit to device #44 (0x2c)
	// device address is specified in datasheet
	Wire.write(byte(0x00));            // sends instruction byte
	Wire.write(val);             // sends potentiometer value byte
	Wire.endTransmission();     // stop transmitting

	val++;        // increment value
	if (val == 64) // if reached 64th position (max)
	{
		val = 0;    // start over from lowest value
	}
	delay(500);
}