#include "menu.h"
#include "ansi.h"
#include "lcd.h"
#include "timer.h"
#include "ball.h"

void menuTree(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32],int8_t *menuSettings, uint16_t *testCount,  uint8_t *bricks, uint8_t *lives){
    uint8_t x, oldx, menuTrack = 0;
    int8_t selector = 1;

    while(((*menuSettings >> 0) & 1) == 0){
        x=readJoystick();
        gotoxy(1,1);
        if (menuTrack == 0){
            startMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);

            if (x!=oldx){
                blinkSelect(4,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // Play game
                        case 1:
                            *menuSettings |= (0x0001 << 0);
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            simpleMapToArray(playingField);
                            (*lives) = 3; // Easy?
                            lvl1(10, 10, playingField, bricks, lives);
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
                oldx = x;
            }
        }
        // Level/Difficulty menu
        else if (menuTrack == 2){
            levelMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);
            if (x!=oldx){
                blinkSelect(3,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // Difficulty Easy
                        case 1:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            *menuSettings |= (0x0001 << 2);
                            //*difficulty = 1;
                            menuTrack = 0;
                            selector = 1;
                            break;
                        // Difficulty Medium
                        case 2:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            *menuSettings |= (0x0001 << 3);
                            //*difficulty = 2;
                            menuTrack = 0;
                            selector = 1;
                            break;
                        // Difficulty Hard
                        case 3:
                            memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                            *menuSettings |= (0x0001 << 4);
                            //*difficulty = 3;
                            menuTrack = 0;
                            selector = 1;
                            break;
                    }
                }

                oldx = x;
            }
        }
        // Mode menu
        else if (menuTrack == 3){
            modeMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);

            if (x!=oldx){
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
                oldx = x;
            }
        }
        // Help menu
        else if (menuTrack == 4){
            helpMenu(playingField, selector, testCount, &menuTrack);
            drawChangeInArray(playingField, oldPlayingField);
            convertArrayToBuffer(playingField);
            lcd_push_buffer(lcdArray);
            copyArray(*playingField, *oldPlayingField);
            if (x!=oldx){
                blinkSelect(1,&selector);
                if((readJoystick()>>4)&1){
                    switch(selector){
                        // Help menu ?
                        case 1:
                            menuTrack = 0;
                            selector = 1;
                            break;
                    }
                    memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);
                }
                oldx = x;
            }
        }
        *testCount = *testCount +1;
        //lcd_update();
    }
}

void livesToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t lives) {
    uint8_t i;
    for (i = 0; i < lives; i++) {
        if (i % 2 == 0) {
            drawHeart(playingField, (x), (y + (i * 4)) );
        } else {
            drawHeart(playingField, (x + 9), (y + (i * (i==1?0:4)) - (i==1?0:4)) );
        }
    }
}

void scoreToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t score) {
    //
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

void simpleMapToArray(uint8_t playingField[128][32]){
    // 196 Horizontal line, 179 Vertical line.
    uint8_t i;
    for (i = 0; i <= 100; i++) {
        playingField[i][0] = 196;
        playingField[i][31] = 196;
    }
}

void helpMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){
    menuSquare(playingField, 3,2, 40,29, 1, selector, testCount);
    level_easy(playingField,5,4);
}

void levelMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack){
    menuSquare(playingField, 3,2, 40,29, 1, selector, testCount);
    level_easy(playingField,5,4);

    menuSquare(playingField, 44,2, 81,29, 2, selector, testCount);
    level_medium(playingField,46,4);

    menuSquare(playingField, 85,2, 122,29, 3, selector, testCount);
    level_medium(playingField,87,4);
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

/*
    if((readJoystick()>>4&1)){
        switch(selector){
            case 1: //play
                *menuTrack = 1;
                break;
            case 2: //mode
                *menuTrack = 2;
                break;
            case 3: //level
                *menuTrack = 3;
                break;
            case 4: //mode
                *menuTrack = 4;
                break;
        }
    }
*/
}

void blinkSelect(int8_t maxWindows, int8_t * selector){
    //uint8_t x,oldx;


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

void level_hard(uint8_t a[128][32], uint8_t x, uint8_t y){
	a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+0][y+8] = BLOCK;
	a[x+0][y+9] = BLOCK;
	a[x+0][y+10] = BLOCK;
	a[x+0][y+11] = BLOCK;
	a[x+0][y+12] = BLOCK;
	a[x+0][y+13] = BLOCK;
	a[x+0][y+14] = BLOCK;
	a[x+0][y+15] = BLOCK;
	a[x+0][y+16] = BLOCK;
	a[x+0][y+17] = BLOCK;
	a[x+0][y+18] = BLOCK;
	a[x+0][y+19] = BLOCK;
	a[x+0][y+20] = BLOCK;
	a[x+0][y+21] = BLOCK;
	a[x+0][y+22] = BLOCK;
	a[x+0][y+23] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+1][y+4] = BLOCK;
	a[x+1][y+8] = BLOCK;
	a[x+1][y+12] = BLOCK;
	a[x+1][y+16] = BLOCK;
	a[x+1][y+20] = BLOCK;
	a[x+1][y+22] = BLOCK;
	a[x+1][y+23] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+2] = BLOCK;
	a[x+2][y+3] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+2][y+5] = BLOCK;
	a[x+2][y+8] = BLOCK;
	a[x+2][y+12] = BLOCK;
	a[x+2][y+16] = BLOCK;
	a[x+2][y+17] = BLOCK;
	a[x+2][y+18] = BLOCK;
	a[x+2][y+19] = BLOCK;
	a[x+2][y+20] = BLOCK;
	a[x+2][y+23] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+1] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+3][y+6] = BLOCK;
	a[x+3][y+8] = BLOCK;
	a[x+3][y+11] = BLOCK;
	a[x+3][y+12] = BLOCK;
	a[x+3][y+14] = BLOCK;
	a[x+3][y+16] = BLOCK;
	a[x+3][y+20] = BLOCK;
	a[x+3][y+22] = BLOCK;
	a[x+3][y+23] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+4] = BLOCK;
	a[x+4][y+6] = BLOCK;
	a[x+4][y+8] = BLOCK;
	a[x+4][y+9] = BLOCK;
	a[x+4][y+12] = BLOCK;
	a[x+4][y+13] = BLOCK;
	a[x+4][y+16] = BLOCK;
	a[x+4][y+17] = BLOCK;
	a[x+4][y+20] = BLOCK;
	a[x+4][y+21] = BLOCK;
	a[x+4][y+23] = BLOCK;
	a[x+5][y+0] = BLOCK;
	a[x+5][y+2] = BLOCK;
	a[x+5][y+4] = BLOCK;
	a[x+5][y+5] = BLOCK;
	a[x+5][y+6] = BLOCK;
	a[x+5][y+7] = BLOCK;
	a[x+5][y+8] = BLOCK;
	a[x+5][y+10] = BLOCK;
	a[x+5][y+11] = BLOCK;
	a[x+5][y+12] = BLOCK;
	a[x+5][y+14] = BLOCK;
	a[x+5][y+15] = BLOCK;
	a[x+5][y+16] = BLOCK;
	a[x+5][y+17] = BLOCK;
	a[x+5][y+18] = BLOCK;
	a[x+5][y+20] = BLOCK;
	a[x+5][y+21] = BLOCK;
	a[x+5][y+22] = BLOCK;
	a[x+5][y+23] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+8] = BLOCK;
	a[x+6][y+9] = BLOCK;
	a[x+6][y+12] = BLOCK;
	a[x+6][y+16] = BLOCK;
	a[x+6][y+17] = BLOCK;
	a[x+6][y+19] = BLOCK;
	a[x+6][y+20] = BLOCK;
	a[x+6][y+23] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+4] = BLOCK;
	a[x+7][y+6] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+7][y+8] = BLOCK;
	a[x+7][y+12] = BLOCK;
	a[x+7][y+15] = BLOCK;
	a[x+7][y+16] = BLOCK;
	a[x+7][y+20] = BLOCK;
	a[x+7][y+21] = BLOCK;
	a[x+7][y+23] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+4] = BLOCK;
	a[x+8][y+6] = BLOCK;
	a[x+8][y+8] = BLOCK;
	a[x+8][y+10] = BLOCK;
	a[x+8][y+12] = BLOCK;
	a[x+8][y+14] = BLOCK;
	a[x+8][y+16] = BLOCK;
	a[x+8][y+20] = BLOCK;
	a[x+8][y+23] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+1] = BLOCK;
	a[x+9][y+2] = BLOCK;
	a[x+9][y+3] = BLOCK;
	a[x+9][y+4] = BLOCK;
	a[x+9][y+6] = BLOCK;
	a[x+9][y+8] = BLOCK;
	a[x+9][y+9] = BLOCK;
	a[x+9][y+10] = BLOCK;
	a[x+9][y+11] = BLOCK;
	a[x+9][y+12] = BLOCK;
	a[x+9][y+13] = BLOCK;
	a[x+9][y+14] = BLOCK;
	a[x+9][y+16] = BLOCK;
	a[x+9][y+17] = BLOCK;
	a[x+9][y+18] = BLOCK;
	a[x+9][y+19] = BLOCK;
	a[x+9][y+20] = BLOCK;
	a[x+9][y+22] = BLOCK;
	a[x+9][y+23] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+10][y+8] = BLOCK;
	a[x+10][y+11] = BLOCK;
	a[x+10][y+12] = BLOCK;
	a[x+10][y+16] = BLOCK;
	a[x+10][y+19] = BLOCK;
	a[x+10][y+20] = BLOCK;
	a[x+10][y+22] = BLOCK;
	a[x+10][y+23] = BLOCK;
	a[x+11][y+0] = BLOCK;
	a[x+11][y+3] = BLOCK;
	a[x+11][y+4] = BLOCK;
	a[x+11][y+5] = BLOCK;
	a[x+11][y+8] = BLOCK;
	a[x+11][y+10] = BLOCK;
	a[x+11][y+12] = BLOCK;
	a[x+11][y+16] = BLOCK;
	a[x+11][y+18] = BLOCK;
	a[x+11][y+20] = BLOCK;
	a[x+11][y+23] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+2] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+12][y+8] = BLOCK;
	a[x+12][y+9] = BLOCK;
	a[x+12][y+12] = BLOCK;
	a[x+12][y+13] = BLOCK;
	a[x+12][y+14] = BLOCK;
	a[x+12][y+15] = BLOCK;
	a[x+12][y+16] = BLOCK;
	a[x+12][y+17] = BLOCK;
	a[x+12][y+20] = BLOCK;
	a[x+12][y+21] = BLOCK;
	a[x+12][y+22] = BLOCK;
	a[x+12][y+23] = BLOCK;
	a[x+13][y+0] = BLOCK;
	a[x+13][y+2] = BLOCK;
	a[x+13][y+4] = BLOCK;
	a[x+13][y+6] = BLOCK;
	a[x+13][y+8] = BLOCK;
	a[x+13][y+9] = BLOCK;
	a[x+13][y+10] = BLOCK;
	a[x+13][y+12] = BLOCK;
	a[x+13][y+15] = BLOCK;
	a[x+13][y+16] = BLOCK;
	a[x+13][y+20] = BLOCK;
	a[x+13][y+23] = BLOCK;
	a[x+14][y+0] = BLOCK;
	a[x+14][y+2] = BLOCK;
	a[x+14][y+4] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+14][y+8] = BLOCK;
	a[x+14][y+11] = BLOCK;
	a[x+14][y+12] = BLOCK;
	a[x+14][y+14] = BLOCK;
	a[x+14][y+16] = BLOCK;
	a[x+14][y+20] = BLOCK;
	a[x+14][y+23] = BLOCK;
	a[x+15][y+0] = BLOCK;
	a[x+15][y+1] = BLOCK;
	a[x+15][y+4] = BLOCK;
	a[x+15][y+7] = BLOCK;
	a[x+15][y+8] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+14] = BLOCK;
	a[x+15][y+16] = BLOCK;
	a[x+15][y+20] = BLOCK;
	a[x+15][y+23] = BLOCK;
	a[x+16][y+0] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+6] = BLOCK;
	a[x+16][y+7] = BLOCK;
	a[x+16][y+8] = BLOCK;
	a[x+16][y+9] = BLOCK;
	a[x+16][y+10] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+12] = BLOCK;
	a[x+16][y+13] = BLOCK;
	a[x+16][y+15] = BLOCK;
	a[x+16][y+16] = BLOCK;
	a[x+16][y+17] = BLOCK;
	a[x+16][y+18] = BLOCK;
	a[x+16][y+19] = BLOCK;
	a[x+16][y+20] = BLOCK;
	a[x+16][y+22] = BLOCK;
	a[x+16][y+23] = BLOCK;
	a[x+17][y+0] = BLOCK;
	a[x+17][y+3] = BLOCK;
	a[x+17][y+4] = BLOCK;
	a[x+17][y+5] = BLOCK;
	a[x+17][y+8] = BLOCK;
	a[x+17][y+11] = BLOCK;
	a[x+17][y+12] = BLOCK;
	a[x+17][y+14] = BLOCK;
	a[x+17][y+16] = BLOCK;
	a[x+17][y+20] = BLOCK;
	a[x+17][y+21] = BLOCK;
	a[x+17][y+22] = BLOCK;
	a[x+17][y+23] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+8] = BLOCK;
	a[x+18][y+11] = BLOCK;
	a[x+18][y+12] = BLOCK;
	a[x+18][y+16] = BLOCK;
	a[x+18][y+17] = BLOCK;
	a[x+18][y+18] = BLOCK;
	a[x+18][y+19] = BLOCK;
	a[x+18][y+20] = BLOCK;
	a[x+18][y+23] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+2] = BLOCK;
	a[x+19][y+4] = BLOCK;
	a[x+19][y+5] = BLOCK;
	a[x+19][y+6] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+19][y+8] = BLOCK;
	a[x+19][y+10] = BLOCK;
	a[x+19][y+12] = BLOCK;
	a[x+19][y+13] = BLOCK;
	a[x+19][y+14] = BLOCK;
	a[x+19][y+15] = BLOCK;
	a[x+19][y+16] = BLOCK;
	a[x+19][y+20] = BLOCK;
	a[x+19][y+21] = BLOCK;
	a[x+19][y+22] = BLOCK;
	a[x+19][y+23] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+1] = BLOCK;
	a[x+20][y+4] = BLOCK;
	a[x+20][y+8] = BLOCK;
	a[x+20][y+9] = BLOCK;
	a[x+20][y+12] = BLOCK;
	a[x+20][y+13] = BLOCK;
	a[x+20][y+16] = BLOCK;
	a[x+20][y+17] = BLOCK;
	a[x+20][y+18] = BLOCK;
	a[x+20][y+19] = BLOCK;
	a[x+20][y+20] = BLOCK;
	a[x+20][y+23] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+4] = BLOCK;
	a[x+21][y+7] = BLOCK;
	a[x+21][y+8] = BLOCK;
	a[x+21][y+12] = BLOCK;
	a[x+21][y+14] = BLOCK;
	a[x+21][y+15] = BLOCK;
	a[x+21][y+16] = BLOCK;
	a[x+21][y+20] = BLOCK;
	a[x+21][y+23] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+4] = BLOCK;
	a[x+22][y+6] = BLOCK;
	a[x+22][y+8] = BLOCK;
	a[x+22][y+12] = BLOCK;
	a[x+22][y+13] = BLOCK;
	a[x+22][y+15] = BLOCK;
	a[x+22][y+16] = BLOCK;
	a[x+22][y+20] = BLOCK;
	a[x+22][y+21] = BLOCK;
	a[x+22][y+23] = BLOCK;
	a[x+23][y+0] = BLOCK;
	a[x+23][y+1] = BLOCK;
	a[x+23][y+2] = BLOCK;
	a[x+23][y+3] = BLOCK;
	a[x+23][y+4] = BLOCK;
	a[x+23][y+6] = BLOCK;
	a[x+23][y+8] = BLOCK;
	a[x+23][y+9] = BLOCK;
	a[x+23][y+10] = BLOCK;
	a[x+23][y+11] = BLOCK;
	a[x+23][y+12] = BLOCK;
	a[x+23][y+13] = BLOCK;
	a[x+23][y+15] = BLOCK;
	a[x+23][y+16] = BLOCK;
	a[x+23][y+17] = BLOCK;
	a[x+23][y+18] = BLOCK;
	a[x+23][y+19] = BLOCK;
	a[x+23][y+20] = BLOCK;
	a[x+23][y+21] = BLOCK;
	a[x+23][y+23] = BLOCK;
	a[x+24][y+0] = BLOCK;
	a[x+24][y+4] = BLOCK;
	a[x+24][y+5] = BLOCK;
	a[x+24][y+8] = BLOCK;
	a[x+24][y+12] = BLOCK;
	a[x+24][y+15] = BLOCK;
	a[x+24][y+16] = BLOCK;
	a[x+24][y+20] = BLOCK;
	a[x+24][y+22] = BLOCK;
	a[x+24][y+23] = BLOCK;
	a[x+25][y+0] = BLOCK;
	a[x+25][y+1] = BLOCK;
	a[x+25][y+2] = BLOCK;
	a[x+25][y+4] = BLOCK;
	a[x+25][y+5] = BLOCK;
	a[x+25][y+8] = BLOCK;
	a[x+25][y+11] = BLOCK;
	a[x+25][y+12] = BLOCK;
	a[x+25][y+16] = BLOCK;
	a[x+25][y+17] = BLOCK;
	a[x+25][y+18] = BLOCK;
	a[x+25][y+20] = BLOCK;
	a[x+25][y+23] = BLOCK;
	a[x+26][y+0] = BLOCK;
	a[x+26][y+2] = BLOCK;
	a[x+26][y+4] = BLOCK;
	a[x+26][y+5] = BLOCK;
	a[x+26][y+6] = BLOCK;
	a[x+26][y+7] = BLOCK;
	a[x+26][y+8] = BLOCK;
	a[x+26][y+11] = BLOCK;
	a[x+26][y+12] = BLOCK;
	a[x+26][y+13] = BLOCK;
	a[x+26][y+14] = BLOCK;
	a[x+26][y+15] = BLOCK;
	a[x+26][y+16] = BLOCK;
	a[x+26][y+18] = BLOCK;
	a[x+26][y+20] = BLOCK;
	a[x+26][y+21] = BLOCK;
	a[x+26][y+22] = BLOCK;
	a[x+26][y+23] = BLOCK;
	a[x+27][y+0] = BLOCK;
	a[x+27][y+2] = BLOCK;
	a[x+27][y+4] = BLOCK;
	a[x+27][y+8] = BLOCK;
	a[x+27][y+9] = BLOCK;
	a[x+27][y+10] = BLOCK;
	a[x+27][y+12] = BLOCK;
	a[x+27][y+15] = BLOCK;
	a[x+27][y+16] = BLOCK;
	a[x+27][y+20] = BLOCK;
	a[x+27][y+23] = BLOCK;
	a[x+28][y+0] = BLOCK;
	a[x+28][y+1] = BLOCK;
	a[x+28][y+2] = BLOCK;
	a[x+28][y+3] = BLOCK;
	a[x+28][y+4] = BLOCK;
	a[x+28][y+5] = BLOCK;
	a[x+28][y+8] = BLOCK;
	a[x+28][y+12] = BLOCK;
	a[x+28][y+14] = BLOCK;
	a[x+28][y+16] = BLOCK;
	a[x+28][y+20] = BLOCK;
	a[x+28][y+23] = BLOCK;
	a[x+29][y+0] = BLOCK;
	a[x+29][y+4] = BLOCK;
	a[x+29][y+6] = BLOCK;
	a[x+29][y+7] = BLOCK;
	a[x+29][y+8] = BLOCK;
	a[x+29][y+12] = BLOCK;
	a[x+29][y+13] = BLOCK;
	a[x+29][y+14] = BLOCK;
	a[x+29][y+16] = BLOCK;
	a[x+29][y+20] = BLOCK;
	a[x+29][y+22] = BLOCK;
	a[x+29][y+23] = BLOCK;
	a[x+30][y+0] = BLOCK;
	a[x+30][y+1] = BLOCK;
	a[x+30][y+2] = BLOCK;
	a[x+30][y+3] = BLOCK;
	a[x+30][y+4] = BLOCK;
	a[x+30][y+6] = BLOCK;
	a[x+30][y+8] = BLOCK;
	a[x+30][y+9] = BLOCK;
	a[x+30][y+10] = BLOCK;
	a[x+30][y+11] = BLOCK;
	a[x+30][y+12] = BLOCK;
	a[x+30][y+15] = BLOCK;
	a[x+30][y+16] = BLOCK;
	a[x+30][y+17] = BLOCK;
	a[x+30][y+18] = BLOCK;
	a[x+30][y+19] = BLOCK;
	a[x+30][y+20] = BLOCK;
	a[x+30][y+21] = BLOCK;
	a[x+30][y+23] = BLOCK;
	a[x+31][y+0] = BLOCK;
	a[x+31][y+2] = BLOCK;
	a[x+31][y+4] = BLOCK;
	a[x+31][y+8] = BLOCK;
	a[x+31][y+12] = BLOCK;
	a[x+31][y+16] = BLOCK;
	a[x+31][y+17] = BLOCK;
	a[x+31][y+19] = BLOCK;
	a[x+31][y+20] = BLOCK;
	a[x+31][y+23] = BLOCK;
	a[x+32][y+0] = BLOCK;
	a[x+32][y+1] = BLOCK;
	a[x+32][y+2] = BLOCK;
	a[x+32][y+4] = BLOCK;
	a[x+32][y+8] = BLOCK;
	a[x+32][y+12] = BLOCK;
	a[x+32][y+16] = BLOCK;
	a[x+32][y+18] = BLOCK;
	a[x+32][y+20] = BLOCK;
	a[x+32][y+23] = BLOCK;
	a[x+33][y+0] = BLOCK;
	a[x+33][y+1] = BLOCK;
	a[x+33][y+2] = BLOCK;
	a[x+33][y+3] = BLOCK;
	a[x+33][y+4] = BLOCK;
	a[x+33][y+5] = BLOCK;
	a[x+33][y+6] = BLOCK;
	a[x+33][y+7] = BLOCK;
	a[x+33][y+8] = BLOCK;
	a[x+33][y+9] = BLOCK;
	a[x+33][y+10] = BLOCK;
	a[x+33][y+11] = BLOCK;
	a[x+33][y+12] = BLOCK;
	a[x+33][y+13] = BLOCK;
	a[x+33][y+14] = BLOCK;
	a[x+33][y+15] = BLOCK;
	a[x+33][y+16] = BLOCK;
	a[x+33][y+17] = BLOCK;
	a[x+33][y+18] = BLOCK;
	a[x+33][y+19] = BLOCK;
	a[x+33][y+20] = BLOCK;
	a[x+33][y+21] = BLOCK;
	a[x+33][y+22] = BLOCK;
	a[x+33][y+23] = BLOCK;
}

void level_medium(uint8_t a[128][32], uint8_t x, uint8_t y){
	a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+0][y+8] = BLOCK;
	a[x+0][y+9] = BLOCK;
	a[x+0][y+10] = BLOCK;
	a[x+0][y+11] = BLOCK;
	a[x+0][y+12] = BLOCK;
	a[x+0][y+13] = BLOCK;
	a[x+0][y+14] = BLOCK;
	a[x+0][y+15] = BLOCK;
	a[x+0][y+16] = BLOCK;
	a[x+0][y+17] = BLOCK;
	a[x+0][y+18] = BLOCK;
	a[x+0][y+19] = BLOCK;
	a[x+0][y+20] = BLOCK;
	a[x+0][y+21] = BLOCK;
	a[x+0][y+22] = BLOCK;
	a[x+0][y+23] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+1][y+4] = BLOCK;
	a[x+1][y+8] = BLOCK;
	a[x+1][y+12] = BLOCK;
	a[x+1][y+16] = BLOCK;
	a[x+1][y+20] = BLOCK;
	a[x+1][y+23] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+2][y+8] = BLOCK;
	a[x+2][y+12] = BLOCK;
	a[x+2][y+16] = BLOCK;
	a[x+2][y+17] = BLOCK;
	a[x+2][y+18] = BLOCK;
	a[x+2][y+19] = BLOCK;
	a[x+2][y+20] = BLOCK;
	a[x+2][y+23] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+3][y+8] = BLOCK;
	a[x+3][y+11] = BLOCK;
	a[x+3][y+12] = BLOCK;
	a[x+3][y+16] = BLOCK;
	a[x+3][y+20] = BLOCK;
	a[x+3][y+23] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+4] = BLOCK;
	a[x+4][y+8] = BLOCK;
	a[x+4][y+9] = BLOCK;
	a[x+4][y+12] = BLOCK;
	a[x+4][y+16] = BLOCK;
	a[x+4][y+17] = BLOCK;
	a[x+4][y+20] = BLOCK;
	a[x+4][y+23] = BLOCK;
	a[x+5][y+0] = BLOCK;
	a[x+5][y+2] = BLOCK;
	a[x+5][y+4] = BLOCK;
	a[x+5][y+5] = BLOCK;
	a[x+5][y+6] = BLOCK;
	a[x+5][y+7] = BLOCK;
	a[x+5][y+8] = BLOCK;
	a[x+5][y+10] = BLOCK;
	a[x+5][y+12] = BLOCK;
	a[x+5][y+14] = BLOCK;
	a[x+5][y+15] = BLOCK;
	a[x+5][y+16] = BLOCK;
	a[x+5][y+17] = BLOCK;
	a[x+5][y+20] = BLOCK;
	a[x+5][y+21] = BLOCK;
	a[x+5][y+22] = BLOCK;
	a[x+5][y+23] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+8] = BLOCK;
	a[x+6][y+9] = BLOCK;
	a[x+6][y+12] = BLOCK;
	a[x+6][y+16] = BLOCK;
	a[x+6][y+17] = BLOCK;
	a[x+6][y+20] = BLOCK;
	a[x+6][y+23] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+4] = BLOCK;
	a[x+7][y+6] = BLOCK;
	a[x+7][y+7] = BLOCK;
	a[x+7][y+8] = BLOCK;
	a[x+7][y+12] = BLOCK;
	a[x+7][y+15] = BLOCK;
	a[x+7][y+16] = BLOCK;
	a[x+7][y+20] = BLOCK;
	a[x+7][y+23] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+4] = BLOCK;
	a[x+8][y+6] = BLOCK;
	a[x+8][y+8] = BLOCK;
	a[x+8][y+12] = BLOCK;
	a[x+8][y+14] = BLOCK;
	a[x+8][y+16] = BLOCK;
	a[x+8][y+20] = BLOCK;
	a[x+8][y+23] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+1] = BLOCK;
	a[x+9][y+2] = BLOCK;
	a[x+9][y+3] = BLOCK;
	a[x+9][y+4] = BLOCK;
	a[x+9][y+6] = BLOCK;
	a[x+9][y+8] = BLOCK;
	a[x+9][y+9] = BLOCK;
	a[x+9][y+10] = BLOCK;
	a[x+9][y+11] = BLOCK;
	a[x+9][y+12] = BLOCK;
	a[x+9][y+13] = BLOCK;
	a[x+9][y+14] = BLOCK;
	a[x+9][y+16] = BLOCK;
	a[x+9][y+17] = BLOCK;
	a[x+9][y+18] = BLOCK;
	a[x+9][y+19] = BLOCK;
	a[x+9][y+20] = BLOCK;
	a[x+9][y+23] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+10][y+8] = BLOCK;
	a[x+10][y+11] = BLOCK;
	a[x+10][y+12] = BLOCK;
	a[x+10][y+16] = BLOCK;
	a[x+10][y+19] = BLOCK;
	a[x+10][y+20] = BLOCK;
	a[x+10][y+23] = BLOCK;
	a[x+11][y+0] = BLOCK;
	a[x+11][y+4] = BLOCK;
	a[x+11][y+8] = BLOCK;
	a[x+11][y+10] = BLOCK;
	a[x+11][y+12] = BLOCK;
	a[x+11][y+16] = BLOCK;
	a[x+11][y+18] = BLOCK;
	a[x+11][y+20] = BLOCK;
	a[x+11][y+23] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+12][y+8] = BLOCK;
	a[x+12][y+9] = BLOCK;
	a[x+12][y+12] = BLOCK;
	a[x+12][y+13] = BLOCK;
	a[x+12][y+14] = BLOCK;
	a[x+12][y+15] = BLOCK;
	a[x+12][y+16] = BLOCK;
	a[x+12][y+17] = BLOCK;
	a[x+12][y+20] = BLOCK;
	a[x+12][y+21] = BLOCK;
	a[x+12][y+22] = BLOCK;
	a[x+12][y+23] = BLOCK;
	a[x+13][y+0] = BLOCK;
	a[x+13][y+4] = BLOCK;
	a[x+13][y+6] = BLOCK;
	a[x+13][y+8] = BLOCK;
	a[x+13][y+9] = BLOCK;
	a[x+13][y+10] = BLOCK;
	a[x+13][y+12] = BLOCK;
	a[x+13][y+15] = BLOCK;
	a[x+13][y+16] = BLOCK;
	a[x+13][y+20] = BLOCK;
	a[x+13][y+23] = BLOCK;
	a[x+14][y+0] = BLOCK;
	a[x+14][y+4] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+14][y+8] = BLOCK;
	a[x+14][y+11] = BLOCK;
	a[x+14][y+12] = BLOCK;
	a[x+14][y+14] = BLOCK;
	a[x+14][y+16] = BLOCK;
	a[x+14][y+20] = BLOCK;
	a[x+14][y+23] = BLOCK;
	a[x+15][y+0] = BLOCK;
	a[x+15][y+4] = BLOCK;
	a[x+15][y+7] = BLOCK;
	a[x+15][y+8] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+14] = BLOCK;
	a[x+15][y+16] = BLOCK;
	a[x+15][y+20] = BLOCK;
	a[x+15][y+23] = BLOCK;
	a[x+16][y+0] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+6] = BLOCK;
	a[x+16][y+7] = BLOCK;
	a[x+16][y+8] = BLOCK;
	a[x+16][y+9] = BLOCK;
	a[x+16][y+10] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+12] = BLOCK;
	a[x+16][y+13] = BLOCK;
	a[x+16][y+15] = BLOCK;
	a[x+16][y+16] = BLOCK;
	a[x+16][y+17] = BLOCK;
	a[x+16][y+18] = BLOCK;
	a[x+16][y+19] = BLOCK;
	a[x+16][y+20] = BLOCK;
	a[x+16][y+22] = BLOCK;
	a[x+16][y+23] = BLOCK;
	a[x+17][y+0] = BLOCK;
	a[x+17][y+3] = BLOCK;
	a[x+17][y+4] = BLOCK;
	a[x+17][y+5] = BLOCK;
	a[x+17][y+8] = BLOCK;
	a[x+17][y+11] = BLOCK;
	a[x+17][y+12] = BLOCK;
	a[x+17][y+14] = BLOCK;
	a[x+17][y+16] = BLOCK;
	a[x+17][y+20] = BLOCK;
	a[x+17][y+21] = BLOCK;
	a[x+17][y+22] = BLOCK;
	a[x+17][y+23] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+3] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+8] = BLOCK;
	a[x+18][y+11] = BLOCK;
	a[x+18][y+12] = BLOCK;
	a[x+18][y+16] = BLOCK;
	a[x+18][y+17] = BLOCK;
	a[x+18][y+18] = BLOCK;
	a[x+18][y+19] = BLOCK;
	a[x+18][y+20] = BLOCK;
	a[x+18][y+23] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+2] = BLOCK;
	a[x+19][y+4] = BLOCK;
	a[x+19][y+5] = BLOCK;
	a[x+19][y+6] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+19][y+8] = BLOCK;
	a[x+19][y+10] = BLOCK;
	a[x+19][y+12] = BLOCK;
	a[x+19][y+13] = BLOCK;
	a[x+19][y+14] = BLOCK;
	a[x+19][y+15] = BLOCK;
	a[x+19][y+16] = BLOCK;
	a[x+19][y+20] = BLOCK;
	a[x+19][y+21] = BLOCK;
	a[x+19][y+22] = BLOCK;
	a[x+19][y+23] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+1] = BLOCK;
	a[x+20][y+4] = BLOCK;
	a[x+20][y+8] = BLOCK;
	a[x+20][y+9] = BLOCK;
	a[x+20][y+12] = BLOCK;
	a[x+20][y+13] = BLOCK;
	a[x+20][y+16] = BLOCK;
	a[x+20][y+17] = BLOCK;
	a[x+20][y+18] = BLOCK;
	a[x+20][y+19] = BLOCK;
	a[x+20][y+20] = BLOCK;
	a[x+20][y+23] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+4] = BLOCK;
	a[x+21][y+7] = BLOCK;
	a[x+21][y+8] = BLOCK;
	a[x+21][y+12] = BLOCK;
	a[x+21][y+14] = BLOCK;
	a[x+21][y+15] = BLOCK;
	a[x+21][y+16] = BLOCK;
	a[x+21][y+20] = BLOCK;
	a[x+21][y+23] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+4] = BLOCK;
	a[x+22][y+6] = BLOCK;
	a[x+22][y+8] = BLOCK;
	a[x+22][y+12] = BLOCK;
	a[x+22][y+13] = BLOCK;
	a[x+22][y+15] = BLOCK;
	a[x+22][y+16] = BLOCK;
	a[x+22][y+20] = BLOCK;
	a[x+22][y+21] = BLOCK;
	a[x+22][y+23] = BLOCK;
	a[x+23][y+0] = BLOCK;
	a[x+23][y+1] = BLOCK;
	a[x+23][y+2] = BLOCK;
	a[x+23][y+3] = BLOCK;
	a[x+23][y+4] = BLOCK;
	a[x+23][y+6] = BLOCK;
	a[x+23][y+8] = BLOCK;
	a[x+23][y+9] = BLOCK;
	a[x+23][y+10] = BLOCK;
	a[x+23][y+11] = BLOCK;
	a[x+23][y+12] = BLOCK;
	a[x+23][y+13] = BLOCK;
	a[x+23][y+15] = BLOCK;
	a[x+23][y+16] = BLOCK;
	a[x+23][y+17] = BLOCK;
	a[x+23][y+18] = BLOCK;
	a[x+23][y+19] = BLOCK;
	a[x+23][y+20] = BLOCK;
	a[x+23][y+21] = BLOCK;
	a[x+23][y+23] = BLOCK;
	a[x+24][y+0] = BLOCK;
	a[x+24][y+4] = BLOCK;
	a[x+24][y+5] = BLOCK;
	a[x+24][y+8] = BLOCK;
	a[x+24][y+12] = BLOCK;
	a[x+24][y+15] = BLOCK;
	a[x+24][y+16] = BLOCK;
	a[x+24][y+20] = BLOCK;
	a[x+24][y+22] = BLOCK;
	a[x+24][y+23] = BLOCK;
	a[x+25][y+0] = BLOCK;
	a[x+25][y+4] = BLOCK;
	a[x+25][y+8] = BLOCK;
	a[x+25][y+11] = BLOCK;
	a[x+25][y+12] = BLOCK;
	a[x+25][y+16] = BLOCK;
	a[x+25][y+17] = BLOCK;
	a[x+25][y+18] = BLOCK;
	a[x+25][y+20] = BLOCK;
	a[x+25][y+23] = BLOCK;
	a[x+26][y+0] = BLOCK;
	a[x+26][y+4] = BLOCK;
	a[x+26][y+5] = BLOCK;
	a[x+26][y+6] = BLOCK;
	a[x+26][y+7] = BLOCK;
	a[x+26][y+8] = BLOCK;
	a[x+26][y+11] = BLOCK;
	a[x+26][y+12] = BLOCK;
	a[x+26][y+13] = BLOCK;
	a[x+26][y+14] = BLOCK;
	a[x+26][y+15] = BLOCK;
	a[x+26][y+16] = BLOCK;
	a[x+26][y+18] = BLOCK;
	a[x+26][y+20] = BLOCK;
	a[x+26][y+21] = BLOCK;
	a[x+26][y+22] = BLOCK;
	a[x+26][y+23] = BLOCK;
	a[x+27][y+0] = BLOCK;
	a[x+27][y+4] = BLOCK;
	a[x+27][y+8] = BLOCK;
	a[x+27][y+9] = BLOCK;
	a[x+27][y+10] = BLOCK;
	a[x+27][y+12] = BLOCK;
	a[x+27][y+16] = BLOCK;
	a[x+27][y+20] = BLOCK;
	a[x+27][y+23] = BLOCK;
	a[x+28][y+0] = BLOCK;
	a[x+28][y+4] = BLOCK;
	a[x+28][y+8] = BLOCK;
	a[x+28][y+12] = BLOCK;
	a[x+28][y+16] = BLOCK;
	a[x+28][y+20] = BLOCK;
	a[x+28][y+23] = BLOCK;
	a[x+29][y+0] = BLOCK;
	a[x+29][y+4] = BLOCK;
	a[x+29][y+6] = BLOCK;
	a[x+29][y+7] = BLOCK;
	a[x+29][y+8] = BLOCK;
	a[x+29][y+12] = BLOCK;
	a[x+29][y+16] = BLOCK;
	a[x+29][y+20] = BLOCK;
	a[x+29][y+23] = BLOCK;
	a[x+30][y+0] = BLOCK;
	a[x+30][y+1] = BLOCK;
	a[x+30][y+2] = BLOCK;
	a[x+30][y+3] = BLOCK;
	a[x+30][y+4] = BLOCK;
	a[x+30][y+6] = BLOCK;
	a[x+30][y+8] = BLOCK;
	a[x+30][y+9] = BLOCK;
	a[x+30][y+10] = BLOCK;
	a[x+30][y+11] = BLOCK;
	a[x+30][y+12] = BLOCK;
	a[x+30][y+16] = BLOCK;
	a[x+30][y+17] = BLOCK;
	a[x+30][y+18] = BLOCK;
	a[x+30][y+19] = BLOCK;
	a[x+30][y+20] = BLOCK;
	a[x+30][y+23] = BLOCK;
	a[x+31][y+0] = BLOCK;
	a[x+31][y+4] = BLOCK;
	a[x+31][y+8] = BLOCK;
	a[x+31][y+12] = BLOCK;
	a[x+31][y+16] = BLOCK;
	a[x+31][y+20] = BLOCK;
	a[x+31][y+23] = BLOCK;
	a[x+32][y+0] = BLOCK;
	a[x+32][y+4] = BLOCK;
	a[x+32][y+8] = BLOCK;
	a[x+32][y+12] = BLOCK;
	a[x+32][y+16] = BLOCK;
	a[x+32][y+20] = BLOCK;
	a[x+32][y+23] = BLOCK;
	a[x+33][y+0] = BLOCK;
	a[x+33][y+1] = BLOCK;
	a[x+33][y+2] = BLOCK;
	a[x+33][y+3] = BLOCK;
	a[x+33][y+4] = BLOCK;
	a[x+33][y+5] = BLOCK;
	a[x+33][y+6] = BLOCK;
	a[x+33][y+7] = BLOCK;
	a[x+33][y+8] = BLOCK;
	a[x+33][y+9] = BLOCK;
	a[x+33][y+10] = BLOCK;
	a[x+33][y+11] = BLOCK;
	a[x+33][y+12] = BLOCK;
	a[x+33][y+13] = BLOCK;
	a[x+33][y+14] = BLOCK;
	a[x+33][y+15] = BLOCK;
	a[x+33][y+16] = BLOCK;
	a[x+33][y+17] = BLOCK;
	a[x+33][y+18] = BLOCK;
	a[x+33][y+19] = BLOCK;
	a[x+33][y+20] = BLOCK;
	a[x+33][y+21] = BLOCK;
	a[x+33][y+22] = BLOCK;
	a[x+33][y+23] = BLOCK;
}

void level_easy(uint8_t a[128][32], uint8_t x, uint8_t y){
 	a[x+0][y+0] = BLOCK;
	a[x+0][y+1] = BLOCK;
	a[x+0][y+2] = BLOCK;
	a[x+0][y+3] = BLOCK;
	a[x+0][y+4] = BLOCK;
	a[x+0][y+5] = BLOCK;
	a[x+0][y+6] = BLOCK;
	a[x+0][y+7] = BLOCK;
	a[x+0][y+8] = BLOCK;
	a[x+0][y+9] = BLOCK;
	a[x+0][y+10] = BLOCK;
	a[x+0][y+11] = BLOCK;
	a[x+0][y+12] = BLOCK;
	a[x+0][y+13] = BLOCK;
	a[x+0][y+14] = BLOCK;
	a[x+0][y+15] = BLOCK;
	a[x+0][y+16] = BLOCK;
	a[x+0][y+17] = BLOCK;
	a[x+0][y+18] = BLOCK;
	a[x+0][y+19] = BLOCK;
	a[x+0][y+20] = BLOCK;
	a[x+0][y+21] = BLOCK;
	a[x+0][y+22] = BLOCK;
	a[x+0][y+23] = BLOCK;
	a[x+1][y+0] = BLOCK;
	a[x+1][y+4] = BLOCK;
	a[x+1][y+8] = BLOCK;
	a[x+1][y+12] = BLOCK;
	a[x+1][y+16] = BLOCK;
	a[x+1][y+20] = BLOCK;
	a[x+1][y+23] = BLOCK;
	a[x+2][y+0] = BLOCK;
	a[x+2][y+4] = BLOCK;
	a[x+2][y+8] = BLOCK;
	a[x+2][y+12] = BLOCK;
	a[x+2][y+16] = BLOCK;
	a[x+2][y+17] = BLOCK;
	a[x+2][y+18] = BLOCK;
	a[x+2][y+19] = BLOCK;
	a[x+2][y+20] = BLOCK;
	a[x+2][y+23] = BLOCK;
	a[x+3][y+0] = BLOCK;
	a[x+3][y+4] = BLOCK;
	a[x+3][y+8] = BLOCK;
	a[x+3][y+12] = BLOCK;
	a[x+3][y+16] = BLOCK;
	a[x+3][y+20] = BLOCK;
	a[x+3][y+23] = BLOCK;
	a[x+4][y+0] = BLOCK;
	a[x+4][y+4] = BLOCK;
	a[x+4][y+8] = BLOCK;
	a[x+4][y+12] = BLOCK;
	a[x+4][y+16] = BLOCK;
	a[x+4][y+20] = BLOCK;
	a[x+4][y+23] = BLOCK;
	a[x+5][y+0] = BLOCK;
	a[x+5][y+2] = BLOCK;
	a[x+5][y+4] = BLOCK;
	a[x+5][y+5] = BLOCK;
	a[x+5][y+6] = BLOCK;
	a[x+5][y+7] = BLOCK;
	a[x+5][y+8] = BLOCK;
	a[x+5][y+12] = BLOCK;
	a[x+5][y+13] = BLOCK;
	a[x+5][y+14] = BLOCK;
	a[x+5][y+15] = BLOCK;
	a[x+5][y+16] = BLOCK;
	a[x+5][y+20] = BLOCK;
	a[x+5][y+21] = BLOCK;
	a[x+5][y+22] = BLOCK;
	a[x+5][y+23] = BLOCK;
	a[x+6][y+0] = BLOCK;
	a[x+6][y+3] = BLOCK;
	a[x+6][y+4] = BLOCK;
	a[x+6][y+5] = BLOCK;
	a[x+6][y+8] = BLOCK;
	a[x+6][y+12] = BLOCK;
	a[x+6][y+16] = BLOCK;
	a[x+6][y+20] = BLOCK;
	a[x+6][y+23] = BLOCK;
	a[x+7][y+0] = BLOCK;
	a[x+7][y+4] = BLOCK;
	a[x+7][y+6] = BLOCK;
	a[x+7][y+8] = BLOCK;
	a[x+7][y+12] = BLOCK;
	a[x+7][y+16] = BLOCK;
	a[x+7][y+20] = BLOCK;
	a[x+7][y+23] = BLOCK;
	a[x+8][y+0] = BLOCK;
	a[x+8][y+4] = BLOCK;
	a[x+8][y+6] = BLOCK;
	a[x+8][y+8] = BLOCK;
	a[x+8][y+12] = BLOCK;
	a[x+8][y+16] = BLOCK;
	a[x+8][y+20] = BLOCK;
	a[x+8][y+23] = BLOCK;
	a[x+9][y+0] = BLOCK;
	a[x+9][y+1] = BLOCK;
	a[x+9][y+2] = BLOCK;
	a[x+9][y+3] = BLOCK;
	a[x+9][y+4] = BLOCK;
	a[x+9][y+6] = BLOCK;
	a[x+9][y+8] = BLOCK;
	a[x+9][y+9] = BLOCK;
	a[x+9][y+10] = BLOCK;
	a[x+9][y+11] = BLOCK;
	a[x+9][y+12] = BLOCK;
	a[x+9][y+16] = BLOCK;
	a[x+9][y+17] = BLOCK;
	a[x+9][y+18] = BLOCK;
	a[x+9][y+19] = BLOCK;
	a[x+9][y+20] = BLOCK;
	a[x+9][y+23] = BLOCK;
	a[x+10][y+0] = BLOCK;
	a[x+10][y+4] = BLOCK;
	a[x+10][y+7] = BLOCK;
	a[x+10][y+8] = BLOCK;
	a[x+10][y+12] = BLOCK;
	a[x+10][y+16] = BLOCK;
	a[x+10][y+19] = BLOCK;
	a[x+10][y+20] = BLOCK;
	a[x+10][y+23] = BLOCK;
	a[x+11][y+0] = BLOCK;
	a[x+11][y+4] = BLOCK;
	a[x+11][y+8] = BLOCK;
	a[x+11][y+12] = BLOCK;
	a[x+11][y+16] = BLOCK;
	a[x+11][y+18] = BLOCK;
	a[x+11][y+20] = BLOCK;
	a[x+11][y+23] = BLOCK;
	a[x+12][y+0] = BLOCK;
	a[x+12][y+4] = BLOCK;
	a[x+12][y+5] = BLOCK;
	a[x+12][y+6] = BLOCK;
	a[x+12][y+7] = BLOCK;
	a[x+12][y+8] = BLOCK;
	a[x+12][y+12] = BLOCK;
	a[x+12][y+13] = BLOCK;
	a[x+12][y+14] = BLOCK;
	a[x+12][y+15] = BLOCK;
	a[x+12][y+16] = BLOCK;
	a[x+12][y+17] = BLOCK;
	a[x+12][y+20] = BLOCK;
	a[x+12][y+21] = BLOCK;
	a[x+12][y+22] = BLOCK;
	a[x+12][y+23] = BLOCK;
	a[x+13][y+0] = BLOCK;
	a[x+13][y+4] = BLOCK;
	a[x+13][y+6] = BLOCK;
	a[x+13][y+8] = BLOCK;
	a[x+13][y+9] = BLOCK;
	a[x+13][y+10] = BLOCK;
	a[x+13][y+12] = BLOCK;
	a[x+13][y+15] = BLOCK;
	a[x+13][y+16] = BLOCK;
	a[x+13][y+20] = BLOCK;
	a[x+13][y+23] = BLOCK;
	a[x+14][y+0] = BLOCK;
	a[x+14][y+4] = BLOCK;
	a[x+14][y+7] = BLOCK;
	a[x+14][y+8] = BLOCK;
	a[x+14][y+11] = BLOCK;
	a[x+14][y+12] = BLOCK;
	a[x+14][y+14] = BLOCK;
	a[x+14][y+16] = BLOCK;
	a[x+14][y+20] = BLOCK;
	a[x+14][y+23] = BLOCK;
	a[x+15][y+0] = BLOCK;
	a[x+15][y+4] = BLOCK;
	a[x+15][y+7] = BLOCK;
	a[x+15][y+8] = BLOCK;
	a[x+15][y+11] = BLOCK;
	a[x+15][y+12] = BLOCK;
	a[x+15][y+13] = BLOCK;
	a[x+15][y+14] = BLOCK;
	a[x+15][y+16] = BLOCK;
	a[x+15][y+20] = BLOCK;
	a[x+15][y+23] = BLOCK;
	a[x+16][y+0] = BLOCK;
	a[x+16][y+1] = BLOCK;
	a[x+16][y+2] = BLOCK;
	a[x+16][y+3] = BLOCK;
	a[x+16][y+4] = BLOCK;
	a[x+16][y+7] = BLOCK;
	a[x+16][y+8] = BLOCK;
	a[x+16][y+9] = BLOCK;
	a[x+16][y+10] = BLOCK;
	a[x+16][y+11] = BLOCK;
	a[x+16][y+12] = BLOCK;
	a[x+16][y+13] = BLOCK;
	a[x+16][y+15] = BLOCK;
	a[x+16][y+16] = BLOCK;
	a[x+16][y+17] = BLOCK;
	a[x+16][y+18] = BLOCK;
	a[x+16][y+19] = BLOCK;
	a[x+16][y+20] = BLOCK;
	a[x+16][y+22] = BLOCK;
	a[x+16][y+23] = BLOCK;
	a[x+17][y+0] = BLOCK;
	a[x+17][y+4] = BLOCK;
	a[x+17][y+8] = BLOCK;
	a[x+17][y+11] = BLOCK;
	a[x+17][y+12] = BLOCK;
	a[x+17][y+14] = BLOCK;
	a[x+17][y+16] = BLOCK;
	a[x+17][y+20] = BLOCK;
	a[x+17][y+21] = BLOCK;
	a[x+17][y+22] = BLOCK;
	a[x+17][y+23] = BLOCK;
	a[x+18][y+0] = BLOCK;
	a[x+18][y+4] = BLOCK;
	a[x+18][y+8] = BLOCK;
	a[x+18][y+11] = BLOCK;
	a[x+18][y+12] = BLOCK;
	a[x+18][y+16] = BLOCK;
	a[x+18][y+17] = BLOCK;
	a[x+18][y+18] = BLOCK;
	a[x+18][y+19] = BLOCK;
	a[x+18][y+20] = BLOCK;
	a[x+18][y+23] = BLOCK;
	a[x+19][y+0] = BLOCK;
	a[x+19][y+4] = BLOCK;
	a[x+19][y+5] = BLOCK;
	a[x+19][y+6] = BLOCK;
	a[x+19][y+7] = BLOCK;
	a[x+19][y+8] = BLOCK;
	a[x+19][y+10] = BLOCK;
	a[x+19][y+12] = BLOCK;
	a[x+19][y+13] = BLOCK;
	a[x+19][y+14] = BLOCK;
	a[x+19][y+15] = BLOCK;
	a[x+19][y+16] = BLOCK;
	a[x+19][y+20] = BLOCK;
	a[x+19][y+21] = BLOCK;
	a[x+19][y+22] = BLOCK;
	a[x+19][y+23] = BLOCK;
	a[x+20][y+0] = BLOCK;
	a[x+20][y+4] = BLOCK;
	a[x+20][y+8] = BLOCK;
	a[x+20][y+9] = BLOCK;
	a[x+20][y+12] = BLOCK;
	a[x+20][y+13] = BLOCK;
	a[x+20][y+16] = BLOCK;
	a[x+20][y+20] = BLOCK;
	a[x+20][y+23] = BLOCK;
	a[x+21][y+0] = BLOCK;
	a[x+21][y+4] = BLOCK;
	a[x+21][y+7] = BLOCK;
	a[x+21][y+8] = BLOCK;
	a[x+21][y+12] = BLOCK;
	a[x+21][y+14] = BLOCK;
	a[x+21][y+15] = BLOCK;
	a[x+21][y+16] = BLOCK;
	a[x+21][y+20] = BLOCK;
	a[x+21][y+23] = BLOCK;
	a[x+22][y+0] = BLOCK;
	a[x+22][y+4] = BLOCK;
	a[x+22][y+6] = BLOCK;
	a[x+22][y+8] = BLOCK;
	a[x+22][y+12] = BLOCK;
	a[x+22][y+15] = BLOCK;
	a[x+22][y+16] = BLOCK;
	a[x+22][y+20] = BLOCK;
	a[x+22][y+23] = BLOCK;
	a[x+23][y+0] = BLOCK;
	a[x+23][y+1] = BLOCK;
	a[x+23][y+2] = BLOCK;
	a[x+23][y+3] = BLOCK;
	a[x+23][y+4] = BLOCK;
	a[x+23][y+6] = BLOCK;
	a[x+23][y+8] = BLOCK;
	a[x+23][y+9] = BLOCK;
	a[x+23][y+10] = BLOCK;
	a[x+23][y+11] = BLOCK;
	a[x+23][y+12] = BLOCK;
	a[x+23][y+15] = BLOCK;
	a[x+23][y+16] = BLOCK;
	a[x+23][y+17] = BLOCK;
	a[x+23][y+18] = BLOCK;
	a[x+23][y+19] = BLOCK;
	a[x+23][y+20] = BLOCK;
	a[x+23][y+23] = BLOCK;
	a[x+24][y+0] = BLOCK;
	a[x+24][y+4] = BLOCK;
	a[x+24][y+5] = BLOCK;
	a[x+24][y+8] = BLOCK;
	a[x+24][y+12] = BLOCK;
	a[x+24][y+15] = BLOCK;
	a[x+24][y+16] = BLOCK;
	a[x+24][y+20] = BLOCK;
	a[x+24][y+23] = BLOCK;
	a[x+25][y+0] = BLOCK;
	a[x+25][y+4] = BLOCK;
	a[x+25][y+8] = BLOCK;
	a[x+25][y+12] = BLOCK;
	a[x+25][y+16] = BLOCK;
	a[x+25][y+17] = BLOCK;
	a[x+25][y+18] = BLOCK;
	a[x+25][y+20] = BLOCK;
	a[x+25][y+23] = BLOCK;
	a[x+26][y+0] = BLOCK;
	a[x+26][y+4] = BLOCK;
	a[x+26][y+5] = BLOCK;
	a[x+26][y+6] = BLOCK;
	a[x+26][y+7] = BLOCK;
	a[x+26][y+8] = BLOCK;
	a[x+26][y+12] = BLOCK;
	a[x+26][y+13] = BLOCK;
	a[x+26][y+14] = BLOCK;
	a[x+26][y+15] = BLOCK;
	a[x+26][y+16] = BLOCK;
	a[x+26][y+18] = BLOCK;
	a[x+26][y+20] = BLOCK;
	a[x+26][y+21] = BLOCK;
	a[x+26][y+22] = BLOCK;
	a[x+26][y+23] = BLOCK;
	a[x+27][y+0] = BLOCK;
	a[x+27][y+4] = BLOCK;
	a[x+27][y+8] = BLOCK;
	a[x+27][y+12] = BLOCK;
	a[x+27][y+16] = BLOCK;
	a[x+27][y+20] = BLOCK;
	a[x+27][y+23] = BLOCK;
	a[x+28][y+0] = BLOCK;
	a[x+28][y+4] = BLOCK;
	a[x+28][y+8] = BLOCK;
	a[x+28][y+12] = BLOCK;
	a[x+28][y+16] = BLOCK;
	a[x+28][y+20] = BLOCK;
	a[x+28][y+23] = BLOCK;
	a[x+29][y+0] = BLOCK;
	a[x+29][y+4] = BLOCK;
	a[x+29][y+8] = BLOCK;
	a[x+29][y+12] = BLOCK;
	a[x+29][y+16] = BLOCK;
	a[x+29][y+20] = BLOCK;
	a[x+29][y+23] = BLOCK;
	a[x+30][y+0] = BLOCK;
	a[x+30][y+1] = BLOCK;
	a[x+30][y+2] = BLOCK;
	a[x+30][y+3] = BLOCK;
	a[x+30][y+4] = BLOCK;
	a[x+30][y+8] = BLOCK;
	a[x+30][y+9] = BLOCK;
	a[x+30][y+10] = BLOCK;
	a[x+30][y+11] = BLOCK;
	a[x+30][y+12] = BLOCK;
	a[x+30][y+16] = BLOCK;
	a[x+30][y+17] = BLOCK;
	a[x+30][y+18] = BLOCK;
	a[x+30][y+19] = BLOCK;
	a[x+30][y+20] = BLOCK;
	a[x+30][y+23] = BLOCK;
	a[x+31][y+0] = BLOCK;
	a[x+31][y+4] = BLOCK;
	a[x+31][y+8] = BLOCK;
	a[x+31][y+12] = BLOCK;
	a[x+31][y+16] = BLOCK;
	a[x+31][y+20] = BLOCK;
	a[x+31][y+23] = BLOCK;
	a[x+32][y+0] = BLOCK;
	a[x+32][y+4] = BLOCK;
	a[x+32][y+8] = BLOCK;
	a[x+32][y+12] = BLOCK;
	a[x+32][y+16] = BLOCK;
	a[x+32][y+20] = BLOCK;
	a[x+32][y+23] = BLOCK;
	a[x+33][y+0] = BLOCK;
	a[x+33][y+1] = BLOCK;
	a[x+33][y+2] = BLOCK;
	a[x+33][y+3] = BLOCK;
	a[x+33][y+4] = BLOCK;
	a[x+33][y+5] = BLOCK;
	a[x+33][y+6] = BLOCK;
	a[x+33][y+7] = BLOCK;
	a[x+33][y+8] = BLOCK;
	a[x+33][y+9] = BLOCK;
	a[x+33][y+10] = BLOCK;
	a[x+33][y+11] = BLOCK;
	a[x+33][y+12] = BLOCK;
	a[x+33][y+13] = BLOCK;
	a[x+33][y+14] = BLOCK;
	a[x+33][y+15] = BLOCK;
	a[x+33][y+16] = BLOCK;
	a[x+33][y+17] = BLOCK;
	a[x+33][y+18] = BLOCK;
	a[x+33][y+19] = BLOCK;
	a[x+33][y+20] = BLOCK;
	a[x+33][y+21] = BLOCK;
	a[x+33][y+22] = BLOCK;
	a[x+33][y+23] = BLOCK;

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
