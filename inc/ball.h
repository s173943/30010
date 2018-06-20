#ifndef _BALL_H_
#define _BALL_H_

#include "stm32f30x_conf.h"
#include "string.h"
#include "trigonometri.h"
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "menu.h"

#define MINVELX 6194 //bliver til 0.0851??
#define MINVELY 22337 //bliver til 0.2?

struct ball_t {
    struct vector_t pos, vel;
    uint16_t hits;
    uint8_t state;
};

struct powerUp_t {
    uint8_t x;
    uint8_t y;
    int8_t vel;
    uint8_t type;
};

void initVector(struct vector_t *v, int32_t x, int32_t y);
void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy, uint8_t aliveOrDead);
void initPowerUp(struct powerUp_t *p, int32_t x, int32_t y, int8_t leftOrRight);
void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32]);
void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy);
void removeBall(struct ball_t *b);
void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives, uint8_t *score, struct powerUp_t *p, uint8_t *balls, uint8_t *menuSettings);
void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks, struct powerUp_t *p, int8_t powerUpLeftOrRight, uint8_t *score);
void powerUpdate(struct powerUp_t *p, uint8_t x1, uint8_t x2, struct ball_t *b, struct ball_t *c, struct ball_t *d, struct ball_t *e, struct ball_t *f, uint8_t playingField[128][32], uint8_t *balls);
void powerToArray(struct powerUp_t *p, uint8_t playingField[128][32]);
void ballToArray(struct ball_t *b, uint8_t playingField[128][32]);
void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]);
void updatePlayer(uint8_t a[128][32],uint16_t adc1,uint16_t adc2);
void removePowerUpFromArray(struct powerUp_t *p, uint8_t playingField[128][32]);

#endif /* _BALL_H_ */
