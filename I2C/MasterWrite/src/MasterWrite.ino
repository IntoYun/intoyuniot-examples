/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Wire Master Writer

 Demonstrates use of the Wire library
 Writes data to an I2C/TWI slave device
 Refer to the "Wire Slave Receiver" example for use with this

 */


void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
    Wire.beginTransmission(4);  // transmit to device #4
    Wire.write("x is ");        // sends five bytes
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    x++;
    delay(500);
}
