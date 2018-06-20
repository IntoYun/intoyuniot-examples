/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example
 analogWrite()

 This sketch fades LEDs up and down one at a time on analog pins 0 through 8.

 The circuit:
 * LEDs attached from analog pins 0 through 8 to ground.

 */

// These constants won't change.  They're used to give names
// to the pins used:
//不同板子请修改其引脚
const int dac8bitPin = A4;
const int dac12bitPin = A5;
int output8bit = 0;
int output12bit = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(dac8bitPin, OUTPUT);
    pinMode(dac12bitPin, OUTPUT);

    analogWriteResolution(dac8bitPin, 8);
    analogWriteResolution(dac12bitPin, 12);
}

void loop()
{
    Serial.printf("8bit_pin_A4_value = %d, 12bit_pin_A5_value = %d\r\n", output8bit, output12bit);

    analogWrite(dac8bitPin, output8bit);
    output8bit += 50;
    if(output8bit > 255) {
        output8bit = 0;
    }

    analogWrite(dac12bitPin, output12bit);
    output12bit += 500;
    if(output12bit > 4095) {
        output12bit = 0;
    }

    delay(3000);
}

