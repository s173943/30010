#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED
#include "ball.h"
#include "brick.h"

struct powerUp_t {
    uint8_t x;
    uint8_t y;
    int8_t vel;
    uint8_t type;
};

void initPowerUp(struct powerUp_t *p, int32_t x, int32_t y, int8_t leftOrRight);

void powerUpdate(struct powerUp_t *p, uint8_t x1, uint8_t x2, struct ball_t *b, struct ball_t *c, struct ball_t *d, struct ball_t *e, struct ball_t *f, uint8_t playingField[128][32], uint8_t *balls);

void powerToArray(struct powerUp_t *p, uint8_t playingField[128][32]);

void removePowerUpFromArray(struct powerUp_t *p, uint8_t playingField[128][32]);


#endif /* POWERUP_H_INCLUDED */
