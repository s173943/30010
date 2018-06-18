#include "timer.h"

void configTimer2(){
    RCC->APB1ENR |= 0x00000001; // Enable clock line 2

    TIM2->CR1 = 0x0000;
    TIM2->ARR = 1000;
    TIM2->PSC = 9;
    TIM2->CR1 |= 0x0001;

    // Configure counter compare registers
    TIM2->CCER &= ~TIM_CCER_CC3P;
    TIM2->CCER |= 0x00000001 << 8;

    TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
    TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM2->CCMR2 |= TIM_OCMode_PWM1;
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |= TIM_OCPreload_Enable;

    TIM2->CCR3 = 500; // set duty cycle to 50%
}

void configTimer1() {
    RCC->APB2ENR |= RCC_APB2Periph_TIM1;
    TIM1->CR1 = 0x0000;
    TIM1->ARR = 0x0000F9FF; // 100 Hz.
    TIM1->PSC = 0x0009; // Prescale = 9
    TIM1->DIER |= 0x0001;
    NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);
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

void wait() {
    for(uint32_t i = 0; i < 2000000; i++) {}
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
/*
void showStopWatch(){

}
*/
