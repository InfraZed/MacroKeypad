#include <Key.h>
#include <Keypad.h>

#include <FastLED.h>
#include <Keyboard.h>

#define LED_PIN     14
#define NUM_LEDS    8
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t mode = 0;


const byte ROWS = 2; //two rows
const byte COLS = 5; //five columns

const char MACRO_1 = '1';
const char MACRO_2 = '2';
const char MACRO_3 = '3';
const char MACRO_4 = '4';
const char MACRO_5 = '5';
const char MACRO_6 = '6';
const char MACRO_7 = '7';
const char MACRO_8 = '8';
const char MACRO_9 = '9';
const char MACRO_10 = '0';

char keys[ROWS][COLS] = {
  { MACRO_1,MACRO_2,MACRO_3,MACRO_4,MACRO_5 },
  { MACRO_6,MACRO_7,MACRO_8,MACRO_9,MACRO_10 }
};

byte rowPins[ROWS] = { 3,4 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 5,6,7,8,9 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  // put your setup code here, to run once:
  delay( 2000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
    
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
char key = keypad.getKey();

  if (key == NO_KEY) 
  {
    Serial.println(key);
    rainbow();
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND);
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    return; 
  }

  if (key == MACRO_1)
  {
    Keyboard.press(KEY_F13);
    //Keyboard.print("Hello");
    delay(10);
    Keyboard.releaseAll();
  }
  else if (key == MACRO_2)
  {
    Keyboard.press(KEY_F14);
    delay(10);
    Keyboard.releaseAll();
  }
  else if (key == MACRO_3)
  {
    Keyboard.press(KEY_F15);
    delay(10);
    Keyboard.releaseAll();
  }
   else if (key == MACRO_4)
  {
    Keyboard.press(KEY_F16);
    delay(10);
    Keyboard.releaseAll();
  }
   else if (key == MACRO_5)
  {
    Keyboard.press(KEY_F17);
    delay(10);
    Keyboard.releaseAll();
  }
    else if (key == MACRO_10)
  {
    mode += 1;
    if (mode > 3) {mode=0;}
    if (mode == 0) 
    {
      blinkColor(CRGB::White);
    }

    if (mode == 1) 
    {
      blinkColor(CRGB::Red);
    }

    if (mode == 2) 
    {
      blinkColor(CRGB::Green);
    }

    if (mode == 3) 
    {
      blinkColor(CRGB::Blue);
    }
  }
  else {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(key);
    delay(10);
    Keyboard.releaseAll();
  }

  rainbow();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
  EVERY_N_MILLISECONDS( 20 ) { gHue+=3; } // slowly cycle the "base color" through the rainbow
}


void blinkColor(const struct CRGB& color)
{
  for (int i = 0; i < 3; i++)
  {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(250);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(250);
  }
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow2( leds, NUM_LEDS, gHue, 7);
}

void fill_rainbow2( struct CRGB * pFirstLED, int numToFill,
                  uint8_t initialhue,
                  uint8_t deltahue )
{
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 255;
    for( int i = 0; i < numToFill; i++) {
        pFirstLED[i] = hsv;
        hsv.hue += deltahue;
    }
}
