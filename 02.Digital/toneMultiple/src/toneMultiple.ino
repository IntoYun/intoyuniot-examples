/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  Multiple tone player

 Plays multiple tones on multiple pins in sequence

 circuit:
 * 3 8-ohm speaker on digital pins D6, D7, and D8

*/
//不同板子请修改引脚
void setup() 
{
	pinMode(D0,OUTPUT);
	pinMode(D1,OUTPUT);
	pinMode(D2,OUTPUT);
}

void loop() 
{
    // turn off tone function for digital pin 8:
    noTone(D2);
    // play a note on pin 6 for 200 ms:
    tone(D0, 440, 200);
    delay(200);

    // turn off tone function for digital pin 6:
    noTone(D0);
    // play a note on pin 7 for 500 ms:
    tone(D1, 494, 500);
    delay(500);

    // turn off tone function for digital pin 7:
    noTone(D1);
    // play a note on pin 8 for 500 ms:
    tone(D2, 523, 300);
    delay(300);
}
