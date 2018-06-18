#ifndef _BALL_H_
#define _BALL_H_

#include "stm32f30x_conf.h"
#include "string.h"
#include "trigonometri.h"
#include "ansi.h"
#include "pin_io.h"

#define MINVELX 6194 //bliver til 0.0851??
#define MINVElY 22337 //bliver til 0.2?

//0.09425 laveste boldhastighed?
//0.34077

struct ball_t {
    struct vector_t pos, vel;
    uint16_t hits;
    uint8_t state;
};

void initVector(struct vector_t *v, int32_t x, int32_t y);
void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy, uint8_t aliveOrDead);
void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy);
void removeBall(struct ball_t *b);
void lvl1(uint8_t x, uint8_t y, uint8_t playingField[128][32],  uint8_t *bricks, uint8_t *lives);
void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks);


void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives, uint8_t *score);
void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *score);


void ballToArray(struct ball_t *b, uint8_t playingField[128][32]);
void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]);

#endif /* _BALL_H_ */
