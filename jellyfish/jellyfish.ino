
// Colours: Purple (), blue (), silver (), pink () -> cool tones

#include <FastLED.h>

#define TOP_LED_RING    2
#define MIDDLE_LED_RING 3
#define BOTTOM_LED_RING 4
#define TOP_LED         25
#define NUM_LEDS        100
#define BRIGHTNESS      64
// #define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define FADE_AMOUNT     255
#define TWINKLE_SPEED 3 // modified
#define TWINKLE_DENSITY 5 // modified
#define DELAY_DURATION 100


// Array of LEDs
CRGB top_leds[TOP_LED];
CRGB middle_leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette; 
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

//Tick for bottom ring 
struct LEDFade {
    uint8_t currentBrightness;
    uint8_t targetBrightness;
    bool fadingUp;
};

LEDFade topLedFades[NUM_LEDS];
LEDFade middleLedFades[NUM_LEDS];

// LED mappings used in the pew
int starter_leds_asc[5] = {10,30,50,70,90};
int ender_leds_asc[5] = {19,39,59,79,99};
int starter_leds_desc[5] = {9,29,49,69,89};
int ender_leds_desc[5] = {0,20,40,60,80};
int die_asc[5] = {10,38,56,74,92};
int die_desc[5] = {4,26,48,60,82};

CRGB* starPattern[125];

void setup() {
    // power-up safety delay
    delay( 3000 );
    

    // This adds the LEDs on pin 2/3
    FastLED.addLeds<NEOPIXEL, TOP_LED_RING>(top_leds, 25).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<NEOPIXEL, MIDDLE_LED_RING>(middle_leds, 100).setCorrection( TypicalLEDStrip );
    // FastLED.addLeds<NEOPIXEL, BOTTOM_LED_RING>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    
    FastLED.setBrightness(  BRIGHTNESS );
    
    // Set the topLedFades and middleLedFades arrays to 0 
    // memset(topLedFades, 0, sizeof(topLedFades)); 
    // memset(middleLedFades, 0, sizeof(middleLedFades));

    setupStarMapping();
}


void loop()
{    
    ChangePalettePeriodically();
    // pew();

    //Base code for elays
    FastLED.delay(1000 / UPDATES_PER_SECOND);

}
 
// This changes the pattern every 10 seconds.
void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;

    // randomSparkle(top_leds, topLedFades, 25, 5, 10);
    // randomSparkle(middle_leds, middleLedFades,  100, 3, 5);
    // delay(DELAY_DURATION);

    // pew();
    // chaseEffect();
    // rgb_snowfall();
    // snowfall();
    CascadingPattern();

    // if( lastSecond != secondHand) {
    //     lastSecond = secondHand;
    //     if( secondHand ==  0)  { snowfall(); }
    //     if( secondHand ==  10) { pew(); }
    //     if( secondHand ==  20) { chaseEffect(); }
    //     if( secondHand ==  30) { rgb_snowfall(); }
    //     if( secondHand ==  40) { CascadingPattern(); }
    //     if( secondHand ==  50) { }
    //     if( secondHand ==  60) { }
    // }
}

void CascadingPattern() {
    
    fill_solid(top_leds,25,CRGB(0, 255, 20)); 

    int starter_leds_asc[5] = {10,30,50,70,90};
    int ender_leds_asc[5] = {19,39,59,79,99};
    int starter_leds_desc[5] = {9,29,49,69,89};
    int ender_leds_desc[5] = {0,20,40,60,80};
    int die_asc[5] = {10,30,50,70,90};
    int die_desc[5] = {9,29,49,69,89};

    for (int t = 0; t < 20; t++) {
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
                number[j] = (die_asc[i] + t - j) % 10 + starter_leds_asc[i];
            }
            middle_leds[number[0]] = CRGB(0, 255, 20);
            middle_leds[number[1]] = CRGB(0, 255, 20);
            middle_leds[number[2]] = CRGB(0, 255, 20);
            middle_leds[number[3]] = CHSV(60,60,60);
        }
        
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
                number[j] = (die_desc[i] - t + j) % 10 + ender_leds_desc[i];
            }
            middle_leds[number[0]] = CRGB(0, 255, 20);
            middle_leds[number[1]] = CRGB(0, 255, 20);
            middle_leds[number[2]] = CRGB(0, 255, 20);
            middle_leds[number[3]] = CHSV(60,60,60);
        }
        FastLED.show();
        delay(100);
    }
}

void IlluminatePalette()
{
    CRGB blue  = CRGB(0, 255, 20); //this is the illuminate colour, max out the green and add a bit of blue
    // CRGB green  = CRGB::MediumAquamarine;
    CRGB gold  = CRGB::Gold;
    
    currentPalette = CRGBPalette16(
                                   blue,  blue,  blue,  blue,
                                   blue, blue, blue,  blue,
                                   gold,  gold,  gold,  gold,
                                   gold, gold, gold,  gold );
}


void snowfall()
{

    fill_solid(top_leds,25,CRGB::White);

    for (int t = 0; t < 20; t++) { // 20 leds
        for (int i = 0; i < 5; i++) { //5 sides 
            int number[4] = {0}; 
            for (int j = 0; j < 4; j++) { //changing four leds
                number[j] = (die_asc[i] + t - j) % 10 + starter_leds_asc[i];
            }
            middle_leds[number[0]] = CHSV(100,0,255);
            // middle_leds[number[1]] = CRGB::Red;
            // middle_leds[number[2]] = CRGB::Green;
            middle_leds[number[1]] = CHSV(100,0,100);
            middle_leds[number[2]] = CHSV(100,0,50);
            middle_leds[number[3]] = CHSV(0,0,0);
        }
        
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
                number[j] = (die_desc[i] - t + j) % 10 + ender_leds_desc[i];
            }
            middle_leds[number[0]] = CHSV(100,0,255);
            // middle_leds[number[1]] = CRGB::Red;
            // middle_leds[number[2]] = CRGB::Green;

            middle_leds[number[1]] = CHSV(100,0,100);
            middle_leds[number[2]] = CHSV(100,0,50);
            middle_leds[number[3]] = CHSV(0,0,0);
        }
            
        // // here 
        
        // for (int i = 0; i < 5; i++) {

        //     middle_leds[number[1]] = CHSV(100,0,100);
        //     middle_leds[number[2]] = CHSV(100,0,50);
        //     middle_leds[number[3]] = CHSV(0,0,0);

        
        //   }




        FastLED.show();
        delay(100);
    }
}

void rgb_snowfall () {
    
  for (int t = 0; t < 20; t++) {
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
                number[j] = (die_asc[i] + t - j) % 10 + starter_leds_asc[i];
            }
            middle_leds[number[0]] = CRGB(255,50,255);
            middle_leds[number[1]] = CRGB(123,100,82);
            middle_leds[number[2]] = CRGB(301,100,48);
            middle_leds[number[3]] = CHSV(0,0,0);
        }
        
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
                number[j] = (die_desc[i] - t + j) % 10 + ender_leds_desc[i];
            }
            middle_leds[number[0]] = CRGB(255,50,255);
            middle_leds[number[1]] = CRGB(123,100,82);
            middle_leds[number[2]] = CRGB(301,100,48);
            middle_leds[number[3]] = CHSV(0,0,0);
        }
        FastLED.show();
        delay(100);
    }
}

// void twinkle() {
//     rand() % 10;
    
// }

void pew() {
    
    for (int x = 0; x < 250; x++) {

        int a = (x + 25) % 125;  
        int b = (x + 50) % 125;
        int c = (x + 75) % 125;
        int d = (x + 100) % 125;
        int e = (x + 125) % 125;
        
        *starPattern[e] = CRGB::Blue;
        *starPattern[a] = CRGB::Purple;
        *starPattern[b] = CRGB::Cyan;
        *starPattern[c] = CRGB::White;
        *starPattern[d] = CRGB(255,87,51);

        FastLED.show();
        delay(30);
    }
}


void pew2() {

    for (int x = 0; x < 250; x++) {

        int a = (x + 25) % 125;  
        int b = (x + 50) % 125;
        int c = (x + 75) % 125;
        int d = (x + 100) % 125;
        int e = (x + 125) % 125;
        
        *starPattern[e] = CRGB::Blue; 
        *starPattern[a] = CRGB::Purple;
        *starPattern[b] = CRGB::Cyan;
        *starPattern[c] = CRGB::White;
        *starPattern[d] = CRGB(255,87,51);

        FastLED.show();
        delay(30);
    }
}

void chaseEffect() {
  // top ring 0-24
  // mid ring 25-124
  int top_ring_len = 25;
  int middle_ring_len = 100;

  // uint8_t hue = 0;
  CRGBPalette16 palette(
    // CRGB::Amethyst,
    // CRGB::LightSkyBlue,
    // CRGB::Snow,
    // CRGB::LightPink
    CHSV(270,255,BRIGHTNESS), 
    CHSV(185,255,BRIGHTNESS), 
    CHSV(260,5,BRIGHTNESS)
    // CHSV(310,55,BRIGHTNESS)	
  );

  uint8_t index = 0;
  while (1) {  
    EVERY_N_MILLISECONDS(25) {  
      top_leds[0] = ColorFromPalette(palette, index);
      middle_leds[0] = ColorFromPalette(palette, index);
      
      for (int i = top_ring_len - 1; i > 0; i--) {
        top_leds[i] = top_leds[i - 1];
      }

      for (int i = middle_ring_len - 1; i > 0; i--) {
        middle_leds[i] = middle_leds[i - 1];
      }
      
    }
    index++;
    index = index % 256;
    FastLED.show();
  }
}

void randomSparkle(CRGB* leds, LEDFade* ledFades, int numLeds, int minTwinkle, int maxTwinkle) {
    static uint32_t lastUpdate = 0;
    uint32_t currentTime = millis();
    if (currentTime - lastUpdate > 100) {
        lastUpdate = currentTime;
        FastLED.clear();
        int activeLEDs = random(minTwinkle, maxTwinkle + 1);
        for (int i = 0; i < activeLEDs; i++) {
            int ledIndex = random(numLeds);
            uint8_t hue = random(256);
            ledFades[ledIndex].targetBrightness = random(256); // Set a new random target brightness
            ledFades[ledIndex].fadingUp = (ledFades[ledIndex].currentBrightness < ledFades[ledIndex].targetBrightness);
        }
        delay(DELAY_DURATION);
        FastLED.show();
    }

    // Gradually update brightness towards the target
    for (int i = 0; i < numLeds; i++) {
        if (ledFades[i].fadingUp && ledFades[i].currentBrightness < ledFades[i].targetBrightness) {
            ledFades[i].currentBrightness++;
        } else if (!ledFades[i].fadingUp && ledFades[i].currentBrightness > 0) {
            ledFades[i].currentBrightness--;
        }
        leds[i] = CHSV(random(256), 255, ledFades[i].currentBrightness); 
    }
}

// This function maps the LED strips across both middle and top LEDs to form a star pattern
void setupStarMapping() {
    int i = 0;

    for (int i = 0; i < 10; i++) {
        starPattern[i] = &middle_leds[i];
    }

    for (i = 10; i < 15; i++) {
        int j = i - 10;
        starPattern[i] = &top_leds[j];
    }

    for (i = 15; i < 35; i++) {
        int j = i + 15;
        starPattern[i] = &middle_leds[j];
    }

    for (i = 35; i < 40; i++) {
        int j = i - 25;
        starPattern[i] = &top_leds[j];
    }

    for (i = 40; i < 60; i++) {
        int j = i + 30;
        starPattern[i] = &middle_leds[j];
    }
    
    for (i = 60; i < 65; i++) {
        int j = i - 40;
        starPattern[i] = &top_leds[j];
    }
    
    for (i = 65; i < 85; i++) {
        int j = i - 55;
        starPattern[i] = &middle_leds[j];
    }
    
    for (i = 85; i < 90; i++) {
        int j = i - 80;
        starPattern[i] = &top_leds[j];
    }
    
    for (i = 90; i < 110; i++) {
        int j = i - 40;
        starPattern[i] = &middle_leds[j];
    }
    
    for (i = 110; i < 115; i++) {
        int j = i - 95;
        starPattern[i] = &top_leds[j];
    }
    for (i = 115; i < 125; i++) {
        int j = i - 25;
        starPattern[i] = &middle_leds[j];
    }
}

