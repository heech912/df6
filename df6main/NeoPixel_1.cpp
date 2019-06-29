// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__

 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket

#endif



#define PIN        6
#define NUMPIXELS  8



// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



#define DELAYVAL 500



void setup() {

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)

  clock_prescale_set(clock_div_1);

#endif

  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}


//픽셀을 전부 끄고 pixels_delayTime만큼 기다린다.
void pixels_TurnOff(int pixels_delayTime){
  pixels.clear();
  pixels.show();
  delay(pixels_delayTime);
}



void loop() {

  pixels_TurnOff(5000);

  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, i * 20));
    pixels.show();
    delay(DELAYVAL);
  }

  pixels_TurnOff(5000);

  for(int j=1; j<=250; j++){

    for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(250-j, 250, 250-i*30));
      pixels.show();
    }

    delay(100); //dalay 총 25000. 250*100

  }


  delay(1000);


}
