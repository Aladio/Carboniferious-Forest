#include <Servo.h>

Servo servo1; // make instance of Servo

int i = 20;  // how many times wing will flap.

const int piezo = A0; // name piezo input
int knockVal;  // variable for value of the knock

const int quietKnock = 300;
const int loudKnock = 600;
const int howManyKocks = 3;

int numberOfKnocks = 0;

void setup() {
	Serial.begin(9600); // initalize the serial monitor for debugging.

	servo1.attach(11);  // attach servo1 to pin 11 on arduino.
}

void loop() {
	knockVal = analogRead(piezo);  // read the piezo sensor

	if (knockVal > quietKnock && numberOfKnocks >= howManyKocks) {
		flapWing(i);
	}
	if (numberOfKnocks < howManyKocks && knockVal > quietKnock) {
		if (checkForKnock(knockVal) == true) {
			numberOfKnocks++;
		}
		Serial.print(howManyKocks - numberOfKnocks);
		Serial.println(" more knocks to go");
	}
}

void flapWing(int i) {
	Serial.println("Flap!");
	servo1.write(90); // move wing to starting point
	delay(50);
	for (int count = 0; count < i; ++count) { // loop i flap times.
		servo1.write(102);
		delay(100);

		servo1.write(90);
		delay(100);
	}
}

boolean checkForKnock(int value) {
	if (value > quietKnock && value < loudKnock) {
		Serial.print("Valid knock value of ");
		Serial.println(value);
		return true;
	}
	else {
		Serial.print("Bad knock value of ");
		Serial.println(value);
		return false;
	}
}
