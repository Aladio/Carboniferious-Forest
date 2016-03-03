/*
//////////////////////////////////////////////////
//making sense of the Parallax PIR sensor's output
//////////////////////////////////////////////////

Switches lighting according to the state of the sensors output pin.
Determines the beginning and end of continuous motion sequences.

@author: Kristian Gohlke / krigoo (_) gmail (_) com / http://krx.at
@date:   3. September 2006

kr1 (cleft) 2006
released under a creative commons "Attribution-NonCommercial-ShareAlike 2.0" license
http://creativecommons.org/licenses/by-nc-sa/2.0/de/


The Parallax PIR Sensor is an easy to use digital infrared motion sensor module.
(http://www.parallax.com/detail.asp?product_id=555-28027)

 The sensor's output pin goes to HIGH if motion is present.
 However, even if motion is present it goes to LOW from time to time,
 which might give the impression no motion is present.
 This program deals with this issue by ignoring LOW-phases shorter than a given time,
 assuming continuous motion is present during these phases.
*/

// Work this in
#include "cie1931.h"

//#include <TimerOne.h>
 /////////////////////////////
 // For Motion Sensor
 //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
 int calibrationTime = 30;

 //the time when the sensor outputs a low impulse
 unsigned long lowIn;

 //the amount of milliseconds the sensor has to be low
 //before we assume all motion has stopped
 unsigned long pause = 120000;

 boolean lockLow = true;
 boolean takeLowTime;

 int pirPin = 4;    //the digital pin connected to the PIR sensor's output

 /////////////////////////////
 // For Led Strips

#define GREENPIN 5
#define REDPIN 6
#define BLUEPIN 7
#define FADESPEED 300              // make this higher to slow down

 // start color
 // in this case blacklight violet
 int g = 0;
 int r = 50;
 int b = 180;


 /*
   Calculate numbers for the loop that will bring up and dim the lights
   --------------------------------------------------------------------
   The limiting number is BLUE  255-180=75     blueStep=1
   RED (255-50)/75=2.7 (round up to a whole step)  redStep=3
   GREEN 255/75=3.4  (round up to a whole step)  greenStep=4
   120LEDs (128-5)/75=1.6
 */

 int greenStep = 4;
 int redStep = 3;
 int blueStep = 1;

 boolean lightsState;  // Keep track if lights are on or off

 //////////////////////////////
 // For Flood Lights

#define TRPIN 8
#define TCPIN 9
#define TLPIN 10
#define BRPIN 11
#define BCPIN 12
#define BLPIN 13



 /////////////////////////////
 void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  lights_down();    // Set lights down
  lightsState = false;
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);

  // Set up the pins
  pinMode(pirPin, INPUT);

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  pinMode(TRPIN, OUTPUT);
  pinMode(TCPIN, OUTPUT);
  pinMode(TLPIN, OUTPUT);
  pinMode(BRPIN, OUTPUT);
  pinMode(BCPIN, OUTPUT);
  pinMode(BLPIN, OUTPUT);

}

/////////////////////////////
// Main loop
void loop()
{
  if (digitalRead(pirPin) == HIGH) {
    if (lockLow) {
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis() / 1000);
      Serial.println(" sec");
    }

    lights_up();
    takeLowTime = true;

  }

  if (digitalRead(pirPin) == LOW) {

    if (takeLowTime) {
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause,
    //we assume that no more motion is going to happen
    if (!lockLow && millis() - lowIn > pause) {
      //makes sure this block of code is only executed again after
      //a new motion sequence has been detected
      lockLow = true;
      Serial.print("motion ended at ");      //output
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      delay(50);
      lights_down();
      //software_Reset();
    }
  }

//  Work this in
//    byte i = 0;
//    while (1) {
//        analogWrite(2, cie[i]);
//        delay(10);
//        i++;
//    }
//
//

}


//////////////////////////
//Functions
//------ Reset ---------------------------------------------------------------------
void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}
// lights_up()
// Based on calcuations above, loop though color steps to fade led strip from black light blue to white
// Each step of the loop also increases 120V LED bulbs by 1.
void lights_up()
{

  if (lightsState == false) {
    for (int i = 0; i <= 75; i++) {
      g = g + greenStep;  // Add Color Steps to go from blue to white
      r = r + redStep;
      b = b + blueStep;
      if (g <= 255) analogWrite(GREENPIN, g);   // Dont let the color numbers get above 255 then write color.
      if (r <= 255) analogWrite(REDPIN, r);
      if (b <= 255) analogWrite(BLUEPIN, b);
      analogWrite(TRPIN, i);  // Bring up the flood lights
      analogWrite(TCPIN, i);
      analogWrite(TLPIN, i);
      analogWrite(BRPIN, i);
      analogWrite(BCPIN, i);
      analogWrite(BLPIN, i);

      delay(FADESPEED);
    }
    analogWrite(GREENPIN, 255);    // Make sure we are at 255 for all colors in LED strip
    analogWrite(REDPIN, 255);
    analogWrite(BLUEPIN, 255);
    for (int j = 76; j >= 255; j++) {  // Do the last 180 steps to get the floods to full brightness
      analogWrite(TRPIN, j);
      analogWrite(TCPIN, j);
      analogWrite(TLPIN, j);
      analogWrite(BRPIN, j);
      analogWrite(BCPIN, j);
      analogWrite(BLPIN, j);
      delay(FADESPEED);
    }
    lightsState = true;
  }
}

// lights_down()
// reset the lights to initial state.
void lights_down() {
  delay(500);
  g = 0;      //  Set Led Strip back to black light blue
  r = 50;
  b = 180;
  analogWrite(GREENPIN, g);
  analogWrite(REDPIN, r);
  analogWrite(BLUEPIN, b);

  analogWrite(TRPIN, 0);  // Turn of the flood lights
  analogWrite(TCPIN, 0);
  analogWrite(TLPIN, 0);
  analogWrite(BRPIN, 0);
  analogWrite(BCPIN, 0);
  analogWrite(BLPIN, 0);
  lightsState = false;
}

