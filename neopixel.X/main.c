#include <xc.h>

// Configuration bits
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (LVP disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Define system clock
// #define _XTAL_FREQ 20000000 // 20 MHz crystal oscillator
#define _XTAL_FREQ 4000000

// Function Prototypes
void sendBit(unsigned char bitVal);
void sendByte(unsigned char byteVal);
void sendPixel(unsigned char r, unsigned char g, unsigned char b);

void main(void) {
    // Initialize the RC0 pin as output
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC3 = 0;
    
    TRISD1 = 0;
    
    while(1) {
        PORTCbits.RC1 = 1;
        PORTCbits.RC0 = 1;
        
        // Send a red color pixel
        sendPixel(255, 0, 0) ;
        __delay_ms(500);
        
        PORTCbits.RC0 = 0;
        PORTCbits.RC1 = 0;
        // Send a green color pixel
        sendPixel(0, 255, 0);
        __delay_ms(500);
        
        // Send a blue color pixel
        sendPixel(0, 0, 255);
        __delay_ms(500);
    }
}

void sendBit(unsigned char bitVal) {
//    Currently, the blinking/writing to output ports does not work (i.e.
//    setting them as 1 and then 0 -> tested with random LEDs, setting them to 1
//    works but then getting them to blink is not working as expected)
    
    PORTDbits.RD1 = 1;
    
    if(bitVal) {
        // Send a '1' bit
        PORTCbits.RC0 = 1;
        __delay_ms(0.7); // 800 ns high
        PORTCbits.RC0 = 0;
        PORTCbits.RC2 = 1;
        __delay_ms(0.6); // 450 ns low
        PORTCbits.RC2 = 0;
    } else {
        // Send a '0' bit
        PORTCbits.RC0 = 1;
        __delay_ms(0.35); // 400 ns high
        PORTCbits.RC0 = 0;
        PORTCbits.RC3 = 1;
        __delay_ms(0.8); // 850 ns low
        PORTCbits.RC3 = 0;
    }
    
//    PORTDbits.RD1 = 0;
}

void sendByte(unsigned char byteVal) {
//    PORTCbits.RC2 = 1;
    for(char i = 0; i < 8; i++) {
        sendBit((byteVal >> (7 - i)) & 0x01);
    }
}

void sendPixel(unsigned char r, unsigned char g, unsigned char b) {
    sendByte(g); // NeoPixel expects colors in GRB order
    sendByte(r);
    sendByte(b);
}
