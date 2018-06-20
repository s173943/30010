#ifndef _BALL_H_
#define _BALL_H_

#include "stm32f30x_conf.h"
#include "string.h"
#include "trigonometri.h"
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "menu.h"
#include "powerUp.h"
#include "brick.h"


#define MINVELX 6194 //bliver til 0.0851??
#define MINVELY 22337 //bliver til 0.2?

struct ball_t {
    struct vector_t pos, vel;
    uint8_t state;
};



void initVector(struct vector_t *v, int32_t x, int32_t y);
void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy, uint8_t aliveOrDead);
void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy);
void removeBall(struct ball_t *b);
void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives, uint8_t *score, struct powerUp_t *p, uint8_t *balls, uint8_t *menuSettings);
void ballToArray(struct ball_t *b, uint8_t playingField[128][32]);
void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]);
<<<<<<< HEAD
void updatePlayer(uint8_t a[128][32],uint16_t adc1,uint16_t adc2);
void removePowerUpFromArray(struct powerUp_t *p, uint8_t playingField[128][32]);
=======
void updatePlayer(uint8_t a[128][32]);
>>>>>>> fuckup

#endif /* _BALL_H_ */
