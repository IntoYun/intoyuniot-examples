/*
 ************************************************************************
 * @author  :  IntoRobot Team
 * @version :  V1.0.0
 * @date    :  03-30-15
 ************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

 Blink without Delay

 Turns on and off a light emitting diode(LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.
 */

int pin = 7; //请根据您选择的板子修改引脚号
unsigned long duration;

void setup()
{
    pinMode(pin, INPUT);
    Serial.begin(115200);
}

void loop()
{
    duration = pulseIn(pin, HIGH);
    Serial.printf("duration = %d", duration);
    delay(2000);
}
