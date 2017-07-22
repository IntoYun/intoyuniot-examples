/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  For Loop Iteration

 Demonstrates the use of a for() loop.
 Lights multiple LEDs in sequence, then in reverse.

 The circuit:
 * LEDs from pins D0 through D4 to ground
*/

int timer = 100;           // The higher the number, the slower the timing.

void setup() 
{
    // use a for loop to initialize each pin as an output:
    for (int thisPin = D0; thisPin <= D4; thisPin++) 
    {
        pinMode(thisPin, OUTPUT);
    }
}

void loop() 
{
    // loop from the lowest pin to the highest:
    for (int thisPin = D0; thisPin <= D4; thisPin++) 
    {
        // turn the pin on:
        digitalWrite(thisPin, HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(thisPin, LOW);
    }

    // loop from the highest pin to the lowest:
    for (int thisPin = D4; thisPin >= D0; thisPin--) 
    {
        // turn the pin on:
        digitalWrite(thisPin, HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(thisPin, LOW);
    }
}
