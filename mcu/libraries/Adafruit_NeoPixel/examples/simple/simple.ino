// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
//  pixels.setBrightness(50);
}

int mod(int x, int m) {
    return (x%m + m)%m;
}

void loop() {
  trailing('b');
}

void trailing(char color) {
  for(int i=0;i<NUMPIXELS;i++){
    for( int j = 0; j < 8; j++ ){
      int pixel = mod(i-j, NUMPIXELS);
      int intensity = pow( 2, 8 - j ) - 1;
      uint32_t color = pixels.Color( 0, 0, intensity );
      pixels.setPixelColor( pixel, color );
    }
    int lastPixel = mod(i-9, NUMPIXELS);
    pixels.setPixelColor( lastPixel, 0, 0, 0 );

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}

uint32_t getColor(char color, int intensity) {
  
  switch (color) {
    case 1:
      //do something when var equals 1
      break;
    case 2:
      //do something when var equals 2
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
}

