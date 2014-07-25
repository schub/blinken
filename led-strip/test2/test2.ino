#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ400);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t c_red = strip.Color(255, 0, 0);
uint32_t c_green = strip.Color(0, 255, 0);
uint32_t c_blue = strip.Color(0, 0, 255);
uint32_t c_black = strip.Color(0, 0, 0);
uint32_t c_white = strip.Color(255, 255, 255);

uint16_t leg[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  colorWipe2(strip.Color(0, 0, 255), 10);
  //colorWipe3(strip.Color(0, 0, 255), 10);
  //setObject(leg, c_blue);
  
  //colorWipe(c_blue, 20);
  
}

void setObject(uint16_t data[], uint32_t col) {
  
  for (uint16_t i=0; i<9; i++) {
    strip.setPixelColor(data[i], c_blue);
  }
  
  delay(50);
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe2(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint32_t c1 = Wheel(i % 255);
    uint32_t c2 = Wheel((strip.numPixels()-i) % 255);
    
    strip.setPixelColor(i, c1);
    strip.setPixelColor(i+1, c1);
    strip.setPixelColor(i+2, c1);
    
    strip.setPixelColor(strip.numPixels()-i, c2);
    strip.setPixelColor(strip.numPixels()-i-1, c2);
    strip.setPixelColor(strip.numPixels()-i-2, c2);

    strip.show();
    delay(wait);
    strip.setPixelColor(i, c_black);
    strip.setPixelColor(strip.numPixels()-i, c_black);
  }
}

void colorWipe3(uint32_t c, uint8_t wait) {

  for(uint16_t outer=0; outer<10000; outer++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      if  (i%10 < 5) {
        strip.setPixelColor((i+outer)%300, c_red);
      } else {
        strip.setPixelColor((i+outer)%300, c_black);
      }
    }
    strip.show();
    delay(10);
  }
}

// sets a range of leds
void setRange(uint16_t index, uint16_t num, uint32_t col) {
  for (uint16_t i = index; i<index+num; i++) {
    strip.setPixelColor(i, col);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

