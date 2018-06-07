#ifndef _PIN_IO_H_
#define _PIN_IO_H_

#include "stm32f30x_conf.h"

void pinSetup(uint16_t port, char portName, uint32_t moder, uint32_t puder);
void configJoy();
void configLed();
uint8_t readJoystick();
void setLed(uint8_t b, uint8_t g, uint8_t r);

uint16_t readADC1();
uint16_t readADC2();

#endif /* _PIN_IO_H_ */
