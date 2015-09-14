// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define BUTTON_PIN     2
#define PIN            6
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long debouncingTime = 300; //Debouncing Time in Milliseconds
volatile unsigned long lastMicros;
int delayVal = 100; // delay for half a second
int buttonState = 0;
int cleanState = 1;

void setup() {
  Serial.begin( 9600 );
//  pinMode( BUTTON_PIN , INPUT );
  attachInterrupt( digitalPinToInterrupt( BUTTON_PIN ), debounceInterrupt, RISING );
  pixels.begin(); // This initializes the NeoPixel library.
  cleanRing();
}

int mod( int x, int m ) {
  return ( x % m + m ) % m;
}

void loop() {
  Serial.println(buttonState);
  if ( buttonState ) {
    trailing( 'b' );
  } else if ( !cleanState ) {
    cleanRing();
  }
}

void trailing( char color ) {
  for( int i=0; i < NUMPIXELS; i++ ){
    for( int j = 0; j < 8; j++ ){
      int pixel = mod( i-j , NUMPIXELS );
      int intensity = pow( 2, 8 - j ) - 1;
      uint32_t pixelColor = getColor( color, intensity ); 
      pixels.setPixelColor( pixel, pixelColor );
    }
    int lastPixel = mod( i-9 , NUMPIXELS);
    pixels.setPixelColor( lastPixel, 0, 0, 0 );

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay( delayVal ); // Delay for a period of time (in milliseconds).

  }
  cleanState = 0;
}

uint32_t getColor( char color, int intensity ) {
  uint32_t pixelColor;
  switch (color) {
    case 'r':
      pixelColor = pixels.Color( intensity, 0, 0 );
      break;
    case 'g':
      pixelColor = pixels.Color( 0, intensity, 0 );
      break;
    default: 
      pixelColor = pixels.Color( 0, 0, intensity );
    break;
  }
  return pixelColor;
}

void cleanRing() {
  Serial.println( "cleanRing" );
  for( int i = 0; i < NUMPIXELS; i++ ){
    pixels.setPixelColor( i, 0, 0, 0 );
  }
  pixels.show();
  cleanState = 1;
}

void debounceInterrupt() {
  if(( long )( micros() - lastMicros ) >= debouncingTime * 1000 ) {
    changeState();
    lastMicros = micros();
  }
}

void changeState() {
  Serial.println( "changeState" );
  buttonState = ( buttonState + 1 ) % 2;
}

