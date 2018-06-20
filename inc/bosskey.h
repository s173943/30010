#ifndef BOSSKEY_H_INCLUDED
#define BOSSKEY_H_INCLUDED

#include "stm32f30x_conf.h"

#define BLOCK 219

void bossKeyEN(uint8_t *workorPay, uint8_t playingField[128][32], uint8_t oldPlayingField[128][32], uint8_t *oldx);
void bossKey(uint8_t a[128][32], uint8_t x, uint8_t y);

#endif /* BRICK_H_INCLUDED */
