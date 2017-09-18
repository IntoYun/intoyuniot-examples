/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 EEPROM Write

 Stores values read from analog input 0 into the EEPROM.
 These values will stay in the EEPROM when the board is
 turned off and may be retrieved later by another sketch.
 */


// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;

void setup()
{
    pinMode(A0,AN_INPUT);
}

void loop()
{
    // need to divide by 4 because analog inputs range from
    // 0 to 1023 and each byte of the EEPROM can only hold a
    // value from 0 to 255.
    int val = analogRead(A0) / 4;

    // write the value to the appropriate byte of the EEPROM.
    // these values will remain there when the board is
    // turned off.
    EEPROM.write(addr, val);

    // advance to the next address.  there are 100 bytes in
    // the EEPROM, so go back to 0 when we hit 100.
    addr = addr + 1;

    if (addr == 100)
    {
        addr = 0;
    }

    delay(100);
}
