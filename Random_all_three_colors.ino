// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// Revised by Duane Benson, 2018

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            9

#define ambientSense A3         // Analog input used to read the amient light value

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 5; // delay for half a second
     // variables for light reading
int sensorValue = 0;             // variable to store the value coming from the sensor
int stripBright = 0;             // variablw to store adjusted brightness value
uint8_t  ambient = 32;           // Default brightness level. Will be adjusted by the ambient light sensor
int rMin = 1;
int rMax = 125;


void setup() {
  autoBrightness();              // Check ambient light sensor and adjust the brightness value
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){
    autoBrightness();
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(random(rMin, rMax),random(rMin, rMax),random(rMin, rMax))); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

}

//*********************************************************************
  void autoBrightness() {
      sensorValue = analogRead(ambientSense);
      stripBright = map(sensorValue, 0, 1023, 0, 127);
      Serial.println(sensorValue);
      stripBright = stripBright + ambient;
      pixels.setBrightness(stripBright); // set brightness
  }

