#ifndef LCD_H
#define LCD_H

#include "stm32f30x_conf.h"
#include <stdio.h>
#include <string.h>
#include "charset.h"
#include "30010_io.h"
#include "trigonometri.h"
#include "pin_io.h"

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )
#define PLAYERMAX 21

uint8_t updateLCD;
uint8_t lcdArray[512];

void setupLCD();
void reset_Buffer();
void convertArrayToBuffer(uint8_t a[128][32]);

#endif //LCD_H

