#include "neopixel.h"
#include "mcc_generated_files/mcc.h"

void logic_0()
{
    LATCbits.LATC5 = 1; // Data_SetHigh();
    __delay_us(0.35);
    LATCbits.LATC5 = 0; // Data_SetLow();
    //__delay_us(0.1);
}

void logic_1()
{
    LATCbits.LATC5 = 1; // Data_SetHigh();
    __delay_us(0.7);
    LATCbits.LATC5 = 0; // Data_SetLow();
    //__delay_us(0.1);
}

int * pixels[STRIP_SIZE];

void setPixelColor(int i, int * color)
{
    pixels[i] = color;
}

void show()
{
    int * color;
    for(int i = 0; i < STRIP_SIZE; i++)
    {
        color = pixels[i];
        (color[0] >> 1) ? logic_1() : logic_0();
        (color[0] >> 2) ? logic_1() : logic_0();
        (color[0] >> 3) ? logic_1() : logic_0();
        (color[0] >> 4) ? logic_1() : logic_0();
        (color[0] >> 5) ? logic_1() : logic_0();
        (color[0] >> 6) ? logic_1() : logic_0();
        (color[0] >> 7) ? logic_1() : logic_0();
        (color[0] >> 8) ? logic_1() : logic_0();

        (color[1] >> 1) ? logic_1() : logic_0();
        (color[1] >> 2) ? logic_1() : logic_0();
        (color[1] >> 3) ? logic_1() : logic_0();
        (color[1] >> 4) ? logic_1() : logic_0();
        (color[1] >> 5) ? logic_1() : logic_0();
        (color[1] >> 6) ? logic_1() : logic_0();
        (color[1] >> 7) ? logic_1() : logic_0();
        (color[1] >> 8) ? logic_1() : logic_0();

        (color[2] >> 1) ? logic_1() : logic_0();
        (color[2] >> 2) ? logic_1() : logic_0();
        (color[2] >> 3) ? logic_1() : logic_0();
        (color[2] >> 4) ? logic_1() : logic_0();
        (color[2] >> 5) ? logic_1() : logic_0();
        (color[2] >> 6) ? logic_1() : logic_0();
        (color[2] >> 7) ? logic_1() : logic_0();
        (color[2] >> 8) ? logic_1() : logic_0();
    }
}

