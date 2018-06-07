#ifndef _BALL_H_
#define _BALL_H_

#include "stm32f30x_conf.h"
#include "string.h"
#include "lut_trig.h"
#include "ansi.h"

struct ball_t {
    struct vector_t pos, vel;
    uint16_t hits;
};

void initVector(struct vector_t *v, int32_t x, int32_t y);
void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy);
void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy);
void removeBall(struct ball_t *b);
void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif /* _BALL_H_ */

