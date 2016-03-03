// Sketch to run upper flood lights and pond lights
// Gary Ashkin

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN_FLOOD            8
#define PIN_POND            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS_FLOOD       4
#define NUMPIXELS_POND       50

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels_flood = Adafruit_NeoPixel(NUMPIXELS_FLOOD, PIN_FLOOD, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_pond = Adafruit_NeoPixel(NUMPIXELS_POND, PIN_POND, NEO_GRB + NEO_KHZ800);

int delayval = 5; // delay for half a second

void setup() {

  pixels_flood.begin(); // This initializes the NeoPixel library.
  pixels_pond.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS_FLOOD;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_flood.setPixelColor(i, pixels_flood.Color(0,115,154)); // Moderately bright green color.

    pixels_flood.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

    for(int i=0;i<NUMPIXELS_POND;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_pond.setPixelColor(i, pixels_pond.Color(38,2,14)); // Moderately bright green color.

    pixels_pond.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
