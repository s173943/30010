#include "menu.h"

extern uint8_t updateLCD;

void drawLevel(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t bricksx, uint8_t bricksy, uint8_t *bricks){
    for(uint8_t i = 0; i < bricksx; i++){
        for(uint8_t j = 0; j < bricksy; j++){
            drawBrick((x+i*3), (y+j*4), playingField);
            (*bricks)++;
        }
    }
}

void menuTree(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32],uint8_t *menuSettings, uint8_t *menuSettingsCheck, uint16_t *testCount, uint8_t *lives, uint8_t *score, uint8_t *oldx){
    uint8_t x = readJoystick(), menuTrack = 0, selector = 1;

    // If ingame and down is pressed let the menu start again, all is lost though!
    if ((((((*menuSettings) >> 0) & 1) != 0) && (readJoystick() & (0x001 << 1)) && (x != (*oldx))) || (((*menuSettings) >> 6) & 1) != 0) {
        (*menuSettings) &= ~(0x01); // Sets first bit to 0
        (*menuSettingsCheck) = 0; // Sets first bit to 0
        (*menuSettings) &= ~(0x01 << 5); // Reset win
        (*menuSettings) &= ~(0x01 << 6); // Reset lost
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
    }

    /*
    Bit 0: Gamestart = 1
    Bit 1: Single-/2- player
    Bit 2: Easy
    Bit 3: Medium
    Bit 4: Hard
    Bit 5: Won
    Bit 6: Lost
    */

    while((((*menuSettings) >> 0) & 1) == 0){
        x=readJoystick();
        if (menuTrack == 0){
            startMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);

            if (x!=(*oldx)){
                blinkSelect(4,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // Play game
                        case 1:
                            *menuSettings |= (0x0001 << 0);
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            simpleMapToArray(playingField); // Draw edges
                            (*lives) = 3; // Can be set later on?
                            (*score) = 0;
                            break;
                        // Level
                        case 2:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            selector = 1;
                            menuTrack = 2;
                            break;
                        // Mode
                        case 3:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            selector = 1;
                            menuTrack = 3;
                            break;
                        case 4:
                        // Help
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            selector = 1;
                            menuTrack = 4;
                            break;
                    }
                }
                (*oldx) = x;
            }
        }
        // Level/Difficulty menu
        else if (menuTrack == 2){
            levelMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);
            if (x!=(*oldx)){
                blinkSelect(3,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // Difficulty Easy
                        case 1:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            (*menuSettings) |= (0x0001 << 2);
                            menuTrack = 0;
                            selector = 1;
                            break;
                        // Difficulty Medium
                        case 2:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            (*menuSettings) |= (0x0001 << 3);
                            menuTrack = 0;
                            selector = 1;
                            break;
                        // Difficulty Hard
                        case 3:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            (*menuSettings) |= (0x0001 << 4);
                            menuTrack = 0;
                            selector = 1;
                            break;
                    }
                }
                (*oldx) = x;
            }
        }
        // Mode menu
        else if (menuTrack == 3){
            modeMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);

            if (x!=(*oldx)){
                blinkSelect(2,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // One player
                        case 1:
                            *menuSettings |= (0x0001 << 1);
                            //*playerMode = 1;
                            menuTrack = 0;
                            selector = 1;
                            break;
                        // Two player
                        case 2:
                            *menuSettings |= (0x0000 << 1);
                            //*playerMode = 2;
                            menuTrack = 0;
                            selector = 1;
                            break;
                    }
                    memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                }
                (*oldx) = x;
            }
        }
        // Help menu
        else if (menuTrack == 4){
            helpMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);
            if (x!=(*oldx)){
                blinkSelect(1,&selector);
                if((readJoystick()>>4)&1){
                    menuTrack = 0;
                    memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                }
                (*oldx) = x;
            }
        }
        *testCount = *testCount +1;
    }
}

void youLoseScreen(uint8_t a[128][32], uint8_t score) {
    memset(a, 0x00, sizeof (uint8_t) * 128 * 32);
    youLose(a, 37, 8, score);
    drawWindowFromArray(a);
    convertArrayToBuffer(a);
    lcd_push_buffer(lcdArray);

    while ((readJoystick() & (0x01 << 4)) != (0x01 << 4));
}

void interpretMenuSettings(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32], uint8_t menuSettings, uint8_t * menuSettingsCheck, uint8_t *bricks) {
    if ((menuSettings & 0x04) == 0x04 && ((*menuSettingsCheck) & 0x04) != 0x04) { // Easy
        setSpeed(10);
        drawLevel(playingField, 34, 2, 10, 7, bricks);
        (*menuSettingsCheck) |= 0x04;
    } else if ((menuSettings & 0x08) == 0x08 && ((*menuSettingsCheck) & 0x08) != 0x08) { // Medium
        setSpeed(5);
        drawLevel(playingField, 25, 2, 16, 7, bricks);
        (*menuSettingsCheck) |= 0x08;
    } else if ((menuSettings & 0x10) == 0x10 && ((*menuSettingsCheck) & 0x10) != 0x10) { // Hard
        setSpeed(2);
        drawLevel(playingField, 16, 2, 22, 7, bricks);
        (*menuSettingsCheck) |= 0x10;
    }
}

void clearPartOfArray(uint8_t playingField[128][32], uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t i, j;
    for (i = x1; i <= (x1+x2); i++) {
        for (j = y1; j <= (y1+y2); j++) {
            playingField[i][j] = 0;
        }
    }
}

void copyArray(uint8_t * playingField, uint8_t * oldPlayingField) {
    uint16_t i;
    for (i = 0; i < 4096; i++) { // 128 * 32 = 4096
        oldPlayingField[i] = playingField[i];
    }
}

void bossKeyEN(uint8_t *workorPay, uint8_t playingField[128][32], uint8_t oldPlayingField[128][32], uint8_t *oldx){
    uint8_t x = readJoystick();

    if ((*oldx)!=x){
        if(*workorPay == 0){
            if(readJoystick() & (0x01 << 4)){
                copyArray(*playingField, *oldPlayingField);
                memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                setFreq(0);
                *workorPay = 1;
            }
            (*oldx) = x;
        }
        while(*workorPay == 1){
            x = readJoystick();
            bossKey(playingField,0,0);
            drawWindowFromArray(playingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);

            if(x & (0x01 << 4) && (*oldx)!=x){
                memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                drawWindowFromArray(playingField);
                copyArray(*oldPlayingField,*playingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);
                *workorPay = 0;
            }
            (*oldx) = x;
        }
        (*oldx) = x;
    }
}

void livesToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t lives) {
    uint8_t i;
    lives = (lives > 4)?4:lives; // if more than four only display four
    clearPartOfArray(playingField, x, y, 17, 14);
    for (i = 0; i < lives; i++) {
        if (i % 2 == 0) {
            drawHeart(playingField, (x), (y + (i * 4)) );
        } else {
            drawHeart(playingField, (x + 9), (y + (i * (i==1?0:4)) - (i==1?0:4)) );
        }
    }
}

void scoreToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t score) {
    drawScore(playingField, x, y);
    clearPartOfArray(playingField, x+5, y+8, 17, 7);
    numberWrite(playingField, x+5, y+8, score);
}

void drawHeart(uint8_t a[128][32], uint8_t x, uint8_t y) {
    a[x+1][y] = BLOCK;
    a[x+2][y] = BLOCK;
    a[x+5][y] = BLOCK;
    a[x+6][y] = BLOCK;
    a[x+0][y+1] = BLOCK;
    a[x+3][y+1] = BLOCK;
    a[x+4][y+1] = BLOCK;
    a[x+7][y+1] = BLOCK;
    a[x+0][y+2] = BLOCK;
    a[x+7][y+2] = BLOCK;
    a[x+0][y+3] = BLOCK;
    a[x+7][y+3] = BLOCK;
    a[x+1][y+4] = BLOCK;
    a[x+6][y+4] = BLOCK;
    a[x+2][y+5] = BLOCK;
    a[x+5][y+5] = BLOCK;
    a[x+3][y+6] = BLOCK;
    a[x+4][y+6] = BLOCK;
}

void drawScore(uint8_t a[128][32], uint8_t x, uint8_t y) {
    a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+1][y+3] = BLOCK;
	a[x+1][y+6] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+3] = BLOCK;
	a[x+2][y+6] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+3][y+5] = BLOCK;
	a[x+5][y+2] = BLOCK;
	a[x+5][y+3] = BLOCK;
	a[x+5][y+4] = BLOCK;
	a[x+5][y+5] = BLOCK;
	a[x+6][y+1] = BLOCK;
	a[x+6][y+6] = BLOCK;
	a[x+7][y+1] = BLOCK;
	a[x+7][y+6] = BLOCK;
	a[x+8][y+1] = BLOCK;
	a[x+8][y+6] = BLOCK;
	a[x+10][y+2] = BLOCK;
	a[x+10][y+3] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+5] = BLOCK;
	a[x+11][y+1] = BLOCK;
	a[x+11][y+6] = BLOCK;
	a[x+12][y+1] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+13][y+1] = BLOCK;
	a[x+13][y+6] = BLOCK;
	a[x+14][y+2] = BLOCK;
	a[x+14][y+3] = BLOCK;
	a[x+14][y+4] = BLOCK;
	a[x+14][y+5] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+5] = BLOCK;
	a[x+16][y+6] = BLOCK;
	a[x+17][y+1] = BLOCK;
	a[x+18][y+1] = BLOCK;
	a[x+19][y+1] = BLOCK;
	a[x+21][y+2] = BLOCK;
	a[x+21][y+3] = BLOCK;
	a[x+21][y+4] = BLOCK;
	a[x+21][y+5] = BLOCK;
	a[x+22][y+1] = BLOCK;
	a[x+22][y+4] = BLOCK;
	a[x+22][y+6] = BLOCK;
	a[x+23][y+1] = BLOCK;
	a[x+23][y+4] = BLOCK;
	a[x+23][y+6] = BLOCK;
	a[x+24][y+2] = BLOCK;
	a[x+24][y+3] = BLOCK;
}

void simpleMapToArray(uint8_t playingField[128][32]){
    // 196 Horizontal line, 179 Vertical line.
    uint8_t i;
    for (i = 0; i <= 100; i++) {
        playingField[i][0] = 196;
        playingField[i][31] = 196;
    }
}

void helpMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){
    helpscreen(playingField, 0, 0);
}

void levelMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){
    menuSquare(playingField, 3,2, 40,29, 1, selector, testCount);
    level_easy(playingField,5,4);

    menuSquare(playingField, 44,2, 81,29, 2, selector, testCount);
    level_medium(playingField,46,4);

    menuSquare(playingField, 85,2, 122,29, 3, selector, testCount);
    level_hard(playingField,87,4);
}

void modeMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){
    menuSquare(playingField, 3,2, 28,29, 1, selector, testCount);
    sanik(playingField,6,5);

    menuSquare(playingField, 32,2, 90,29, 2,selector, testCount);
    sanik(playingField, 35,5);
    ugandanKnuckles(playingField,59,4);
}

void startMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){

    menuSquare(playingField, 3,2, 29,13, 1, selector, testCount); //play
    play(playingField, 5,4);

    menuSquare(playingField, 33,2, 65,13, 2, selector, testCount); //level
    level(playingField, 35,4);

    menuSquare(playingField, 3,17, 29,28, 3, selector, testCount); //mode
    mode(playingField, 5,19);

    menuSquare(playingField, 33,17, 59,28, 4, selector, testCount); //mode
    help(playingField,35,19);

    logo(playingField,74,2);

    convertArrayToBuffer(playingField);
    lcd_push_buffer(lcdArray);

}

void blinkSelect(uint8_t maxWindows, uint8_t * selector){

    if((readJoystick()>>3)&1){
        *selector = *selector + 1;
        if (*selector >= maxWindows+1){
            *selector = 1;
        }
    }
    else if((readJoystick()>>2)&1){
        *selector = *selector - 1;
        if (*selector <= 0){
            *selector = maxWindows;
        }
    }
    if(maxWindows == 4){
        if((readJoystick() >> 0) & 1){
            if (*selector+2 == 5){
                *selector = 1;
            }
            else if(*selector+2 == 6){
                *selector = 2;
            }
            else{
                *selector = *selector + 2;
            }
        }
        if((readJoystick() >> 1) & 1){
            if (*selector-2 == -1){
                *selector = 3;
            }
            else if(*selector-2 == 0){
                *selector = 4;
            }
            else{
                *selector = *selector -2;
            }
        }
    }
}

void menuSquare(uint8_t playingField[128][32], int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t val, int8_t selector, uint16_t *testCount){
    uint8_t i;
    if (val == selector){
        if(*testCount == 20){
            for(i = y1; i <= y2; i++){
                playingField[x1][i] = 0;
                playingField[x2][i] = 0;
            }
            for(i = x1; i <= x2; i++){
                playingField[i][y1] = 0;
                playingField[i][y2] = 0;
            }

        }
        else if(*testCount == 40){
            for(i = y1; i <= y2; i++){
                playingField[x1][i] = 179;
                playingField[x2][i] = 179;
            }
            for(i = x1; i <= x2; i++){
                playingField[i][y1] = 95;
                playingField[i][y2] = 95;
            }
        }
        else if (*testCount == 60){
            *testCount = 0;
        }
    }

    else{
        for(i = y1; i <= y2; i++){
            playingField[x1][i] = 179;
            playingField[x2][i] = 179;
        }
        for(i = x1; i <= x2; i++){
            playingField[i][y1] = 95;
            playingField[i][y2] = 95;
        }
    }
}

void help(uint8_t a[128][32], uint8_t x, uint8_t y){
    a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+1][y+4] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+1] = BLOCK;
	a[x+4][y+2] = BLOCK;
	a[x+4][y+3] = BLOCK;
	a[x+4][y+4] = BLOCK;
	a[x+4][y+5] = BLOCK;
	a[x+4][y+6] = BLOCK;
	a[x+4][y+7] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+1] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+6] = BLOCK;
	a[x+6][y+7] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+3] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+3] = BLOCK;
	a[x+8][y+7] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+3] = BLOCK;
	a[x+9][y+7] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+3] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+1] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+13][y+7] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+15][y+7] = BLOCK;
	a[x+16][y+7] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+1] = BLOCK;
	a[x+18][y+2] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+5] = BLOCK;
	a[x+18][y+6] = BLOCK;
	a[x+18][y+7] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+4] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+4] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+4] = BLOCK;
	a[x+22][y+1] = BLOCK;
	a[x+22][y+2] = BLOCK;
	a[x+22][y+3] = BLOCK;
}

void mode(uint8_t a[128][32], uint8_t x, uint8_t y){
	a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+1][y+1] = BLOCK;
	a[x+2][y+2] = BLOCK;
	a[x+2][y+3] = BLOCK;
	a[x+3][y+1] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+1] = BLOCK;
	a[x+4][y+2] = BLOCK;
	a[x+4][y+3] = BLOCK;
	a[x+4][y+4] = BLOCK;
	a[x+4][y+5] = BLOCK;
	a[x+4][y+6] = BLOCK;
	a[x+4][y+7] = BLOCK;
	a[x+6][y+1] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+6] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+7] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+7] = BLOCK;
	a[x+10][y+1] = BLOCK;
	a[x+10][y+2] = BLOCK;
	a[x+10][y+3] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+5] = BLOCK;
	a[x+10][y+6] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+1] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+13][y+0] = BLOCK;
	a[x+13][y+7] = BLOCK;
	a[x+14][y+0] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+15][y+0] = BLOCK;
	a[x+15][y+7] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+5] = BLOCK;
	a[x+16][y+6] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+1] = BLOCK;
	a[x+18][y+2] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+5] = BLOCK;
	a[x+18][y+6] = BLOCK;
	a[x+18][y+7] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+3] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+3] = BLOCK;
	a[x+20][y+7] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+3] = BLOCK;
	a[x+21][y+7] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+3] = BLOCK;
	a[x+22][y+7] = BLOCK;
}

void level(uint8_t a[128][32], uint8_t x, uint8_t y){
    a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+1][y+7] = BLOCK;
	a[x+2][y+7] = BLOCK;
	a[x+3][y+7] = BLOCK;
	a[x+4][y+7] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+1] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+6] = BLOCK;
	a[x+6][y+7] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+3] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+3] = BLOCK;
	a[x+8][y+7] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+3] = BLOCK;
	a[x+9][y+7] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+3] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+1] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+13][y+5] = BLOCK;
	a[x+13][y+6] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+15][y+5] = BLOCK;
	a[x+15][y+6] = BLOCK;
	a[x+16][y+0] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+1] = BLOCK;
	a[x+18][y+2] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+5] = BLOCK;
	a[x+18][y+6] = BLOCK;
	a[x+18][y+7] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+3] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+3] = BLOCK;
	a[x+20][y+7] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+3] = BLOCK;
	a[x+21][y+7] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+3] = BLOCK;
	a[x+22][y+7] = BLOCK;
	a[x+24][y+0] = BLOCK;
	a[x+24][y+1] = BLOCK;
	a[x+24][y+2] = BLOCK;
	a[x+24][y+3] = BLOCK;
	a[x+24][y+4] = BLOCK;
	a[x+24][y+5] = BLOCK;
	a[x+24][y+6] = BLOCK;
	a[x+24][y+7] = BLOCK;
	a[x+25][y+7] = BLOCK;
	a[x+26][y+7] = BLOCK;
	a[x+27][y+7] = BLOCK;
	a[x+28][y+7] = BLOCK;
}

void play(uint8_t a[128][32], uint8_t x, uint8_t y){
    a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+1][y+4] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+4][y+1] = BLOCK;
	a[x+4][y+2] = BLOCK;
	a[x+4][y+3] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+1] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+6] = BLOCK;
	a[x+6][y+7] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+8][y+7] = BLOCK;
	a[x+9][y+7] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+12][y+1] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+13][y+0] = BLOCK;
	a[x+13][y+3] = BLOCK;
	a[x+14][y+0] = BLOCK;
	a[x+14][y+3] = BLOCK;
	a[x+15][y+0] = BLOCK;
	a[x+15][y+3] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+5] = BLOCK;
	a[x+16][y+6] = BLOCK;
	a[x+16][y+7] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+1] = BLOCK;
	a[x+19][y+2] = BLOCK;
	a[x+20][y+3] = BLOCK;
	a[x+20][y+4] = BLOCK;
	a[x+20][y+5] = BLOCK;
	a[x+20][y+6] = BLOCK;
	a[x+20][y+7] = BLOCK;
	a[x+21][y+2] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+1] = BLOCK;

}

void drawLine(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t length, uint8_t height) {
    uint8_t i, j;

    for (i = x; i < x+length; i++) {
        for (j = y; j < y+height; j++) {
            a[i][j] = BLOCK;
        }
    }
}

void level_hard(uint8_t a[128][32], uint8_t x, uint8_t y){
    drawLine(a, x+7, y+3, 3, 18); // Vertical line in the H
    drawLine(a, x+24, y+3, 3, 18); // Vertical line in the H
    drawLine(a, x+10, y+10, 14, 3); // Horizontal line in the H
}

void level_medium(uint8_t a[128][32], uint8_t x, uint8_t y){
    drawLine(a, x+7, y+3, 3, 18);
    drawLine(a, x+24, y+3, 3, 18);
    // Diagonal lines
    drawLine(a, x+10, y+3, 1, 4);
    drawLine(a, x+11, y+4, 1, 4);
    drawLine(a, x+12, y+5, 1, 4);
    drawLine(a, x+13, y+6, 1, 4);
    drawLine(a, x+14, y+7, 1, 4);
    drawLine(a, x+15, y+8, 1, 4);
    drawLine(a, x+16, y+9, 2, 4); // Middle
    drawLine(a, x+18, y+8, 1, 4);
    drawLine(a, x+19, y+7, 1, 4);
    drawLine(a, x+20, y+6, 1, 4);
    drawLine(a, x+21, y+5, 1, 4);
    drawLine(a, x+22, y+4, 1, 4);
    drawLine(a, x+23, y+3, 1, 4);
}

void level_easy(uint8_t a[128][32], uint8_t x, uint8_t y){
    drawLine(a, x+10, y+3, 3, 18);
    drawLine(a, x+13, y+3, 10, 3);
    drawLine(a, x+13, y+18, 10, 3);
    drawLine(a, x+13, y+10, 7, 4);
}

void ugandanKnuckles(uint8_t a[128][32], uint8_t x, uint8_t y) {
    uint8_t yoffset = 0;
    // 0
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    yoffset++;

    a[x+11][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    yoffset++;

    a[x+9][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    yoffset++;

    a[x+8][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    yoffset++;

    a[x+7][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    yoffset++;

    // 5
    a[x+6][y+yoffset] = BLOCK;
    a[x+23][y+yoffset] = BLOCK;
    yoffset++;

    a[x+5][y+yoffset] = BLOCK;
    a[x+24][y+yoffset] = BLOCK;
    yoffset++;

    a[x+4][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+25][y+yoffset] = BLOCK;
    yoffset++;

    a[x+2][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+26][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+26][y+yoffset] = BLOCK;
    yoffset++;

    // 10
    a[x+0][y+yoffset] = BLOCK;
    a[x+1][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+7][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+26][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+1][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+27][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    a[x+27][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    a[x+28][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    a[x+28][y+yoffset] = BLOCK;
    yoffset++;

    // 15
    a[x+1][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+7][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    a[x+28][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+27][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+24][y+yoffset] = BLOCK;
    a[x+27][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+7][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+23][y+yoffset] = BLOCK;
    a[x+27][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+23][y+yoffset] = BLOCK;
    a[x+26][y+yoffset] = BLOCK;
    yoffset++;

    // 20
    a[x+2][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+23][y+yoffset] = BLOCK;
    a[x+26][y+yoffset] = BLOCK;
    yoffset++;

    a[x+3][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    a[x+23][y+yoffset] = BLOCK;
    a[x+24][y+yoffset] = BLOCK;
    a[x+25][y+yoffset] = BLOCK;
    yoffset++;

    a[x+7][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+21][y+yoffset] = BLOCK;
    a[x+24][y+yoffset] = BLOCK;
    yoffset++;

    a[x+8][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    a[x+22][y+yoffset] = BLOCK;
    a[x+24][y+yoffset] = BLOCK;
}

void sanik(uint8_t a[128][32], uint8_t x, uint8_t y) {
    uint8_t yoffset = 0;
    // 0
    a[x+1][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+1][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+6][y+yoffset] = BLOCK;
    a[x+7][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    yoffset++;

    a[x+0][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+4][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    a[x+19][y+yoffset] = BLOCK;
    a[x+20][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+2][y+yoffset] = BLOCK;
    a[x+3][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    yoffset++;

    a[x+1][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    yoffset++;

    a[x+2][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+12][y+yoffset] = BLOCK;
    a[x+13][y+yoffset] = BLOCK;
    a[x+14][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    yoffset++;

    a[x+3][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    a[x+11][y+yoffset] = BLOCK;
    a[x+15][y+yoffset] = BLOCK;
    a[x+16][y+yoffset] = BLOCK;
    a[x+17][y+yoffset] = BLOCK;
    a[x+18][y+yoffset] = BLOCK;
    yoffset++;

    a[x+4][y+yoffset] = BLOCK;
    a[x+5][y+yoffset] = BLOCK;
    a[x+10][y+yoffset] = BLOCK;
    yoffset++;

    a[x+6][y+yoffset] = BLOCK;
    a[x+7][y+yoffset] = BLOCK;
    a[x+8][y+yoffset] = BLOCK;
    a[x+9][y+yoffset] = BLOCK;
}

void logo(uint8_t a[128][32], uint8_t x, uint8_t y){
    a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+1][y+1] = BLOCK;
	a[x+1][y+5] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+6] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+7] = BLOCK;
	a[x+3][y+15] = BLOCK;
	a[x+3][y+25] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+8] = BLOCK;
	a[x+4][y+14] = BLOCK;
	a[x+4][y+15] = BLOCK;
	a[x+4][y+25] = BLOCK;
	a[x+5][y+1] = BLOCK;
	a[x+5][y+9] = BLOCK;
	a[x+5][y+13] = BLOCK;
	a[x+5][y+14] = BLOCK;
	a[x+5][y+15] = BLOCK;
	a[x+5][y+25] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+12] = BLOCK;
	a[x+6][y+15] = BLOCK;
	a[x+6][y+25] = BLOCK;
	a[x+7][y+1] = BLOCK;
	a[x+7][y+9] = BLOCK;
	a[x+7][y+11] = BLOCK;
	a[x+7][y+15] = BLOCK;
	a[x+7][y+25] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+8] = BLOCK;
	a[x+8][y+10] = BLOCK;
	a[x+8][y+11] = BLOCK;
	a[x+8][y+15] = BLOCK;
	a[x+8][y+25] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+7] = BLOCK;
	a[x+9][y+9] = BLOCK;
	a[x+9][y+11] = BLOCK;
	a[x+9][y+15] = BLOCK;
	a[x+9][y+24] = BLOCK;
	a[x+9][y+25] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+6] = BLOCK;
	a[x+10][y+8] = BLOCK;
	a[x+10][y+11] = BLOCK;
	a[x+10][y+12] = BLOCK;
	a[x+10][y+13] = BLOCK;
	a[x+10][y+14] = BLOCK;
	a[x+10][y+15] = BLOCK;
	a[x+10][y+23] = BLOCK;
	a[x+10][y+25] = BLOCK;
	a[x+11][y+1] = BLOCK;
	a[x+11][y+5] = BLOCK;
	a[x+11][y+7] = BLOCK;
	a[x+11][y+8] = BLOCK;
	a[x+11][y+11] = BLOCK;
	a[x+11][y+15] = BLOCK;
	a[x+11][y+22] = BLOCK;
	a[x+11][y+25] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+8] = BLOCK;
	a[x+12][y+9] = BLOCK;
	a[x+12][y+10] = BLOCK;
	a[x+12][y+11] = BLOCK;
	a[x+12][y+15] = BLOCK;
	a[x+12][y+21] = BLOCK;
	a[x+12][y+25] = BLOCK;
	a[x+13][y+5] = BLOCK;
	a[x+13][y+8] = BLOCK;
	a[x+13][y+11] = BLOCK;
	a[x+13][y+15] = BLOCK;
	a[x+13][y+19] = BLOCK;
	a[x+14][y+5] = BLOCK;
	a[x+14][y+6] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+14][y+8] = BLOCK;
	a[x+14][y+11] = BLOCK;
	a[x+14][y+15] = BLOCK;
	a[x+14][y+18] = BLOCK;
	a[x+14][y+20] = BLOCK;
	a[x+15][y+2] = BLOCK;
	a[x+15][y+3] = BLOCK;
	a[x+15][y+5] = BLOCK;
	a[x+15][y+8] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+14] = BLOCK;
	a[x+15][y+15] = BLOCK;
	a[x+15][y+19] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+5] = BLOCK;
	a[x+16][y+8] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+15] = BLOCK;
	a[x+17][y+1] = BLOCK;
	a[x+17][y+3] = BLOCK;
	a[x+17][y+4] = BLOCK;
	a[x+17][y+5] = BLOCK;
	a[x+17][y+8] = BLOCK;
	a[x+17][y+9] = BLOCK;
	a[x+17][y+10] = BLOCK;
	a[x+17][y+11] = BLOCK;
	a[x+17][y+15] = BLOCK;
	a[x+18][y+5] = BLOCK;
	a[x+18][y+8] = BLOCK;
	a[x+18][y+11] = BLOCK;
	a[x+18][y+15] = BLOCK;
	a[x+19][y+2] = BLOCK;
	a[x+19][y+3] = BLOCK;
	a[x+19][y+4] = BLOCK;
	a[x+19][y+5] = BLOCK;
	a[x+19][y+6] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+19][y+8] = BLOCK;
	a[x+19][y+11] = BLOCK;
	a[x+19][y+15] = BLOCK;
	a[x+20][y+1] = BLOCK;
	a[x+20][y+5] = BLOCK;
	a[x+20][y+8] = BLOCK;
	a[x+20][y+11] = BLOCK;
	a[x+20][y+12] = BLOCK;
	a[x+20][y+13] = BLOCK;
	a[x+20][y+14] = BLOCK;
	a[x+20][y+15] = BLOCK;
	a[x+21][y+1] = BLOCK;
	a[x+21][y+5] = BLOCK;
	a[x+21][y+8] = BLOCK;
	a[x+21][y+11] = BLOCK;
	a[x+21][y+15] = BLOCK;
	a[x+22][y+5] = BLOCK;
	a[x+22][y+8] = BLOCK;
	a[x+22][y+9] = BLOCK;
	a[x+22][y+10] = BLOCK;
	a[x+22][y+11] = BLOCK;
	a[x+22][y+15] = BLOCK;
	a[x+23][y+2] = BLOCK;
	a[x+23][y+3] = BLOCK;
	a[x+23][y+5] = BLOCK;
	a[x+23][y+8] = BLOCK;
	a[x+23][y+11] = BLOCK;
	a[x+23][y+15] = BLOCK;
	a[x+24][y+1] = BLOCK;
	a[x+24][y+4] = BLOCK;
	a[x+24][y+5] = BLOCK;
	a[x+24][y+6] = BLOCK;
	a[x+24][y+7] = BLOCK;
	a[x+24][y+8] = BLOCK;
	a[x+24][y+11] = BLOCK;
	a[x+24][y+15] = BLOCK;
	a[x+24][y+22] = BLOCK;
	a[x+25][y+1] = BLOCK;
	a[x+25][y+4] = BLOCK;
	a[x+25][y+5] = BLOCK;
	a[x+25][y+8] = BLOCK;
	a[x+25][y+11] = BLOCK;
	a[x+25][y+12] = BLOCK;
	a[x+25][y+13] = BLOCK;
	a[x+25][y+14] = BLOCK;
	a[x+25][y+15] = BLOCK;
	a[x+25][y+21] = BLOCK;
	a[x+25][y+23] = BLOCK;
	a[x+26][y+2] = BLOCK;
	a[x+26][y+3] = BLOCK;
	a[x+26][y+5] = BLOCK;
	a[x+26][y+8] = BLOCK;
	a[x+26][y+11] = BLOCK;
	a[x+26][y+15] = BLOCK;
	a[x+26][y+22] = BLOCK;
	a[x+27][y+5] = BLOCK;
	a[x+27][y+8] = BLOCK;
	a[x+27][y+9] = BLOCK;
	a[x+27][y+10] = BLOCK;
	a[x+27][y+11] = BLOCK;
	a[x+27][y+15] = BLOCK;
	a[x+27][y+20] = BLOCK;
	a[x+28][y+1] = BLOCK;
	a[x+28][y+2] = BLOCK;
	a[x+28][y+3] = BLOCK;
	a[x+28][y+5] = BLOCK;
	a[x+28][y+8] = BLOCK;
	a[x+28][y+11] = BLOCK;
	a[x+28][y+15] = BLOCK;
	a[x+28][y+19] = BLOCK;
	a[x+29][y+4] = BLOCK;
	a[x+29][y+5] = BLOCK;
	a[x+29][y+6] = BLOCK;
	a[x+29][y+7] = BLOCK;
	a[x+29][y+8] = BLOCK;
	a[x+29][y+11] = BLOCK;
	a[x+29][y+15] = BLOCK;
	a[x+29][y+18] = BLOCK;
	a[x+30][y+1] = BLOCK;
	a[x+30][y+2] = BLOCK;
	a[x+30][y+3] = BLOCK;
	a[x+30][y+5] = BLOCK;
	a[x+30][y+8] = BLOCK;
	a[x+30][y+11] = BLOCK;
	a[x+30][y+12] = BLOCK;
	a[x+30][y+13] = BLOCK;
	a[x+30][y+14] = BLOCK;
	a[x+30][y+15] = BLOCK;
	a[x+31][y+5] = BLOCK;
	a[x+31][y+8] = BLOCK;
	a[x+31][y+11] = BLOCK;
	a[x+31][y+14] = BLOCK;
	a[x+31][y+17] = BLOCK;
	a[x+32][y+1] = BLOCK;
	a[x+32][y+2] = BLOCK;
	a[x+32][y+3] = BLOCK;
	a[x+32][y+4] = BLOCK;
	a[x+32][y+5] = BLOCK;
	a[x+32][y+8] = BLOCK;
	a[x+32][y+9] = BLOCK;
	a[x+32][y+10] = BLOCK;
	a[x+32][y+11] = BLOCK;
	a[x+32][y+13] = BLOCK;
	a[x+32][y+16] = BLOCK;
	a[x+32][y+17] = BLOCK;
	a[x+33][y+1] = BLOCK;
	a[x+33][y+3] = BLOCK;
	a[x+33][y+5] = BLOCK;
	a[x+33][y+8] = BLOCK;
	a[x+33][y+11] = BLOCK;
	a[x+33][y+12] = BLOCK;
	a[x+33][y+15] = BLOCK;
	a[x+33][y+17] = BLOCK;
	a[x+34][y+1] = BLOCK;
	a[x+34][y+2] = BLOCK;
	a[x+34][y+3] = BLOCK;
	a[x+34][y+5] = BLOCK;
	a[x+34][y+6] = BLOCK;
	a[x+34][y+7] = BLOCK;
	a[x+34][y+8] = BLOCK;
	a[x+34][y+10] = BLOCK;
	a[x+34][y+11] = BLOCK;
	a[x+34][y+14] = BLOCK;
	a[x+34][y+15] = BLOCK;
	a[x+34][y+17] = BLOCK;
	a[x+35][y+5] = BLOCK;
	a[x+35][y+8] = BLOCK;
	a[x+35][y+9] = BLOCK;
	a[x+35][y+10] = BLOCK;
	a[x+35][y+13] = BLOCK;
	a[x+35][y+15] = BLOCK;
	a[x+35][y+17] = BLOCK;
	a[x+36][y+5] = BLOCK;
	a[x+36][y+6] = BLOCK;
	a[x+36][y+7] = BLOCK;
	a[x+36][y+8] = BLOCK;
	a[x+36][y+9] = BLOCK;
	a[x+36][y+12] = BLOCK;
	a[x+36][y+13] = BLOCK;
	a[x+36][y+14] = BLOCK;
	a[x+36][y+15] = BLOCK;
	a[x+36][y+16] = BLOCK;
	a[x+36][y+17] = BLOCK;
	a[x+37][y+1] = BLOCK;
	a[x+38][y+1] = BLOCK;
	a[x+38][y+2] = BLOCK;
	a[x+38][y+3] = BLOCK;
	a[x+38][y+4] = BLOCK;
	a[x+38][y+5] = BLOCK;
	a[x+40][y+1] = BLOCK;
	a[x+40][y+3] = BLOCK;
	a[x+40][y+5] = BLOCK;
	a[x+41][y+1] = BLOCK;
	a[x+41][y+3] = BLOCK;
	a[x+41][y+5] = BLOCK;
	a[x+42][y+2] = BLOCK;
	a[x+42][y+4] = BLOCK;

}

void youLose(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t score){
    charToArray(a, x+3, y+0, 'Y');
    charToArray(a, x+9, y+0, 'O');
    charToArray(a, x+15, y+0, 'U');

    charToArray(a, x+27, y+0, 'L');
    charToArray(a, x+33, y+0, 'O');
    charToArray(a, x+38, y+0, 'S');
    charToArray(a, x+45, y+0, 'E');

    charToArray(a, x, y+8, 'S');
    charToArray(a, x+6, y+8, 'C');
    charToArray(a, x+12, y+8, 'O');
    charToArray(a, x+18, y+8, 'R');
    charToArray(a, x+24, y+8, 'E');

    numberWrite(a, x+37, y+8, score);
}

void youWin(uint8_t a[128][32], uint8_t x, uint8_t y){
    a[x+2][y+7] = BLOCK;
	a[x+3][y+8] = BLOCK;
	a[x+3][y+9] = BLOCK;
	a[x+4][y+10] = BLOCK;
	a[x+4][y+11] = BLOCK;
	a[x+4][y+12] = BLOCK;
	a[x+4][y+13] = BLOCK;
	a[x+5][y+8] = BLOCK;
	a[x+5][y+9] = BLOCK;
	a[x+6][y+7] = BLOCK;
	a[x+7][y+10] = BLOCK;
	a[x+7][y+11] = BLOCK;
	a[x+7][y+12] = BLOCK;
	a[x+8][y+9] = BLOCK;
	a[x+8][y+13] = BLOCK;
	a[x+9][y+9] = BLOCK;
	a[x+9][y+13] = BLOCK;
	a[x+10][y+10] = BLOCK;
	a[x+10][y+11] = BLOCK;
	a[x+10][y+12] = BLOCK;
	a[x+10][y+18] = BLOCK;
	a[x+10][y+19] = BLOCK;
	a[x+11][y+20] = BLOCK;
	a[x+11][y+21] = BLOCK;
	a[x+11][y+22] = BLOCK;
	a[x+12][y+9] = BLOCK;
	a[x+12][y+10] = BLOCK;
	a[x+12][y+11] = BLOCK;
	a[x+12][y+12] = BLOCK;
	a[x+12][y+13] = BLOCK;
	a[x+12][y+18] = BLOCK;
	a[x+12][y+19] = BLOCK;
	a[x+13][y+13] = BLOCK;
	a[x+14][y+13] = BLOCK;
	a[x+14][y+20] = BLOCK;
	a[x+14][y+21] = BLOCK;
	a[x+15][y+9] = BLOCK;
	a[x+15][y+10] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+19] = BLOCK;
	a[x+15][y+22] = BLOCK;
	a[x+16][y+9] = BLOCK;
	a[x+16][y+10] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+12] = BLOCK;
	a[x+16][y+13] = BLOCK;
	a[x+16][y+19] = BLOCK;
	a[x+16][y+22] = BLOCK;
	a[x+17][y+20] = BLOCK;
	a[x+17][y+21] = BLOCK;
	a[x+19][y+9] = BLOCK;
	a[x+19][y+19] = BLOCK;
	a[x+19][y+20] = BLOCK;
	a[x+19][y+21] = BLOCK;
	a[x+19][y+22] = BLOCK;
	a[x+20][y+10] = BLOCK;
	a[x+20][y+11] = BLOCK;
	a[x+20][y+12] = BLOCK;
	a[x+20][y+22] = BLOCK;
	a[x+21][y+12] = BLOCK;
	a[x+21][y+13] = BLOCK;
	a[x+21][y+19] = BLOCK;
	a[x+21][y+20] = BLOCK;
	a[x+21][y+21] = BLOCK;
	a[x+21][y+22] = BLOCK;
	a[x+22][y+9] = BLOCK;
	a[x+22][y+10] = BLOCK;
	a[x+22][y+11] = BLOCK;
	a[x+23][y+9] = BLOCK;
	a[x+23][y+10] = BLOCK;
	a[x+23][y+11] = BLOCK;
	a[x+23][y+19] = BLOCK;
	a[x+23][y+20] = BLOCK;
	a[x+23][y+21] = BLOCK;
	a[x+23][y+22] = BLOCK;
	a[x+24][y+12] = BLOCK;
	a[x+24][y+13] = BLOCK;
	a[x+24][y+19] = BLOCK;
	a[x+25][y+10] = BLOCK;
	a[x+25][y+11] = BLOCK;
	a[x+25][y+12] = BLOCK;
	a[x+26][y+9] = BLOCK;
	a[x+27][y+19] = BLOCK;
	a[x+27][y+20] = BLOCK;
	a[x+27][y+22] = BLOCK;
	a[x+28][y+7] = BLOCK;
	a[x+28][y+9] = BLOCK;
	a[x+28][y+10] = BLOCK;
	a[x+28][y+11] = BLOCK;
	a[x+28][y+12] = BLOCK;
	a[x+28][y+13] = BLOCK;
	a[x+28][y+19] = BLOCK;
	a[x+28][y+21] = BLOCK;
	a[x+28][y+22] = BLOCK;
	a[x+30][y+20] = BLOCK;
	a[x+30][y+21] = BLOCK;
	a[x+30][y+22] = BLOCK;
	a[x+31][y+9] = BLOCK;
	a[x+31][y+10] = BLOCK;
	a[x+31][y+11] = BLOCK;
	a[x+31][y+12] = BLOCK;
	a[x+31][y+13] = BLOCK;
	a[x+31][y+19] = BLOCK;
	a[x+31][y+22] = BLOCK;
	a[x+32][y+9] = BLOCK;
	a[x+32][y+19] = BLOCK;
	a[x+32][y+22] = BLOCK;
	a[x+33][y+9] = BLOCK;
	a[x+34][y+10] = BLOCK;
	a[x+34][y+11] = BLOCK;
	a[x+34][y+12] = BLOCK;
	a[x+34][y+13] = BLOCK;
	a[x+34][y+20] = BLOCK;
	a[x+34][y+21] = BLOCK;
	a[x+35][y+7] = BLOCK;
	a[x+35][y+8] = BLOCK;
	a[x+35][y+9] = BLOCK;
	a[x+35][y+10] = BLOCK;
	a[x+35][y+11] = BLOCK;
	a[x+35][y+12] = BLOCK;
	a[x+35][y+13] = BLOCK;
	a[x+35][y+19] = BLOCK;
	a[x+35][y+22] = BLOCK;
	a[x+36][y+2] = BLOCK;
	a[x+36][y+3] = BLOCK;
	a[x+36][y+4] = BLOCK;
	a[x+36][y+5] = BLOCK;
	a[x+36][y+6] = BLOCK;
	a[x+36][y+19] = BLOCK;
	a[x+36][y+22] = BLOCK;
	a[x+37][y+2] = BLOCK;
	a[x+37][y+3] = BLOCK;
	a[x+37][y+4] = BLOCK;
	a[x+37][y+5] = BLOCK;
	a[x+37][y+6] = BLOCK;
	a[x+37][y+7] = BLOCK;
	a[x+37][y+8] = BLOCK;
	a[x+37][y+20] = BLOCK;
	a[x+37][y+21] = BLOCK;
	a[x+38][y+2] = BLOCK;
	a[x+38][y+3] = BLOCK;
	a[x+38][y+4] = BLOCK;
	a[x+38][y+5] = BLOCK;
	a[x+38][y+6] = BLOCK;
	a[x+38][y+7] = BLOCK;
	a[x+38][y+8] = BLOCK;
	a[x+39][y+2] = BLOCK;
	a[x+39][y+3] = BLOCK;
	a[x+39][y+4] = BLOCK;
	a[x+39][y+5] = BLOCK;
	a[x+39][y+6] = BLOCK;
	a[x+39][y+7] = BLOCK;
	a[x+39][y+8] = BLOCK;
	a[x+39][y+19] = BLOCK;
	a[x+39][y+20] = BLOCK;
	a[x+39][y+21] = BLOCK;
	a[x+39][y+22] = BLOCK;
	a[x+40][y+2] = BLOCK;
	a[x+40][y+3] = BLOCK;
	a[x+40][y+4] = BLOCK;
	a[x+40][y+5] = BLOCK;
	a[x+40][y+6] = BLOCK;
	a[x+40][y+7] = BLOCK;
	a[x+40][y+8] = BLOCK;
	a[x+40][y+19] = BLOCK;
	a[x+41][y+2] = BLOCK;
	a[x+41][y+3] = BLOCK;
	a[x+41][y+4] = BLOCK;
	a[x+41][y+5] = BLOCK;
	a[x+41][y+6] = BLOCK;
	a[x+41][y+7] = BLOCK;
	a[x+41][y+8] = BLOCK;
	a[x+41][y+19] = BLOCK;
	a[x+41][y+20] = BLOCK;
	a[x+41][y+21] = BLOCK;
	a[x+41][y+22] = BLOCK;
	a[x+42][y+2] = BLOCK;
	a[x+42][y+3] = BLOCK;
	a[x+42][y+4] = BLOCK;
	a[x+42][y+5] = BLOCK;
	a[x+42][y+6] = BLOCK;
	a[x+42][y+7] = BLOCK;
	a[x+42][y+8] = BLOCK;
	a[x+42][y+19] = BLOCK;
	a[x+42][y+20] = BLOCK;
	a[x+42][y+22] = BLOCK;
	a[x+43][y+2] = BLOCK;
	a[x+43][y+3] = BLOCK;
	a[x+43][y+4] = BLOCK;
	a[x+43][y+5] = BLOCK;
	a[x+43][y+6] = BLOCK;
	a[x+43][y+7] = BLOCK;
	a[x+43][y+8] = BLOCK;
	a[x+43][y+19] = BLOCK;
	a[x+43][y+20] = BLOCK;
	a[x+43][y+22] = BLOCK;
	a[x+44][y+2] = BLOCK;
	a[x+44][y+3] = BLOCK;
	a[x+44][y+4] = BLOCK;
	a[x+44][y+5] = BLOCK;
	a[x+44][y+6] = BLOCK;
	a[x+44][y+7] = BLOCK;
	a[x+44][y+8] = BLOCK;
	a[x+45][y+2] = BLOCK;
	a[x+45][y+3] = BLOCK;
	a[x+45][y+4] = BLOCK;
	a[x+45][y+5] = BLOCK;
	a[x+45][y+6] = BLOCK;
	a[x+45][y+7] = BLOCK;
	a[x+45][y+8] = BLOCK;
	a[x+46][y+2] = BLOCK;
	a[x+46][y+3] = BLOCK;
	a[x+46][y+4] = BLOCK;
	a[x+46][y+5] = BLOCK;
	a[x+46][y+6] = BLOCK;
	a[x+46][y+7] = BLOCK;
	a[x+46][y+8] = BLOCK;
	a[x+47][y+2] = BLOCK;
	a[x+47][y+3] = BLOCK;
	a[x+47][y+4] = BLOCK;
	a[x+47][y+5] = BLOCK;
	a[x+47][y+6] = BLOCK;
	a[x+47][y+7] = BLOCK;
	a[x+47][y+8] = BLOCK;
	a[x+48][y+2] = BLOCK;
	a[x+48][y+3] = BLOCK;
	a[x+48][y+4] = BLOCK;
	a[x+48][y+5] = BLOCK;
	a[x+48][y+6] = BLOCK;
	a[x+48][y+7] = BLOCK;
	a[x+48][y+8] = BLOCK;
	a[x+49][y+2] = BLOCK;
	a[x+49][y+3] = BLOCK;
	a[x+49][y+4] = BLOCK;
	a[x+49][y+5] = BLOCK;
	a[x+49][y+6] = BLOCK;
	a[x+49][y+7] = BLOCK;
	a[x+49][y+8] = BLOCK;
	a[x+50][y+2] = BLOCK;
	a[x+50][y+3] = BLOCK;
	a[x+50][y+4] = BLOCK;
	a[x+50][y+5] = BLOCK;
	a[x+50][y+6] = BLOCK;
	a[x+50][y+7] = BLOCK;
	a[x+50][y+8] = BLOCK;
	a[x+51][y+2] = BLOCK;
	a[x+51][y+3] = BLOCK;
	a[x+51][y+4] = BLOCK;
	a[x+51][y+5] = BLOCK;
	a[x+51][y+6] = BLOCK;
	a[x+51][y+7] = BLOCK;
	a[x+51][y+8] = BLOCK;
	a[x+52][y+2] = BLOCK;
	a[x+52][y+3] = BLOCK;
	a[x+52][y+4] = BLOCK;
	a[x+52][y+5] = BLOCK;
	a[x+52][y+6] = BLOCK;
	a[x+52][y+7] = BLOCK;
	a[x+52][y+8] = BLOCK;
	a[x+53][y+2] = BLOCK;
	a[x+53][y+3] = BLOCK;
	a[x+53][y+4] = BLOCK;
	a[x+53][y+5] = BLOCK;
	a[x+53][y+6] = BLOCK;
	a[x+53][y+7] = BLOCK;
	a[x+53][y+8] = BLOCK;
	a[x+54][y+2] = BLOCK;
	a[x+54][y+3] = BLOCK;
	a[x+54][y+4] = BLOCK;
	a[x+54][y+5] = BLOCK;
	a[x+54][y+6] = BLOCK;
	a[x+54][y+7] = BLOCK;
	a[x+54][y+8] = BLOCK;
	a[x+55][y+2] = BLOCK;
	a[x+55][y+3] = BLOCK;
	a[x+55][y+4] = BLOCK;
	a[x+55][y+5] = BLOCK;
	a[x+55][y+6] = BLOCK;
	a[x+55][y+7] = BLOCK;
	a[x+55][y+8] = BLOCK;
	a[x+56][y+2] = BLOCK;
	a[x+56][y+3] = BLOCK;
	a[x+56][y+4] = BLOCK;
	a[x+56][y+5] = BLOCK;
	a[x+56][y+6] = BLOCK;
	a[x+56][y+7] = BLOCK;
	a[x+56][y+8] = BLOCK;
	a[x+57][y+2] = BLOCK;
	a[x+57][y+3] = BLOCK;
	a[x+57][y+4] = BLOCK;
	a[x+57][y+5] = BLOCK;
	a[x+57][y+6] = BLOCK;
	a[x+57][y+7] = BLOCK;
	a[x+57][y+8] = BLOCK;
	a[x+58][y+2] = BLOCK;
	a[x+58][y+3] = BLOCK;
	a[x+58][y+4] = BLOCK;
	a[x+58][y+5] = BLOCK;
	a[x+58][y+6] = BLOCK;
	a[x+58][y+7] = BLOCK;
	a[x+58][y+8] = BLOCK;
	a[x+59][y+2] = BLOCK;
	a[x+59][y+3] = BLOCK;
	a[x+59][y+4] = BLOCK;
	a[x+59][y+5] = BLOCK;
	a[x+59][y+6] = BLOCK;
	a[x+59][y+7] = BLOCK;
	a[x+59][y+8] = BLOCK;
	a[x+60][y+2] = BLOCK;
	a[x+60][y+3] = BLOCK;
	a[x+60][y+4] = BLOCK;
	a[x+60][y+5] = BLOCK;
	a[x+60][y+6] = BLOCK;
	a[x+60][y+7] = BLOCK;
	a[x+60][y+8] = BLOCK;
	a[x+61][y+2] = BLOCK;
	a[x+61][y+3] = BLOCK;
	a[x+61][y+4] = BLOCK;
	a[x+61][y+5] = BLOCK;
	a[x+61][y+6] = BLOCK;
	a[x+61][y+7] = BLOCK;
	a[x+61][y+8] = BLOCK;
	a[x+62][y+2] = BLOCK;
	a[x+62][y+3] = BLOCK;
	a[x+62][y+4] = BLOCK;
	a[x+62][y+5] = BLOCK;
	a[x+62][y+6] = BLOCK;
	a[x+62][y+7] = BLOCK;
	a[x+62][y+8] = BLOCK;
	a[x+63][y+2] = BLOCK;
	a[x+63][y+3] = BLOCK;
	a[x+63][y+4] = BLOCK;
	a[x+63][y+5] = BLOCK;
	a[x+63][y+6] = BLOCK;
	a[x+63][y+7] = BLOCK;
	a[x+63][y+8] = BLOCK;
	a[x+64][y+2] = BLOCK;
	a[x+64][y+3] = BLOCK;
	a[x+64][y+4] = BLOCK;
	a[x+64][y+5] = BLOCK;
	a[x+64][y+6] = BLOCK;
	a[x+64][y+7] = BLOCK;
	a[x+64][y+8] = BLOCK;
	a[x+65][y+2] = BLOCK;
	a[x+65][y+3] = BLOCK;
	a[x+65][y+4] = BLOCK;
	a[x+65][y+5] = BLOCK;
	a[x+65][y+6] = BLOCK;
	a[x+65][y+7] = BLOCK;
	a[x+65][y+8] = BLOCK;
	a[x+66][y+2] = BLOCK;
	a[x+66][y+3] = BLOCK;
	a[x+66][y+4] = BLOCK;
	a[x+66][y+5] = BLOCK;
	a[x+66][y+6] = BLOCK;
	a[x+66][y+7] = BLOCK;
	a[x+66][y+8] = BLOCK;
	a[x+67][y+2] = BLOCK;
	a[x+67][y+3] = BLOCK;
	a[x+67][y+4] = BLOCK;
	a[x+67][y+5] = BLOCK;
	a[x+67][y+6] = BLOCK;
	a[x+67][y+7] = BLOCK;
	a[x+67][y+8] = BLOCK;
	a[x+68][y+2] = BLOCK;
	a[x+68][y+3] = BLOCK;
	a[x+68][y+4] = BLOCK;
	a[x+68][y+5] = BLOCK;
	a[x+68][y+6] = BLOCK;
	a[x+68][y+7] = BLOCK;
	a[x+68][y+8] = BLOCK;
	a[x+69][y+2] = BLOCK;
	a[x+69][y+3] = BLOCK;
	a[x+69][y+4] = BLOCK;
	a[x+69][y+5] = BLOCK;
	a[x+69][y+6] = BLOCK;
	a[x+69][y+7] = BLOCK;
	a[x+69][y+8] = BLOCK;
	a[x+70][y+2] = BLOCK;
	a[x+70][y+3] = BLOCK;
	a[x+70][y+4] = BLOCK;
	a[x+70][y+5] = BLOCK;
	a[x+70][y+6] = BLOCK;
	a[x+70][y+7] = BLOCK;
	a[x+70][y+8] = BLOCK;
	a[x+71][y+2] = BLOCK;
	a[x+71][y+3] = BLOCK;
	a[x+71][y+4] = BLOCK;
	a[x+71][y+5] = BLOCK;
	a[x+71][y+6] = BLOCK;
	a[x+71][y+7] = BLOCK;
	a[x+71][y+8] = BLOCK;

}

void numberWrite(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t number){
    char str[4];
    sprintf(str, "%03d", number);
    for (uint8_t i = 0; i <= strlen(str)-1; i++){
        switch(str[i]){
            case 48:
            	a[x+0][y+1] = BLOCK;
                a[x+0][y+2] = BLOCK;
                a[x+0][y+3] = BLOCK;
                a[x+0][y+4] = BLOCK;
                a[x+0][y+5] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+2] = BLOCK;
                a[x+4][y+3] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                break;
            case 49:
                a[x+0][y+6] = BLOCK;
                a[x+1][y+1] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+1] = BLOCK;
                a[x+2][y+2] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+4] = BLOCK;
                a[x+2][y+5] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+6] = BLOCK;
                break;
            case 50:
                a[x+0][y+1] = BLOCK;
                a[x+0][y+5] = BLOCK;
                a[x+0][y+6] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+4] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+2] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+6] = BLOCK;
                break;
            case 51:
                a[x+0][y+1] = BLOCK;
                a[x+0][y+5] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+2] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                break;
            case 52:
                a[x+0][y+0] = BLOCK;
                a[x+0][y+1] = BLOCK;
                a[x+0][y+2] = BLOCK;
                a[x+0][y+3] = BLOCK;
                a[x+1][y+3] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+4][y+0] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+2] = BLOCK;
                a[x+4][y+3] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                a[x+4][y+6] = BLOCK;
                break;
            case 53:
                a[x+0][y+0] = BLOCK;
                a[x+0][y+1] = BLOCK;
                a[x+0][y+2] = BLOCK;
                a[x+0][y+3] = BLOCK;
                a[x+0][y+6] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+3] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+0] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                break;
            case 54:
                a[x+0][y+2] = BLOCK;
                a[x+0][y+3] = BLOCK;
                a[x+0][y+4] = BLOCK;
                a[x+0][y+5] = BLOCK;
                a[x+1][y+1] = BLOCK;
                a[x+1][y+3] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                break;
            case 55:
                a[x+0][y+0] = BLOCK;
                a[x+0][y+1] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+4] = BLOCK;
                a[x+1][y+5] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+2] = BLOCK;
                a[x+4][y+0] = BLOCK;
                a[x+4][y+1] = BLOCK;
                break;
            case 56:
                a[x+0][y+1] = BLOCK;
                a[x+0][y+2] = BLOCK;
                a[x+0][y+4] = BLOCK;
                a[x+0][y+5] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+3] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+3][y+6] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+2] = BLOCK;
                a[x+4][y+4] = BLOCK;
                a[x+4][y+5] = BLOCK;
                break;
            case 57:
                a[x+0][y+1] = BLOCK;
                a[x+0][y+2] = BLOCK;
                a[x+1][y+0] = BLOCK;
                a[x+1][y+3] = BLOCK;
                a[x+1][y+6] = BLOCK;
                a[x+2][y+0] = BLOCK;
                a[x+2][y+3] = BLOCK;
                a[x+2][y+6] = BLOCK;
                a[x+3][y+0] = BLOCK;
                a[x+3][y+3] = BLOCK;
                a[x+3][y+5] = BLOCK;
                a[x+4][y+1] = BLOCK;
                a[x+4][y+2] = BLOCK;
                a[x+4][y+3] = BLOCK;
                a[x+4][y+4] = BLOCK;
                break;
            }
            x+=6;
        }
    }

void bossKey(uint8_t a[128][32], uint8_t x, uint8_t y){
	a[x+0][y+0] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+1] = BLOCK;
	a[x+2][y+2] = BLOCK;
	a[x+2][y+3] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+2][y+5] = BLOCK;
	a[x+2][y+10] = BLOCK;
	a[x+2][y+11] = BLOCK;
	a[x+2][y+12] = BLOCK;
	a[x+2][y+13] = BLOCK;
	a[x+2][y+14] = BLOCK;
	a[x+2][y+18] = BLOCK;
	a[x+2][y+19] = BLOCK;
	a[x+2][y+20] = BLOCK;
	a[x+2][y+21] = BLOCK;
	a[x+2][y+22] = BLOCK;
	a[x+2][y+25] = BLOCK;
	a[x+2][y+26] = BLOCK;
	a[x+2][y+29] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+12] = BLOCK;
	a[x+3][y+18] = BLOCK;
	a[x+3][y+19] = BLOCK;
	a[x+3][y+25] = BLOCK;
	a[x+3][y+27] = BLOCK;
	a[x+3][y+29] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+12] = BLOCK;
	a[x+4][y+20] = BLOCK;
	a[x+4][y+21] = BLOCK;
	a[x+4][y+22] = BLOCK;
	a[x+4][y+25] = BLOCK;
	a[x+4][y+28] = BLOCK;
	a[x+4][y+29] = BLOCK;
	a[x+5][y+0] = BLOCK;
	a[x+5][y+1] = BLOCK;
	a[x+5][y+2] = BLOCK;
	a[x+5][y+3] = BLOCK;
	a[x+5][y+4] = BLOCK;
	a[x+5][y+5] = BLOCK;
	a[x+5][y+10] = BLOCK;
	a[x+5][y+11] = BLOCK;
	a[x+5][y+12] = BLOCK;
	a[x+5][y+13] = BLOCK;
	a[x+5][y+14] = BLOCK;
	a[x+5][y+20] = BLOCK;
	a[x+5][y+21] = BLOCK;
	a[x+6][y+2] = BLOCK;
	a[x+6][y+12] = BLOCK;
	a[x+6][y+13] = BLOCK;
	a[x+6][y+18] = BLOCK;
	a[x+6][y+19] = BLOCK;
	a[x+6][y+26] = BLOCK;
	a[x+6][y+27] = BLOCK;
	a[x+6][y+28] = BLOCK;
	a[x+6][y+29] = BLOCK;
	a[x+7][y+2] = BLOCK;
	a[x+7][y+3] = BLOCK;
	a[x+7][y+4] = BLOCK;
	a[x+7][y+5] = BLOCK;
	a[x+7][y+11] = BLOCK;
	a[x+7][y+14] = BLOCK;
	a[x+7][y+18] = BLOCK;
	a[x+7][y+19] = BLOCK;
	a[x+7][y+20] = BLOCK;
	a[x+7][y+21] = BLOCK;
	a[x+7][y+22] = BLOCK;
	a[x+7][y+26] = BLOCK;
	a[x+7][y+27] = BLOCK;
	a[x+7][y+29] = BLOCK;
	a[x+8][y+11] = BLOCK;
	a[x+8][y+14] = BLOCK;
	a[x+8][y+26] = BLOCK;
	a[x+8][y+27] = BLOCK;
	a[x+8][y+29] = BLOCK;
	a[x+9][y+12] = BLOCK;
	a[x+9][y+13] = BLOCK;
	a[x+9][y+17] = BLOCK;
	a[x+9][y+19] = BLOCK;
	a[x+9][y+20] = BLOCK;
	a[x+9][y+21] = BLOCK;
	a[x+9][y+22] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+2] = BLOCK;
	a[x+10][y+3] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+5] = BLOCK;
	a[x+10][y+27] = BLOCK;
	a[x+10][y+28] = BLOCK;
	a[x+10][y+29] = BLOCK;
	a[x+11][y+11] = BLOCK;
	a[x+11][y+12] = BLOCK;
	a[x+11][y+13] = BLOCK;
	a[x+11][y+14] = BLOCK;
	a[x+11][y+19] = BLOCK;
	a[x+11][y+20] = BLOCK;
	a[x+11][y+21] = BLOCK;
	a[x+11][y+22] = BLOCK;
	a[x+11][y+26] = BLOCK;
	a[x+11][y+29] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+3] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+14] = BLOCK;
	a[x+12][y+19] = BLOCK;
	a[x+12][y+26] = BLOCK;
	a[x+12][y+29] = BLOCK;
	a[x+13][y+2] = BLOCK;
	a[x+13][y+3] = BLOCK;
	a[x+13][y+5] = BLOCK;
	a[x+13][y+11] = BLOCK;
	a[x+13][y+12] = BLOCK;
	a[x+13][y+13] = BLOCK;
	a[x+13][y+14] = BLOCK;
	a[x+13][y+19] = BLOCK;
	a[x+13][y+20] = BLOCK;
	a[x+13][y+21] = BLOCK;
	a[x+13][y+22] = BLOCK;
	a[x+13][y+27] = BLOCK;
	a[x+13][y+28] = BLOCK;
	a[x+14][y+2] = BLOCK;
	a[x+14][y+4] = BLOCK;
	a[x+14][y+5] = BLOCK;
	a[x+14][y+26] = BLOCK;
	a[x+14][y+29] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+14] = BLOCK;
	a[x+15][y+19] = BLOCK;
	a[x+15][y+20] = BLOCK;
	a[x+15][y+21] = BLOCK;
	a[x+15][y+22] = BLOCK;
	a[x+15][y+26] = BLOCK;
	a[x+15][y+29] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+22] = BLOCK;
	a[x+16][y+27] = BLOCK;
	a[x+16][y+28] = BLOCK;
	a[x+17][y+11] = BLOCK;
	a[x+17][y+12] = BLOCK;
	a[x+17][y+14] = BLOCK;
	a[x+17][y+19] = BLOCK;
	a[x+17][y+20] = BLOCK;
	a[x+17][y+21] = BLOCK;
	a[x+17][y+22] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+2] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+5] = BLOCK;
	a[x+18][y+11] = BLOCK;
	a[x+18][y+13] = BLOCK;
	a[x+18][y+14] = BLOCK;
	a[x+18][y+19] = BLOCK;
	a[x+18][y+26] = BLOCK;
	a[x+18][y+27] = BLOCK;
	a[x+18][y+28] = BLOCK;
	a[x+18][y+29] = BLOCK;
	a[x+19][y+18] = BLOCK;
	a[x+19][y+19] = BLOCK;
	a[x+19][y+20] = BLOCK;
	a[x+19][y+21] = BLOCK;
	a[x+19][y+22] = BLOCK;
	a[x+19][y+26] = BLOCK;
	a[x+20][y+2] = BLOCK;
	a[x+20][y+3] = BLOCK;
	a[x+20][y+5] = BLOCK;
	a[x+20][y+19] = BLOCK;
	a[x+20][y+22] = BLOCK;
	a[x+20][y+26] = BLOCK;
	a[x+20][y+27] = BLOCK;
	a[x+20][y+28] = BLOCK;
	a[x+20][y+29] = BLOCK;
	a[x+21][y+2] = BLOCK;
	a[x+21][y+3] = BLOCK;
	a[x+21][y+5] = BLOCK;
	a[x+21][y+11] = BLOCK;
	a[x+21][y+14] = BLOCK;
	a[x+21][y+19] = BLOCK;
	a[x+21][y+20] = BLOCK;
	a[x+21][y+21] = BLOCK;
	a[x+21][y+22] = BLOCK;
	a[x+21][y+26] = BLOCK;
	a[x+21][y+27] = BLOCK;
	a[x+21][y+28] = BLOCK;
	a[x+21][y+29] = BLOCK;
	a[x+22][y+2] = BLOCK;
	a[x+22][y+4] = BLOCK;
	a[x+22][y+5] = BLOCK;
	a[x+22][y+19] = BLOCK;
	a[x+22][y+20] = BLOCK;
	a[x+22][y+22] = BLOCK;
	a[x+22][y+26] = BLOCK;
	a[x+22][y+29] = BLOCK;
	a[x+23][y+19] = BLOCK;
	a[x+23][y+20] = BLOCK;
	a[x+23][y+22] = BLOCK;
	a[x+23][y+25] = BLOCK;
	a[x+23][y+26] = BLOCK;
	a[x+23][y+27] = BLOCK;
	a[x+23][y+28] = BLOCK;
	a[x+23][y+29] = BLOCK;
	a[x+25][y+2] = BLOCK;
	a[x+25][y+4] = BLOCK;
	a[x+25][y+5] = BLOCK;
	a[x+25][y+19] = BLOCK;
	a[x+25][y+20] = BLOCK;
	a[x+25][y+22] = BLOCK;
	a[x+25][y+26] = BLOCK;
	a[x+25][y+27] = BLOCK;
	a[x+25][y+29] = BLOCK;
	a[x+26][y+2] = BLOCK;
	a[x+26][y+4] = BLOCK;
	a[x+26][y+5] = BLOCK;
	a[x+26][y+19] = BLOCK;
	a[x+26][y+21] = BLOCK;
	a[x+26][y+22] = BLOCK;
	a[x+26][y+26] = BLOCK;
	a[x+26][y+28] = BLOCK;
	a[x+26][y+29] = BLOCK;
	a[x+27][y+2] = BLOCK;
	a[x+27][y+3] = BLOCK;
	a[x+27][y+4] = BLOCK;
	a[x+27][y+5] = BLOCK;
	a[x+29][y+19] = BLOCK;
	a[x+29][y+22] = BLOCK;
	a[x+29][y+26] = BLOCK;
	a[x+29][y+29] = BLOCK;
	a[x+31][y+2] = BLOCK;
	a[x+31][y+3] = BLOCK;
	a[x+32][y+4] = BLOCK;
	a[x+32][y+5] = BLOCK;
	a[x+33][y+3] = BLOCK;
	a[x+33][y+4] = BLOCK;
	a[x+34][y+2] = BLOCK;
	a[x+34][y+3] = BLOCK;
	a[x+34][y+4] = BLOCK;
	a[x+35][y+4] = BLOCK;
	a[x+35][y+5] = BLOCK;
	a[x+36][y+2] = BLOCK;
	a[x+36][y+3] = BLOCK;
	a[x+37][y+3] = BLOCK;
	a[x+37][y+4] = BLOCK;
	a[x+38][y+2] = BLOCK;
	a[x+38][y+5] = BLOCK;
	a[x+39][y+2] = BLOCK;
	a[x+39][y+5] = BLOCK;
	a[x+40][y+3] = BLOCK;
	a[x+40][y+4] = BLOCK;
	a[x+43][y+2] = BLOCK;
	a[x+43][y+3] = BLOCK;
	a[x+43][y+4] = BLOCK;
	a[x+43][y+5] = BLOCK;
	a[x+44][y+2] = BLOCK;
	a[x+46][y+0] = BLOCK;
	a[x+46][y+1] = BLOCK;
	a[x+46][y+2] = BLOCK;
	a[x+46][y+3] = BLOCK;
	a[x+46][y+4] = BLOCK;
	a[x+46][y+5] = BLOCK;
	a[x+47][y+3] = BLOCK;
	a[x+47][y+4] = BLOCK;
	a[x+48][y+2] = BLOCK;
	a[x+48][y+5] = BLOCK;
	a[x+50][y+2] = BLOCK;
	a[x+50][y+3] = BLOCK;
	a[x+50][y+4] = BLOCK;
	a[x+50][y+5] = BLOCK;
	a[x+50][y+6] = BLOCK;
	a[x+50][y+7] = BLOCK;
	a[x+51][y+2] = BLOCK;
	a[x+51][y+5] = BLOCK;
	a[x+52][y+2] = BLOCK;
	a[x+52][y+5] = BLOCK;
	a[x+53][y+2] = BLOCK;
	a[x+53][y+3] = BLOCK;
	a[x+53][y+4] = BLOCK;
	a[x+53][y+5] = BLOCK;
	a[x+55][y+0] = BLOCK;
	a[x+55][y+1] = BLOCK;
	a[x+55][y+2] = BLOCK;
	a[x+55][y+3] = BLOCK;
	a[x+55][y+4] = BLOCK;
	a[x+55][y+5] = BLOCK;
	a[x+57][y+2] = BLOCK;
	a[x+57][y+4] = BLOCK;
	a[x+57][y+5] = BLOCK;
	a[x+57][y+14] = BLOCK;
	a[x+58][y+2] = BLOCK;
	a[x+58][y+4] = BLOCK;
	a[x+58][y+5] = BLOCK;
	a[x+58][y+11] = BLOCK;
	a[x+58][y+12] = BLOCK;
	a[x+58][y+13] = BLOCK;
	a[x+59][y+2] = BLOCK;
	a[x+59][y+3] = BLOCK;
	a[x+59][y+4] = BLOCK;
	a[x+59][y+5] = BLOCK;
	a[x+59][y+10] = BLOCK;
	a[x+59][y+11] = BLOCK;
	a[x+59][y+13] = BLOCK;
	a[x+60][y+12] = BLOCK;
	a[x+60][y+13] = BLOCK;
	a[x+60][y+14] = BLOCK;
	a[x+61][y+3] = BLOCK;
	a[x+61][y+4] = BLOCK;
	a[x+61][y+5] = BLOCK;
	a[x+62][y+2] = BLOCK;
	a[x+62][y+5] = BLOCK;
	a[x+63][y+2] = BLOCK;
	a[x+63][y+5] = BLOCK;
	a[x+65][y+3] = BLOCK;
	a[x+65][y+4] = BLOCK;
	a[x+65][y+11] = BLOCK;
	a[x+65][y+12] = BLOCK;
	a[x+65][y+13] = BLOCK;
	a[x+65][y+14] = BLOCK;
	a[x+66][y+2] = BLOCK;
	a[x+66][y+3] = BLOCK;
	a[x+66][y+5] = BLOCK;
	a[x+66][y+11] = BLOCK;
	a[x+67][y+2] = BLOCK;
	a[x+67][y+3] = BLOCK;
	a[x+67][y+5] = BLOCK;
	a[x+67][y+11] = BLOCK;
	a[x+67][y+12] = BLOCK;
	a[x+67][y+13] = BLOCK;
	a[x+67][y+14] = BLOCK;
	a[x+68][y+2] = BLOCK;
	a[x+68][y+3] = BLOCK;
	a[x+68][y+5] = BLOCK;
	a[x+68][y+11] = BLOCK;
	a[x+68][y+12] = BLOCK;
	a[x+68][y+14] = BLOCK;
	a[x+69][y+11] = BLOCK;
	a[x+69][y+12] = BLOCK;
	a[x+69][y+13] = BLOCK;
	a[x+69][y+14] = BLOCK;
	a[x+72][y+11] = BLOCK;
	a[x+72][y+12] = BLOCK;
	a[x+72][y+13] = BLOCK;
	a[x+72][y+14] = BLOCK;
	a[x+73][y+11] = BLOCK;
	a[x+74][y+11] = BLOCK;
	a[x+74][y+12] = BLOCK;
	a[x+74][y+13] = BLOCK;
	a[x+74][y+14] = BLOCK;
	a[x+75][y+11] = BLOCK;
	a[x+75][y+12] = BLOCK;
	a[x+75][y+13] = BLOCK;
	a[x+75][y+14] = BLOCK;
	a[x+76][y+11] = BLOCK;
	a[x+76][y+14] = BLOCK;
	a[x+77][y+10] = BLOCK;
	a[x+77][y+11] = BLOCK;
	a[x+77][y+12] = BLOCK;
	a[x+77][y+13] = BLOCK;
	a[x+77][y+14] = BLOCK;
	a[x+79][y+12] = BLOCK;
	a[x+79][y+13] = BLOCK;
	a[x+80][y+11] = BLOCK;
	a[x+80][y+14] = BLOCK;
	a[x+81][y+11] = BLOCK;
	a[x+81][y+14] = BLOCK;
	a[x+82][y+12] = BLOCK;
	a[x+82][y+13] = BLOCK;
	a[x+84][y+11] = BLOCK;
	a[x+84][y+12] = BLOCK;
	a[x+84][y+13] = BLOCK;
	a[x+84][y+14] = BLOCK;
	a[x+85][y+11] = BLOCK;
	a[x+86][y+11] = BLOCK;
	a[x+86][y+12] = BLOCK;
	a[x+86][y+13] = BLOCK;
	a[x+86][y+14] = BLOCK;
	a[x+87][y+11] = BLOCK;
	a[x+88][y+11] = BLOCK;
	a[x+88][y+12] = BLOCK;
	a[x+88][y+13] = BLOCK;
	a[x+88][y+14] = BLOCK;
	a[x+91][y+11] = BLOCK;
	a[x+92][y+10] = BLOCK;
	a[x+92][y+11] = BLOCK;
	a[x+92][y+12] = BLOCK;
	a[x+92][y+13] = BLOCK;
	a[x+92][y+14] = BLOCK;
	a[x+93][y+11] = BLOCK;
	a[x+93][y+14] = BLOCK;
	a[x+94][y+12] = BLOCK;
	a[x+94][y+13] = BLOCK;
	a[x+95][y+11] = BLOCK;
	a[x+95][y+14] = BLOCK;
	a[x+96][y+11] = BLOCK;
	a[x+96][y+14] = BLOCK;
	a[x+97][y+12] = BLOCK;
	a[x+97][y+13] = BLOCK;
	a[x+99][y+11] = BLOCK;
	a[x+99][y+12] = BLOCK;
	a[x+99][y+13] = BLOCK;
	a[x+99][y+14] = BLOCK;
	a[x+99][y+15] = BLOCK;
	a[x+99][y+16] = BLOCK;
	a[x+99][y+17] = BLOCK;
	a[x+100][y+11] = BLOCK;
	a[x+100][y+14] = BLOCK;
	a[x+101][y+11] = BLOCK;
	a[x+101][y+12] = BLOCK;
	a[x+101][y+13] = BLOCK;
	a[x+101][y+14] = BLOCK;
	a[x+104][y+11] = BLOCK;
	a[x+104][y+12] = BLOCK;
	a[x+104][y+14] = BLOCK;
	a[x+105][y+11] = BLOCK;
	a[x+105][y+13] = BLOCK;
	a[x+105][y+14] = BLOCK;
	a[x+107][y+12] = BLOCK;
	a[x+107][y+13] = BLOCK;
	a[x+107][y+14] = BLOCK;
	a[x+108][y+11] = BLOCK;
	a[x+108][y+14] = BLOCK;
	a[x+109][y+11] = BLOCK;
	a[x+109][y+14] = BLOCK;
	a[x+110][y+12] = BLOCK;
	a[x+110][y+13] = BLOCK;
	a[x+111][y+11] = BLOCK;
	a[x+111][y+14] = BLOCK;
	a[x+112][y+11] = BLOCK;
	a[x+112][y+14] = BLOCK;
	a[x+113][y+12] = BLOCK;
	a[x+113][y+13] = BLOCK;
	a[x+115][y+11] = BLOCK;
	a[x+115][y+12] = BLOCK;
	a[x+115][y+13] = BLOCK;
	a[x+115][y+14] = BLOCK;
	a[x+116][y+11] = BLOCK;
	a[x+117][y+11] = BLOCK;
	a[x+117][y+12] = BLOCK;
	a[x+117][y+13] = BLOCK;
	a[x+117][y+14] = BLOCK;
	a[x+118][y+11] = BLOCK;
	a[x+118][y+12] = BLOCK;
	a[x+118][y+14] = BLOCK;
	a[x+119][y+11] = BLOCK;
	a[x+119][y+12] = BLOCK;
	a[x+119][y+14] = BLOCK;
}

void helpscreen(uint8_t a[128][32], uint8_t x, uint8_t y) {
    charToArray(a, x+7, y+0, 'C');
    charToArray(a, x+13, y+0, 'O');
    charToArray(a, x+19, y+0, 'N');
    charToArray(a, x+25, y+0, 'T');
    charToArray(a, x+31, y+0, 'R');
    charToArray(a, x+37, y+0, 'O');
    charToArray(a, x+43, y+0, 'L');

    charToArray(a, x+55, y+0, 'P');
    charToArray(a, x+61, y+0, 'L');
    charToArray(a, x+66, y+0, 'A');
    charToArray(a, x+72, y+0, 'Y');
    charToArray(a, x+78, y+0, 'E');
    charToArray(a, x+84, y+0, 'R');
    charToArray(a, x+90, y+0, 'S');

    charToArray(a, x+102, y+0, 'V');
    charToArray(a, x+108, y+0, 'I');
    charToArray(a, x+114, y+0, 'A');

    charToArray(a, x+7, y+8, 'P');
    charToArray(a, x+13, y+8, 'O');
    charToArray(a, x+19, y+8, 'T');
    charToArray(a, x+25, y+8, 'E');
    charToArray(a, x+31, y+8, 'N');
    charToArray(a, x+37, y+8, 'T');
    charToArray(a, x+43, y+8, 'I');
    charToArray(a, x+49, y+8, 'O');
    charToArray(a, x+55, y+8, 'M');
    charToArray(a, x+61, y+8, 'E');
    charToArray(a, x+67, y+8, 'T');
    charToArray(a, x+73, y+8, 'E');
    charToArray(a, x+79, y+8, 'R');
    charToArray(a, x+85, y+8, 'S');

    charToArray(a, x+97, y+8, 'A');
    charToArray(a, x+103, y+8, 'N');
    charToArray(a, x+109, y+8, 'D');

    charToArray(a, x+7, y+16, 'S');
    charToArray(a, x+13, y+16, 'E');
    charToArray(a, x+19, y+16, 'L');
    charToArray(a, x+25, y+16, 'E');
    charToArray(a, x+31, y+16, 'C');
    charToArray(a, x+37, y+16, 'T');

    charToArray(a, x+49, y+16, 'V');
    charToArray(a, x+55, y+16, 'I');
    charToArray(a, x+61, y+16, 'A');

    charToArray(a, x+73, y+16, 'J');
    charToArray(a, x+79, y+16, 'O');
    charToArray(a, x+85, y+16, 'Y');
    charToArray(a, x+91, y+16, 'S');
    charToArray(a, x+97, y+16, 'T');
    charToArray(a, x+103, y+16, 'I');
    charToArray(a, x+109, y+16, 'C');
    charToArray(a, x+115, y+16, 'K');

    charToArray(a, x+7, y+24, 'C');
    charToArray(a, x+13, y+24, 'E');
    charToArray(a, x+19, y+24, 'N');
    charToArray(a, x+25, y+24, 'T');
    charToArray(a, x+31, y+24, 'E');
    charToArray(a, x+37, y+24, 'R');

    charToArray(a, x+49, y+24, 'F');
    charToArray(a, x+55, y+24, 'O');
    charToArray(a, x+61, y+24, 'R');

    charToArray(a, x+73, y+24, 'B');
    charToArray(a, x+81, y+24, 'A');
    charToArray(a, x+87, y+24, 'C');
    charToArray(a, x+93, y+24, 'K');
}

void charToArray(uint8_t a[128][32], uint8_t x, uint8_t y, char c) {
    switch(c) {
    case 'A':
        drawLine(a, x, y+2, 1, 5);
        drawLine(a, x+4, y+2, 1, 5);
        drawLine(a, x+1, y+4, 3, 1);
        a[x+1][y+1] = BLOCK;
        a[x+2][y] = BLOCK;
        a[x+3][y+1] = BLOCK;
        break;
    case 'B':
        drawLine(a, x, y, 1, 7);
        a[x+1][y] = BLOCK;
        a[x+2][y] = BLOCK;
        a[x+3][y] = BLOCK;
        a[x+1][y+3] = BLOCK;
        a[x+2][y+3] = BLOCK;
        a[x+3][y+3] = BLOCK;
        a[x+1][y+6] = BLOCK;
        a[x+2][y+6] = BLOCK;
        a[x+3][y+6] = BLOCK;
        a[x+4][y+1] = BLOCK;
        a[x+4][y+2] = BLOCK;
        a[x+4][y+4] = BLOCK;
        a[x+4][y+5] = BLOCK;
        break;
    case 'C':
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+6, 4, 1);
        drawLine(a, x, y+1, 1, 5);
        break;
    case 'D':
        drawLine(a, x, y, 1, 7);
        a[x+1][y] = BLOCK;
        a[x+2][y] = BLOCK;
        a[x+1][y+6] = BLOCK;
        a[x+2][y+6] = BLOCK;
        a[x+3][y+1] = BLOCK;
        a[x+3][y+5] = BLOCK;
        a[x+4][y+2] = BLOCK;
        a[x+4][y+3] = BLOCK;
        a[x+4][y+4] = BLOCK;
        break;
    case 'E':
        drawLine(a, x, y+1, 1, 5);
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+3, 4, 1);
        drawLine(a, x+1, y+6, 4, 1);
        break;
    case 'F':
        drawLine(a, x, y, 1, 7);
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+3, 2, 1);
        break;
    case 'T':
        drawLine(a, x, y, 5, 1);
        drawLine(a, x+2, y+1, 1, 6);
        break;
    case 'I':
        drawLine(a, x, y, 5, 1);
        drawLine(a, x+2, y+1, 1, 5);
        drawLine(a, x, y+6, 5, 1);
        break;
    case 'O':
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+6, 4, 1);
        drawLine(a, x, y+1, 1, 5);
        drawLine(a, x+5, y+1, 1, 5);
        break;
    case 'P':
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+3, 4, 1);
        drawLine(a, x, y+1, 1, 6);
        a[x+5][y+1] = BLOCK;
        a[x+5][y+2] = BLOCK;
        break;
    case 'N':
        drawLine(a, x, y, 1, 7);
        drawLine(a, x+5, y, 1, 7);
        a[x+1][y+1] = BLOCK;
        a[x+2][y+2] = BLOCK;
        a[x+2][y+3] = BLOCK;
        a[x+3][y+3] = BLOCK;
        a[x+3][y+4] = BLOCK;
        a[x+4][y+5] = BLOCK;
        break;
    case 'R':
        drawLine(a, x, y, 5, 1);
        drawLine(a, x+1, y+3, 4, 1);
        drawLine(a, x, y+1, 1, 6);
        a[x+5][y+1] = BLOCK;
        a[x+5][y+2] = BLOCK;
        a[x+3][y+4] = BLOCK;
        a[x+4][y+5] = BLOCK;
        a[x+5][y+6] = BLOCK;
        break;
    case 'L':
        drawLine(a, x, y, 1, 6);
        drawLine(a, x+1, y+6, 3, 1);
        break;
    case 'Y':
        drawLine(a, x+2, y+2, 1, 5);
        a[x][y] = BLOCK;
        a[x][y+1] = BLOCK;
        a[x+4][y] = BLOCK;
        a[x+4][y+1] = BLOCK;
        a[x+1][y+2] = BLOCK;
        a[x+3][y+2] = BLOCK;
        break;
    case 'S':
        drawLine(a, x+1, y, 4, 1);
        drawLine(a, x+1, y+3, 4, 1);
        drawLine(a, x+1, y+6, 4, 1);
        a[x][y+1] = BLOCK;
        a[x][y+2] = BLOCK;
        a[x+5][y+4] = BLOCK;
        a[x+5][y+5] = BLOCK;
        break;
    case 'V':
        drawLine(a, x, y, 1, 5);
        drawLine(a, x+5, y, 1, 5);
        a[x+1][y+5] = BLOCK;
        a[x+2][y+6] = BLOCK;
        a[x+3][y+6] = BLOCK;
        a[x+4][y+5] = BLOCK;
        break;
    case 'M':
        drawLine(a, x, y, 1, 7);
        drawLine(a, x+4, y, 1, 7);
        a[x+1][y+1] = BLOCK;
        a[x+3][y+1] = BLOCK;
        a[x+2][y+2] = BLOCK;
        a[x+2][y+2] = BLOCK;
        break;
    case 'J':
        drawLine(a, x, y, 4, 1);
        drawLine(a, x+4, y+1, 1, 5);
        a[x][y+5] = BLOCK;
        a[x+1][y+6] = BLOCK;
        a[x+2][y+6] = BLOCK;
        a[x+3][y+6] = BLOCK;
        break;
    case 'K':
        drawLine(a, x, y, 1, 7);
        a[x+1][y+3] = BLOCK;
        a[x+2][y+2] = BLOCK;
        a[x+2][y+4] = BLOCK;
        a[x+3][y+1] = BLOCK;
        a[x+3][y+5] = BLOCK;
        a[x+4][y] = BLOCK;
        a[x+4][y+6] = BLOCK;
        break;
    case 'U':
        drawLine(a, x+1, y+6, 4, 1);
        drawLine(a, x, y, 1, 6);
        drawLine(a, x+5, y, 1, 6);
        break;
    }
}
