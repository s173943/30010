#include "timer.h"

//struct timer_t stopWatch = {0, 0, 0, 0};

void configTimer(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = 0x0000;
    TIM2->ARR = 0x0009C3FF; // 100 Hz
    TIM2->PSC = 0x0000; // Prescale = 0
    TIM2->DIER |= 0x0001;
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void resetTimer() {
    TIM2->CR1 = 0x0000;
    TIM2->CNT = 0x00000000;
    stopWatch.hours = 0;
    stopWatch.minutes = 0;
    stopWatch.seconds = 0;
    stopWatch.dseconds = 0;
}

void TIM2_IRQHandler(void) {
    stopWatch.dseconds++;

    if (stopWatch.dseconds == 100) {
        stopWatch.dseconds = 0;
        stopWatch.seconds++;
    }
    if (stopWatch.seconds == 60) {
        stopWatch.seconds = 0;
        stopWatch.minutes++;
    }
    if (stopWatch.minutes == 60) {
        stopWatch.minutes = 0;
        stopWatch.hours++;
    }
    if (stopWatch.dseconds == 0 || (stopWatch.dseconds & updateSpeed) == updateSpeed) {
        updateLCD = 1;
    }
    TIM2->SR &= ~0x0001;
}
