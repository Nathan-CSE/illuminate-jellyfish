
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

// Array of LEDs
CRGB top_leds[TOP_LED];
CRGB middle_leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette; 
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

//Tick for bottom ring 

void setup() {
    delay( 3000 ); // power-up safety delay

    // This adds the LEDs on pin 2/3 -> pretty sure addLeds, adds all the pins to the array which
    // we can write to: 0-24 (top ring), 25-124 (middle ring)
    FastLED.addLeds<NEOPIXEL, TOP_LED_RING>(top_leds, 25).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<NEOPIXEL, MIDDLE_LED_RING>(middle_leds, 100).setCorrection( TypicalLEDStrip );
    // FastLED.addLeds<NEOPIXEL, BOTTOM_LED_RING>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

    FastLED.setBrightness(  BRIGHTNESS );
    currentPalette = RainbowColors_p;
    
    currentBlending = LINEARBLEND;
}

void loop()
{
    // fill_solid(top_leds,25,CRGB::Black);
    // fill_solid(middle_leds,125,CRGB::Black);
    // NewCascade();
    // randomSparkle(top_leds, 25, 3, 5);
    // randomSparkle(middle_leds, 100, 3, 5);

    // DannyPalette();
    pew();
    // chaseEffect();
    // NewCascade();
    // CascadingPattern();
    // uint8_t colorIndex = 0;
    
    // for( int i = 0; i < NUM_LEDS; ++i) {
    //     // middle_leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
    //     top_leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
    //     colorIndex += 3;
    // }

    // ChangePalettePeriodically();
    
    // static uint8_t startIndex = 0;
    // startIndex = startIndex + 1; /* motion speed */
    
    // FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    // delay(DELAY_DURATION);
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
 
void CascadingPattern(){
    // I want a different colour scheme, all white, then have it arc down.
    // spin around
    CRGB illuminatecolour = CRGB(0, 255, 20);
    int current;   
    FastLED.show();
    fill_solid(top_leds,25,CRGB(0, 255, 20));
    fill_solid(middle_leds,100,CRGB(120, 120, 120));
    FastLED.show();
    delay(50);


    // top_leds[i] = illuminatecolour;
    // top_leds[i+1] = illuminatecolour;
    // top_leds[i+2] = illuminatecolour;

    for(int i = 10; i > 0;i--){  


        current = i; 
        middle_leds[current] = CRGB(0, 255, 20);
        for(int j = 0; j < 4; j++){
            current += (20-(2*i+1));
            middle_leds[current] = CRGB(0, 255, 20);
            current += (2*i+1);
            middle_leds[current] = CRGB(0, 255, 20);
        }
        current += (20-(2*i+1));
        middle_leds[current] = CRGB(0, 255, 20);
        FastLED.show();
        delay(50);
        current = i;
        middle_leds[current] = CRGB(120, 120, 120);
        for(int j = 0; j < 4; j++){
            current += (20-(2*i+1));
            middle_leds[current] = CRGB(120, 120, 120);
            current += (2*i+1);
            middle_leds[current] = CRGB(120, 120, 120);
        }
        current += (20-(2*i+1));
        middle_leds[current] = CRGB(120, 120, 120);
        FastLED.show();
        delay(50);
    }



} 

void MiddleCascade(int rightStart, int leftStart) 
{
    for (int i = 0; i < 10; i++) {
        middle_leds[rightStart] = CRGB::Blue; 
        middle_leds[leftStart] = CRGB::Blue;
        
        FastLED.show();
        delay(50);

        middle_leds[rightStart] = CRGB::Black;
        middle_leds[leftStart] = CRGB::Black;
        
        rightStart--; 
        leftStart++; 
        delay(50);
    }

}

void NewCascade() {
    //thing
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

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 100;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        top_leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        middle_leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

// This changes the pattern every 10/15/20/25 seconds.
void ChangePalettePeriodically()
{
    // chaseEffect();
    // DannyPalette();
    IlluminatePalette();
    currentBlending = LINEARBLEND;
    
    // uint8_t secondHand = (millis() / 1000) % 60;
    // static uint8_t lastSecond = 99;
        
    // if( lastSecond != secondHand) {
    //     lastSecond = secondHand;
    //     if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
    //     if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
    //     if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
    //     if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
    //     if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
    //     if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
    //     if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
    //     if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
    //     if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
    //     if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
    //     if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    // }
}
 
// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}
 

void IlluminatePalette()
{
    CRGB blue  = CRGB(0, 255, 20);; //this is the illuminate colour, max out the green and add a bit of blue
    // CRGB green  = CRGB::MediumAquamarine;
    CRGB gold  = CRGB::Gold;
    
    currentPalette = CRGBPalette16(
                                   blue,  blue,  blue,  blue,
                                   blue, blue, blue,  blue,
                                   gold,  gold,  gold,  gold,
                                   gold, gold, gold,  gold );
}

// void Snake(){

// }
void DannyPalette()
{
   fill_solid(top_leds,25,CRGB::White);

    int starter_leds_asc[5] = {10,30,50,70,90};
    int ender_leds_asc[5] = {19,39,59,79,99};
    int starter_leds_desc[5] = {9,29,49,69,89};
    int ender_leds_desc[5] = {0,20,40,60,80};
    int order[10] = {10,49,90,29,70,9,50,89,30,69};
    int die_asc[5] = {10,38,56,74,92};
    int die_desc[5] = {4,26,48,60,82};


    for (int t = 0; t < 20; t++) {
        for (int i = 0; i < 5; i++) {
            int number[4] = {0};
            for (int j = 0; j < 4; j++) {
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
        FastLED.show();
        delay(100);
    }
}

void pew() {
    
    CRGB* array[125];
    int  i = 0;
    for (int i = 0; i < 10; i++) {
        array[i] = &middle_leds[i];
    }
    
    for (i = 10; i < 15; i++) {
        int j = i - 10;
        array[i] = &top_leds[j];
    }
    
    for (i = 15; i < 35; i++) {
        int j = i + 15;
        array[i] = &middle_leds[j];
    }
    
    for (i = 35; i < 40; i++) {
        int j = i - 25;
        array[i] = &top_leds[j];
    }
    for (i = 40; i < 60; i++) {
        int j = i + 30;
        array[i] = &middle_leds[j];
    }
    
    for (i = 60; i < 65; i++) {
        int j = i - 40;
        array[i] = &top_leds[j];
    }
    
    for (i = 65; i < 85; i++) {
        int j = i - 55;
        array[i] = &middle_leds[j];
    }
    
    for (i = 85; i < 90; i++) {
        int j = i - 80;
        array[i] = &top_leds[j];
    }
    
    for (i = 90; i < 110; i++) {
        int j = i - 40;
        array[i] = &middle_leds[j];
    }
    
    for (i = 110; i < 115; i++) {
        int j = i - 95;
        array[i] = &top_leds[j];
    }
    for (i = 115; i < 125; i++) {
        int j = i - 25;
        array[i] = &middle_leds[j];
    }

    for (int x = 0; x < 250; x++) {

        // int a = (x + 25) % 125;  
        // int b = (x + 50) % 125;
        // int c = (x + 75) % 125;
        // int d = (x + 100) % 125;
        // int e = (x + 125) % 125;
        
        // *array[e] = CRGB::Blue;
        // *array[a] = CRGB::Purple;
        // *array[b] = CRGB::Cyan;
        // *array[c] = CRGB::White;
        // *array[d] = CRGB(255,87,51);

        // FastLED.show();
        // delay(30);
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

void randomSparkle(CRGB* leds, int numLeds, int minTwinkle, int maxTwinkle) {
    FastLED.clear();

    int activeLEDs = random(minTwinkle, maxTwinkle + 1); // Random number of LEDs to light up
    for (int i = 0; i < activeLEDs; i++) {
        int ledIndex = random(numLeds);
        leds[ledIndex] = CHSV(random(256), 255, random(100, 255));
        FastLED.show();
        delay(random(100, 150));
        leds[ledIndex] = CRGB::Black;    
    }

    // If Pixel is lit, fade away
    for (int i = 0; i < numLeds; i++) {
      if (leds[i]) {  
          leds[i].fadeToBlackBy(FADE_AMOUNT);
      }
    }
}

// increase brightness and decrease it fade in fade out effect