/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example

  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

*/
#include "pitches.h"

//不同板子请修改其引脚
// notes in the melody:
int melody[] =
{
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] =
{
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup()
{
    // iterate over the notes of the melody:
    pinMode(D0,OUTPUT);
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(D0, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(D0);
    }
}

void loop()
{
    // no need to repeat the melody.
}
