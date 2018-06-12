#include "timer.h"

//struct timer_t stopWatch = {0, 0, 0, 0};

void configTimer2(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = 0x0000;
    TIM2->ARR = 0x0000F9FF; // 100 Hz
    TIM2->PSC = 0x0009; // Prescale = 9
    TIM2->DIER |= 0x0001;
    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void configTimer1() {
    RCC->APB2ENR |= RCC_APB2Periph_TIM1;
    TIM1->CR1 = 0x0000;
    TIM1->ARR = 0x0000F9FF; // 100 Hz.
    TIM1->PSC = 0x0009; // Prescale = 9
    TIM1->DIER |= 0x0001;
    NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 1);
    NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
}

void resetTimer2() {
    //
}

void resetTimer1() {
    TIM3->CR1 = 0x0000;
    TIM3->CNT = 0x00000000;
    stopWatch.hours = 0;
    stopWatch.minutes = 0;
    stopWatch.seconds = 0;
    stopWatch.dseconds = 0;
}

void TIM1_UP_TIM16_IRQHandler(void) {
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
    TIM1->SR &= ~0x0001;
}
