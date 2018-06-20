#include "powerUp.h"



void initPowerUp(struct powerUp_t *p, int32_t x, int32_t y, int8_t leftOrRight){
    uint8_t random;
    random = rand() % 3 + 1;
    p->x = x;
    p->y = y;
    p->vel = leftOrRight;
    p->type = random;
}

void powerUpdate(struct powerUp_t *p, uint8_t x1, uint8_t x2, struct ball_t *b, struct ball_t *c, struct ball_t *d, struct ball_t *e, struct ball_t *f, uint8_t playingField[128][32], uint8_t *balls){
    uint8_t q, strikerRight, strikerLeft;
    // If p velocity is not 0 it is alive and should be updated
    if(p->vel != 0){
        if(p->x > x1+1 && p->x < x2+1){
            if((p->vel)>0){
                (p->x)++;
            }else{
                (p->x)--;
            }
        }else{
            if((p->vel)>0){
                for(q=1; q<32; q++){
                    if (playingField[100][q] == 179){
                        strikerRight = q;
                        break;
                    }
                }
                // If within striker
                if(p->y > strikerRight && p->y < strikerRight+10){
                    // if less than 5 balls add 1
                    if(*balls<5){
                        (*balls)++;
                    }
                    // Find first "available" and init it
                    if(b->state == 3){
                        initBall(b, x2+1, 5+strikerRight, 0, 0, 1);
                    }else if(c->state == 3){
                        initBall(c, x2+1, 5+strikerRight, 0, 0, 1);
                    }else if(d->state == 3){
                        initBall(d, x2+1, 5+strikerRight, 0, 0, 1);
                    }else if(e->state == 3){
                        initBall(e, x2+1, 5+strikerRight, 0, 0, 1);
                    }else if(f->state == 3){
                        initBall(f, x2+1, 5+strikerRight, 0, 0, 1);
                    }
                }
                initPowerUp(p, 5, 5, 0);
                playingField[p->x-1][p->y-1] = 0;
                playingField[p->x][p->y] = 0;
                playingField[p->x-1][p->y+1] = 0;
            }else{
                for(q=1; q<32; q++){
                    if (playingField[0][q] == 179){
                        strikerLeft = q;
                        break;
                    }
                }
                // If within striker
                if(p->y > strikerLeft && p->y < strikerLeft+10){
                    // if less than 5 balls add 1
                    if(*balls<5){
                        (*balls)++;
                    }
                    // Find first "available" and init it
                    if(b->state == 3){
                        initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
                    }else if(c->state == 3){
                        initBall(c, x1+1, 5+strikerLeft, 0, 0, 0);
                    }else if(d->state == 3){
                        initBall(d, x1+1, 5+strikerLeft, 0, 0, 0);
                    }else if(e->state == 3){
                        initBall(e, x1+1, 5+strikerLeft, 0, 0, 0);
                    }else if(f->state == 3){
                        initBall(f, x1+1, 5+strikerLeft, 0, 0, 0);
                    }
                }
                initPowerUp(p, 5, 5, 0);
                playingField[p->x+1][p->y-1] = 0;
                playingField[p->x][p->y] = 0;
                playingField[p->x+1][p->y+1] = 0;
            }
        }
    }
}

void powerToArray(struct powerUp_t *p, uint8_t playingField[128][32]){
    // Draw the powerup if its alive (vel over 0)
    // only draw it where nothing else is, to prevent problems
    if(p->vel != 0){
        if((p->vel)>0){
            if(playingField[p->x-1][p->y-1] == 0){
                playingField[p->x-1][p->y-1] = 92;
            }
            if(playingField[p->x][p->y] == 0){
                playingField[p->x][p->y] = 62;
            }
            if(playingField[p->x-1][p->y+1] == 0){
                playingField[p->x-1][p->y+1] = 47;
            }
        }else{
            if(playingField[p->x+1][p->y-1] == 0){
                playingField[p->x+1][p->y-1] = 47;
            }
            if(playingField[p->x][p->y] == 0){
                playingField[p->x][p->y] = 60;
            }
            if(playingField[p->x+1][p->y+1] == 0){
                playingField[p->x+1][p->y+1] = 92;
            }
        }
    }
}

void removePowerUpFromArray(struct powerUp_t *p, uint8_t playingField[128][32]) {
    // Remove if it is alive
    if((p->vel)>0){
        if(playingField[p->x-1][p->y-1] == 92){
            playingField[p->x-1][p->y-1] = 0;
        }
        if(playingField[p->x][p->y] == 62){
            playingField[p->x][p->y] = 0;
        }
        if(playingField[p->x-1][p->y+1] == 47){
            playingField[p->x-1][p->y+1] = 0;
        }
    } else {
        if(playingField[p->x+1][p->y-1] == 47){
            playingField[p->x+1][p->y-1] = 0;
        }
        if(playingField[p->x][p->y] == 60){
            playingField[p->x][p->y] = 0;
        }
        if(playingField[p->x+1][p->y+1] == 92){
            playingField[p->x+1][p->y+1] = 0;
        }
    }
}
















