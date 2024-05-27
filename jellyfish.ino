 
#include <FastLED.h>
 
#define TOP_LED_RING    2
#define MIDDLE_LED_RING 3
#define BOTTOM_LED_RING 4
#define NUM_LEDS        100
#define BRIGHTNESS      64
// #define LED_TYPE    WS2811
#define COLOR_ORDER GRB

// Array of LEDs
CRGB top_leds[NUM_LEDS];
CRGB middle_leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
 

extern CRGBPalette16 myRedWhiteBluePalette; 
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
 
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
    fill_solid(top_leds,25,CRGB::Blue);
    int current;  
    for(int i = 0; i < 10;i++){
        current = i;
        middle_leds[current] = CRGB::Blue;
        for(int j = 0; j < 4; j++){
            current += (20-(2*i+1));
            middle_leds[current] = CRGB::Blue;
            current += (2*i+1);
            middle_leds[current] = CRGB::Blue;
        }
        current += (20-(2*i+1));
        middle_leds[current] = CRGB::Blue;
        FastLED.show();
        delay(1000);
    }

    //   for(int i = 9; i < 0;i--){
    //     current = i;
    //     middle_leds[current] = CRGB::Blue;
    //     for(int j = 0; j < 4; j++){
    //         current += (20-(2*i+1));
    //         middle_leds[current] = CRGB::Blue;
    //         current += (2*i+1);
    //         middle_leds[current] = CRGB::Blue;
    //     }
    //     current += (20-(2*i+1));
    //     middle_leds[current] = CRGB::Blue;
    //     FastLED.show();
    //     current = i;
    //     middle_leds[current] = CRGB::Black;
    //     for(int j = 0; j < 4; j++){
    //         current += (20-(2*i+1));
    //         middle_leds[current] = CRGB::Black;
    //         current += (2*i+1);
    //         middle_leds[current] = CRGB::Black;
    //     }
    //     current += (20-(2*i+1));
    //     middle_leds[current] = CRGB::Black;
    //     FastLED.show();
    //     delay(1000);
    // }

    // for (int i = 0; i < 10; i++) {
    //     middle_leds[rightStart] = CRGB::Blue; 
    //     middle_leds[leftStart] = CRGB::Blue;
        
    //     FastLED.show();
    //     delay(50);

    //     middle_leds[rightStart] = CRGB::Black;
    //     middle_leds[leftStart] = CRGB::Black;
        
    //     rightStart--; 
    //     leftStart++; 
    //     delay(50);
    // }

    // MiddleCascade(9, 10);
    // MiddleCascade(19, 20);
    // MiddleCascade(29, 30);
    // MiddleCascade(39, 40);
    // MiddleCascade(49, 50);
    // MiddleCascade(59, 60);
    // MiddleCascade(69, 70);
    // MiddleCascade(79, 80);
    // MiddleCascade(89, 90);
    // MiddleCascade(99, 100);

    // // cascading
    // for(int dot = 0; dot < 25; dot++) { 
    //     top_leds[dot] = CRGB::Blue;
    //     FastLED.show();
    //     // clear this led for the next time around the loop
    //     // leds[dot] = CRGB::Black;
    //     delay(30);
    // }

    // uint8_t colorIndex = 0;
    
    // for( int i = 0; i < 25; ++i) {
    //     leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
    //     colorIndex += 3;
    // }

    // ChangePalettePeriodically();
    
    // static uint8_t startIndex = 0;
    // startIndex = startIndex + 1; /* motion speed */
    
    // FillLEDsFromPaletteColors( startIndex);
    
    // FastLED.show();
    // FastLED.delay(1000 / UPDATES_PER_SECOND);
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

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        top_leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
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
 
void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

void JellyfishPattern()
{

}
 
// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}
 
// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}
 
// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}
 
 
// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
 


// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.