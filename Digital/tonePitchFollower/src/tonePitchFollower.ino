/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
  This application example code is in the public domain.
  This example is modified from arduino example

  Pitch follower

 Plays a pitch that changes based on a changing analog input

 circuit:
 * 8-ohm speaker on digital pin 9
 * photoresistor on analog 0 to 5V
 * 4.7K resistor on analog 0 to ground

*/


void setup()
{
    // initialize serial communications (for debugging only):
    Serial.begin(115200);
    pinMode(A0,AN_INPUT);
    pinMode(D0,OUTPUT);
}

void loop()
{
    // read the sensor:
    int sensorReading = analogRead(A0);
    // print the sensor reading so you know its range
    Serial.println(sensorReading);
    // map the analog input range (in this case, 400 - 1000 from the photoresistor)
    // to the output pitch range (120 - 1500Hz)
    // change the minimum and maximum input numbers below
    // depending on the range your sensor's giving:
    int thisPitch = map(sensorReading, 400, 1000, 120, 1500);

    // play the pitch:
    tone(D0, thisPitch, 10);
    delay(1);        // delay in between reads for stability
}
