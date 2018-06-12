#include "timer.h"

//struct timer_t stopWatch = {0, 0, 0, 0};

void configTimer2(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = 0x0000;
    TIM2->ARR = 0x0009C3FF; // 100 Hz
    TIM2->PSC = 0x0000; // Prescale = 0
    TIM2->DIER |= 0x0001;
    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void configTimer3() {
    RCC->APB1ENR |= RCC_APB1Periph_TIM3;
    TIM3->CR1 = 0x0000;
    TIM3->ARR = 0x0009C3FF; // 100 Hz
    TIM3->PSC = 0x0000; // Prescale = 0
    TIM3->DIER |= 0x0001;
    NVIC_SetPriority(TIM3_IRQn, 0);
    NVIC_EnableIRQ(TIM3_IRQn);
}

void resetTimer2() {
    //
}

void resetTimer3() {
    TIM3->CR1 = 0x0000;
    TIM3->CNT = 0x00000000;
    stopWatch.hours = 0;
    stopWatch.minutes = 0;
    stopWatch.seconds = 0;
    stopWatch.dseconds = 0;
}

void TIM3_IRQHandler(void) {
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
    TIM3->SR &= ~0x0001;
}
