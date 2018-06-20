#include "brick.h"



void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32]){
    uint8_t vChar, hChar, dlcChar, drcChar, tlcChar, trcChar;
    vChar = 179;
    hChar = 196;
    tlcChar = 218;
    trcChar = 191;
    dlcChar = 192;
    drcChar = 217;

    playingField[x][y] = tlcChar;
    playingField[x+1][y] = hChar;
    playingField[x+2][y] = trcChar;
    playingField[x][y+1] = vChar;
    playingField[x+2][y+1] = vChar;
    playingField[x][y+2] = vChar;
    playingField[x+2][y+2] = vChar;
    playingField[x][y+3] = dlcChar;
    playingField[x+1][y+3] = hChar;
    playingField[x+2][y+3] = drcChar;
}

void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks, struct powerUp_t *p, int8_t powerUpLeftOrRight, uint8_t *score) {
    uint8_t i, j, random ;
    random = rand() % 5 + 1;
    if(random == 1 && p->vel == 0){
        initPowerUp(p, x+1, y+1, powerUpLeftOrRight);
    }
    for(i = x; i < x+3; i++){
        for(j = y; j < y+4; j++){
            playingField[i][j] = 0;
        }
    }
    (*bricks)--;
    (*score)++;
}
