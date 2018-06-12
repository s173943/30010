#include "pin_io.h"

void pinSetup(uint16_t port, char portName, uint32_t moder, uint32_t puder) {
    if (portName == 'A')
    {
        GPIOA->MODER &= ~(0x00000003 << (port * 2));
        GPIOA->MODER |= (moder << (port * 2));
        GPIOA->PUPDR &= ~(0x00000003 << (port * 2));
        GPIOA->PUPDR |= (puder << (port * 2));
        if (moder == 0x00000001)
        {
            GPIOA->OSPEEDR &= ~(0x00000003 << (port * 2));
            GPIOA->OSPEEDR |=  (0x00000002 << (port * 2));
            GPIOA->OTYPER &= ~(0x0003 << (port * 2));
            GPIOA->OTYPER |=  (0x0000 << (port * 2));
        }
    }
    else if (portName == 'B')
    {
        GPIOB->MODER &= ~(0x00000003 << (port * 2));
        GPIOB->MODER |= (moder << (port * 2));
        GPIOB->PUPDR &= ~(0x00000003 << (port * 2));
        GPIOB->PUPDR |= (puder << (port * 2));
        if (moder == 0x00000001)
        {
            GPIOB->OSPEEDR &= ~(0x00000003 << (port * 2));
            GPIOB->OSPEEDR |=  (0x00000002 << (port * 2));
            GPIOB->OTYPER &= ~(0x0003 << (port * 2));
            GPIOB->OTYPER |=  (0x0000 << (port * 2));
        }
    }
    else if (portName == 'C')
    {
        GPIOB->MODER &= ~(0x00000003 << (port * 2));
        GPIOB->MODER |= (moder << (port * 2));
        GPIOB->PUPDR &= ~(0x00000003 << (port * 2));
        GPIOB->PUPDR |= (puder << (port * 2));
        if (moder == 0x00000001)
        {
            GPIOB->OSPEEDR &= ~(0x00000003 << (port * 2));
            GPIOB->OSPEEDR |=  (0x00000002 << (port * 2));
            GPIOB->OTYPER &= ~(0x0003 << (port * 2));
            GPIOB->OTYPER |=  (0x0000 << (port * 2));
        }
    }
}

void configJoy() {
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for port A.
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for port B.
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for port C.

    // Clear mode registers
    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Right   (PC0)
    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // UP      (PA4)
    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Center  (PB5)
    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Left    (PC1)
    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Down    (PB0)
    // Set mode registers (0x00 - Input, 0x01 - Output)
    GPIOC->MODER |= (0x00000000 << (0 * 2)); // Right   (PC0)
    GPIOA->MODER |= (0x00000000 << (4 * 2)); // UP      (PA4)
    GPIOB->MODER |= (0x00000000 << (5 * 2)); // Center  (PB5)
    GPIOC->MODER |= (0x00000000 << (1 * 2)); // Left    (PC1)
    GPIOB->MODER |= (0x00000000 << (0 * 2)); // Down    (PB0)
    // Clear push/pull register
    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Right   (PC0)
    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // UP      (PA4)
    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Center  (PB5)
    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Left    (PC1)
    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Down    (PB0)
    // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)
    GPIOC->PUPDR |= (0x00000000 << (0 * 2)); // Right   (PC0)
    GPIOA->PUPDR |= (0x00000000 << (4 * 2)); // UP      (PA4)
    GPIOB->PUPDR |= (0x00000000 << (5 * 2)); // Center  (PB5)
    GPIOC->PUPDR |= (0x00000000 << (1 * 2)); // Left    (PC1)
    GPIOB->PUPDR |= (0x00000000 << (0 * 2)); // Down    (PB0)
}

uint8_t readJoystick() {
    uint8_t x = 0x00;
    // Read joystick
    x |= (GPIOA->IDR & (0x001 << 4)) >> 4; // Up       (PA4)
    x |= (GPIOB->IDR & (0x001 << 0)) << 1; // Down     (PB0)
    x |= (GPIOC->IDR & (0x001 << 1)) << 1; // Left     (PC1)
    x |= (GPIOC->IDR & (0x001 << 0)) << 3; // Right    (PC0)
    x |= (GPIOB->IDR & (0x001 << 5)) >> 1; // Center   (PB5)

    return x;
}

void configLed() {
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); //Blue
    GPIOA->MODER |= (0x00000001 << (9 * 2));
    GPIOA->PUPDR &= ~(0x00000003 << (9 * 2));
    GPIOA->PUPDR |= (0x00000000 << (9 * 2));
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));
    GPIOA->OSPEEDR |=  (0x00000002 << (9 * 2));
    GPIOA->OTYPER &= ~(0x0003 << (9 * 2));
    GPIOA->OTYPER |=  (0x0000 << (9 *2));

    GPIOC->MODER &= ~(0x00000003 << (7 * 2)); //Green
    GPIOC->MODER |= (0x00000001 << (7 * 2));
    GPIOC->PUPDR &= ~(0x00000003 << (7 * 2));
    GPIOC->PUPDR |= (0x00000000 << (7 * 2));
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
    GPIOC->OSPEEDR |=  (0x00000002 << (7 * 2));
    GPIOC->OTYPER &= ~(0x0003 << (7 * 2));
    GPIOC->OTYPER |=  (0x0000 << (7 * 2));

    GPIOB->MODER &= ~(0x00000003 << (4 * 2)); //Red
    GPIOB->MODER |= (0x00000001 << (4 * 2));
    GPIOB->PUPDR &= ~(0x00000003 << (4 * 2));
    GPIOB->PUPDR |= (0x00000000 << (4 * 2));
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
    GPIOB->OSPEEDR |=  (0x00000002 << (4 * 2));
    GPIOB->OTYPER &= ~(0x0001 << (4 * 2));
    GPIOB->OTYPER |=  (0x0000 << (4 *2));
}

void setLed(uint8_t b, uint8_t g, uint8_t r) {
    r = r > 0 ? 0 : 1;
    g = g > 0 ? 0 : 1;
    b = b > 0 ? 0 : 1;

    if (b == 1) {
        GPIOA->ODR |= (0x0001 << 9);
    } else {
        GPIOA->ODR &= ~(0x0001 << 9);
    }
    if (g == 1) {
        GPIOC->ODR |= (0x0001 << 7);
    } else {
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    if (r == 1) {
        GPIOB->ODR |= (0x0001 << 4);
    } else {
        GPIOB->ODR &= ~(0x0001 << 4);
    }
}

void configSpeaker() {
    // The speaker is located at PB10. TIM2 CH3
    GPIOB->MODER &= ~(0x00000003 << (10 * 2));
    GPIOB->MODER |= (0x00000002 << (10 * 2)); // Alternate function
    GPIOB->PUPDR &= ~(0x00000003 << (10 * 2));
    GPIOB->PUPDR |= (0x00000000 << (10 * 2)); // No pull
    GPIOB->OSPEEDR &= ~(0x00000003 << (10 * 2));
    GPIOB->OSPEEDR |=  (0x00000002 << (10 * 2)); // Medium speed (?)
    GPIOB->OTYPER &= ~(0x0001 << (10));
    GPIOB->OTYPER |=  (0x0000 << (10)); // Push/pull output register

}

uint16_t readADC1() {
    pinSetup(0, 'A', 0, 0);

    RCC->CFGR2  &=  ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2  |=  RCC_CFGR2_ADCPRE12_DIV6;
    RCC->AHBENR |=  RCC_AHBPeriph_ADC12;

    ADC1->CR    =   0x00000000;
    ADC1->CFGR  &=  0xFDFFC007;
    ADC1->SQR1  &=  ~ADC_SQR1_L;

    ADC1->CR    |=  0x10000000;
    for(int i = 0; i < 1000; i++);
    ADC1->CR    |=  0x80000000;
    for(int i = 0; i < 100; i++);

    ADC1->CR    |=  0x00000001;
    while(!(ADC1->ISR & 0x00000001));

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
    return ADC_GetConversionValue(ADC1);
}

uint16_t readADC2() {
    pinSetup(1, 'A', 0, 0);

    RCC->CFGR2  &=  ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2  |=  RCC_CFGR2_ADCPRE12_DIV6;
    RCC->AHBENR |=  RCC_AHBPeriph_ADC12;

    ADC1->CR    =   0x00000000;
    ADC1->CFGR  &=  0xFDFFC007;
    ADC1->SQR1  &=  ~ADC_SQR1_L;

    ADC1->CR    |=  0x10000000;
    for(int i = 0; i < 1000; i++);
    ADC1->CR    |=  0x80000000;
    for(int i = 0; i < 100; i++);

    ADC1->CR    |=  0x00000001;
    while(!(ADC1->ISR & 0x00000001));

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
    return ADC_GetConversionValue(ADC1);
}
