/* 
 * File:   neopixel.h
 * Author: Borey
 *
 * Created on April 12, 2018, 4:59 PM
 */

#ifndef NEOPIXEL_H
#define	NEOPIXEL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#define STRIP_SIZE 36

void logic_0(void);

void logic_1(void);

void setPixelColor(int i, int * color);

void show();

#endif	/* NEOPIXEL_H */

