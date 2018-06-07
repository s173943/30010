#include "stm32f30x_conf.h"
#include "lcd.h"
#include <stdio.h>

#ifndef _TIMER_H_
#define _TIMER_H_

//A flag for updating the LCD
extern uint8_t updateLCD;
#define updateSpeed 0x000a

struct timer_t {
    uint8_t hours, minutes, seconds, hseconds;
};

volatile struct timer_t stopWatch;

void configTimer();
void resetTimer();
void TIM2_IRQHandler(void);

#endif /* _TIMER_H_ */







