/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 EEPROM Read

 Reads the value of each byte of the EEPROM and prints it
 to the computer.

 */

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
    // initialize serialUSB and wait for port to open:
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serialUSB port to connect.
    }
}

void loop()
{
    // read a byte from the current address of the EEPROM
    value = EEPROM.read(address);

    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();

    // advance to the next address of the EEPROM
    address = address + 1;

    // there are only 100 bytes of EEPROM, from 0 to 99, so if we're
    // on address 100, wrap around to address 0
    if (address == 100)
    {
        address = 0;
    }

    delay(500);
}
