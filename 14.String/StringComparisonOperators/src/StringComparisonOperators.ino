/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  03-30-15
************************************************************************
 This application example code is in the public domain.
 This example is modified from arduino example


  Comparing Strings

 Examples of how to compare strings using the comparison operators
*/

String stringOne, stringTwo;

void setup()
{
	// Open serial communications and wait for port to open:
	Serial.begin(115200);
	while (!Serial)
	{
		; // wait for serial port to connect. 
	}


	stringOne = String("this");
	stringTwo = String("that");
	// send an intro:
	Serial.println("\n\nComparing Strings:");
	Serial.println();

}

void loop()
{
	// two strings equal:
	if (stringOne == "this")
	{
		Serial.println("StringOne == \"this\"");
	}
	// two strings not equal:
	if (stringOne != stringTwo)
	{
		Serial.println(stringOne + " =! " + stringTwo);
	}

	// two strings not equal (case sensitivity matters):
	stringOne = "This";
	stringTwo = "this";
	if (stringOne != stringTwo)
	{
		Serial.println(stringOne + " =! " + stringTwo);
	}
	// you can also use equals() to see if two strings are the same:
	if (stringOne.equals(stringTwo))
	{
		Serial.println(stringOne + " equals " + stringTwo);
	}
	else
	{
		Serial.println(stringOne + " does not equal " + stringTwo);
	}

	// or perhaps you want to ignore case:
	if (stringOne.equalsIgnoreCase(stringTwo))
	{
		Serial.println(stringOne + " equals (ignoring case) " + stringTwo);
	}
	else
	{
		Serial.println(stringOne + " does not equal (ignoring case) " + stringTwo);
	}

	// a numeric string compared to the number it represents:
	stringOne = "1";
	int numberOne = 1;
	if (stringOne.toInt() == numberOne)
	{
		Serial.println(stringOne + " = " + numberOne);
	}



	// two numeric strings compared:
	stringOne = "2";
	stringTwo = "1";
	if (stringOne >= stringTwo)
	{
		Serial.println(stringOne + " >= " + stringTwo);
	}

	// comparison operators can be used to compare strings for alphabetic sorting too:
	stringOne = String("Brown");
	if (stringOne < String("Charles"))
	{
		Serial.println(stringOne + " < Charles");
	}

	if (stringOne > String("Adams"))
	{
		Serial.println(stringOne + " > Adams");
	}

	if (stringOne <= String("Browne"))
	{
		Serial.println(stringOne + " <= Browne");
	}


	if (stringOne >= String("Brow"))
	{
		Serial.println(stringOne + " >= Brow");
	}

	// the compareTo() operator also allows you to compare strings
	// it evaluates on the first character that's different.
	// if the first character of the string you're comparing to
	// comes first in alphanumeric order, then compareTo() is greater than 0:
	stringOne = "Cucumber";
	stringTwo = "Cucuracha";
	if (stringOne.compareTo(stringTwo) < 0 )
	{
		Serial.println(stringOne + " comes before " + stringTwo);
	}
	else
	{
		Serial.println(stringOne + " comes after " + stringTwo);
	}

	delay(10000);  // because the next part is a loop:

	// compareTo() is handy when you've got strings with numbers in them too:

	while (true)
	{
		stringOne = "Sensor: ";
		stringTwo = "Sensor: ";

		stringOne += analogRead(A0);
		stringTwo += analogRead(A1);

		if (stringOne.compareTo(stringTwo) < 0 )
		{
			Serial.println(stringOne + " comes before " + stringTwo);
		}
		else
		{
			Serial.println(stringOne + " comes after " + stringTwo);

		}
	}
}
