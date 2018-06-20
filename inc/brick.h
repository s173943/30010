#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED
#include "ball.h"
#include "powerUp.h"

void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32]);

void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks, struct powerUp_t *p, int8_t powerUpLeftOrRight, uint8_t *score);



#endif /* BRICK_H_INCLUDED */
