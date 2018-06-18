#include "ball.h"
#include "lcd.h"
#include "pin_io.h"

void initVector(struct vector_t *v, int32_t x, int32_t y) {
    v->x = x << FIX14_SHIFT;
    v->y = y << FIX14_SHIFT;
}

void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy, uint8_t aliveOrDead){
    initVector(&(b->pos), x, y);
    initVector(&(b->vel), vx, vy);
    (b->state) = aliveOrDead;
}

void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy) {
    gotoxy((b->pos).x >> FIX14_SHIFT,(b->pos).y >> FIX14_SHIFT);
    printf("%c", 111);
    gotoxy(hx, hy);
}

void removeBall(struct ball_t *b) {
    gotoxy((b->pos).x >> FIX14_SHIFT, (b->pos).y >> FIX14_SHIFT);
    printf(" ");
}

void lvl1(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives){
    for(int8_t i = x; i<60; i+=3){
        for(int8_t j = y; j<20; j+=4){
            drawBrick(i, j, playingField, bricks);
            (*bricks)++;
        }
    }
}

void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks){
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

void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives, uint8_t *score){
    int32_t cx, cy, len;
    int8_t i, j, strikerLeft, strikerRight;
    uint8_t leftOrRight, q;
    for(q=1; q<32; q++){
        if (playingField[0][q] == 179){
            strikerLeft = q;
            break;
        }
    }

    for(q=1; q<32; q++){
        if (playingField[100][q] == 179){
            strikerRight = q;
            break;
        }
    }
    cx = (b->pos).x + (b->vel).x;
    cy = (b->pos).y + (b->vel).y;
    leftOrRight = ((cx <= ((x1+1) << FIX14_SHIFT))?1:0);     //ser om vi er til venstre eller h�jre. Hvis leftOrRight er 1, er vi til venstre.
    len = 2;

    gotoxy(110, 10);
    printFix((b->vel).x);
    gotoxy(110, 11);
    printFix((b->vel).y);
    gotoxy(110, 12);
    printf("%02d", strikerLeft);
    gotoxy(110, 13);
    printf("%02d", strikerRight);
    gotoxy(110, 14);
    printf("%02d", leftOrRight);

    /*
    gotoxy(50, 13);
    printFix(MINVELX); //Burde printe 0.09425 laveste boldhastighed?
    gotoxy(50, 14);
    printFix(MINVElY); //Burde printe 0.34077 laveste boldhastighed?

    */
    if(b->state == 0){ //hvis bolden er doed ved venstre playa
        initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
        if(readJoystick() & (0x001 << 3)){
            initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
        }
        else if(readJoystick() & (0x001 << 0)){
            initBall(b, x1+1, 5+strikerLeft, 1, 1, 2);
            rotate(&(b->vel), -64);
        }
    }
    if(b->state == 1){ //hvis bolden er doed ved h�jre playa
        initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
        if(readJoystick() & (0x001 << 2)){
            initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
        }
        else if(readJoystick() & (0x001 << 0)){
            initBall(b, x2-1, 5+strikerRight, -1, 1, 2);
            rotate(&(b->vel), 64);
        }
    }
    else if((b->state) == 2){
        if (cy <= ((y1+1) << FIX14_SHIFT) || cy >= ((y2-1) << FIX14_SHIFT)){ //bolden rammer top/bund
            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }

        if (cx <= ((x1) << FIX14_SHIFT) || cx >= ((x2) << FIX14_SHIFT)){ //n�r bolden rammer en strike
    /*
            gotoxy(105, 25);
            printf("%03d", strikerLeft);
            gotoxy(105, 26);
            printf("%03d", strikerRight);

            gotoxy(50, 17);
            printf("          ");
            gotoxy(50, 18);
            printf("          ");
            gotoxy(50, 19);
            printf("          ");
            gotoxy(50, 20);
            printf("          ");
            gotoxy(50, 21);
            printf("          ");
            */
            if((leftOrRight)?(cy > ((strikerLeft) << FIX14_SHIFT) && cy <= ((len+strikerLeft) << FIX14_SHIFT)):(cy > (strikerRight << FIX14_SHIFT) && cy <= ((len+strikerRight) << FIX14_SHIFT))){  //toppen, tjekker
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ //tjekker om det er h�jre eller venstre. 1 er venstre, 0 er h�jre.
                    rotate(&(b->vel), -43);
                }else{
                    rotate(&(b->vel), 43);
                    }
                /*
                if(leftOrRight){ //vinklen er for lille
                    if((b->vel).x<0){
                        (b->vel).x = -(b->vel).x;
                    }
                }else{
                    if((b->vel).x>0){
                        (b->vel).x = -(b->vel).x;
                    }
                }*/

                gotoxy(110, 20);
                printf("hit top");
            }
            else if((leftOrRight)?(cy > ((len+strikerLeft) << FIX14_SHIFT) && cy <= (((len*2)+strikerLeft) << FIX14_SHIFT)):(cy > ((len+strikerRight) << FIX14_SHIFT) && cy <= (((len*2)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ //tjekker om det er h�jre eller venstre. 1 er venstre, 0 er h�jre.
                    rotate(&(b->vel), -21);
                }else{
                    rotate(&(b->vel), 21);
                }
                /*
                if(leftOrRight){ //vinklen er for lille
                    if((b->vel).x<0){
                        (b->vel).x = -(b->vel).x;
                    }
                }else{
                    if((b->vel).x>0){
                        (b->vel).x = -(b->vel).x;
                    }
                }*/
                gotoxy(110, 21);
                printf("hit midtop");
            }
            else if((leftOrRight)?(cy > (((len*2)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*3)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*2)+strikerRight) << FIX14_SHIFT) && cy <= (((len*3)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                (b->vel).x = -((b->vel).x);
                gotoxy(110, 22);
                printf("hit mid");
            }
            else if((leftOrRight)?(cy > (((len*3)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*4)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*3)+strikerRight) << FIX14_SHIFT) && cy <= (((len*4)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                 (b->vel).x = -((b->vel).x);
                 if(leftOrRight){ //tjekker om det er h�jre eller venstre. 1 er venstre, 0 er h�jre.
                    rotate(&(b->vel), 21);
                }else{
                    rotate(&(b->vel), -21);
                }
                /*
                if(leftOrRight){ //vinklen er for lille
                    if((b->vel).x<0){
                        (b->vel).x = -(b->vel).x;
                    }
                }else{
                    if((b->vel).x>0){
                        (b->vel).x = -(b->vel).x;
                    }
                }*/
                gotoxy(110, 23);
                printf("hit midbot");
            }
            else if((leftOrRight)?(cy > (((len*4)+strikerLeft) << FIX14_SHIFT) && cy < ((len*5)+strikerLeft) << FIX14_SHIFT):(cy > (((len*4)+strikerRight) << FIX14_SHIFT) && cy <= (((len*5)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ //tjekker om det er h�jre eller venstre. 1 er venstre, 0 er h�jre.
                    rotate(&(b->vel), 43);
                }else{
                    rotate(&(b->vel), -43);
                }
                /*
                if(leftOrRight){ //vinklen er for lille
                    if((b->vel).x<0){
                        (b->vel).x = -(b->vel).x;
                    }
                }else{
                    if((b->vel).x>0){
                        (b->vel).x = -(b->vel).x;
                    }
                }*/
                gotoxy(110, 24);
                printf("hit bot");
            }
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;

            if(cx < ((x1) << FIX14_SHIFT)){ //uden for venstre striker
                initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
            }
            else if(cx > ((x2) << FIX14_SHIFT)){ //uden for h�jre striker
                initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
            }

        }

        i = cx >> FIX14_SHIFT;
        j = cy >> FIX14_SHIFT;

        if(playingField[i][j] != 0 && cy >= ((y1+2) << FIX14_SHIFT) && cy <= ((y2-2) << FIX14_SHIFT) && cx >= ((x1+2) << FIX14_SHIFT) && cx <= ((x2-2) << FIX14_SHIFT)){ //n�r bolden rammer en brick
        gotoxy(115, 15);
        printf("%c", playingField[i][j]);
            if(playingField[i][j]==196){ //n�r bolden rammer en vandret streg
                while(playingField[i][j] != 192 && playingField[i][j] != 218){
                    i--;
                }if(playingField[i][j] == 192){
                    while(playingField[i][j] != 218){
                        j--;
                    }
                    removeBrick(i, j, playingField, bricks);
                }else if(playingField[i][j] == 218){
                    removeBrick(i, j, playingField, bricks);
                }
                (b->vel).y = -((b->vel).y);
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;

            }

            else if(playingField[i][j] == 179){ //n�r bolden rammer en lodret streg
                while(playingField[i][j] != 218 && playingField[i][j] != 191){
                    j--;
                }if(playingField[i][j] == 191){
                    while(playingField[i][j] != 218){
                        i--;
                    }
                    removeBrick(i, j, playingField, bricks);
                }else if(playingField[i][j] == 218){
                    removeBrick(i, j, playingField, bricks);
                }
                (b->vel).x = -((b->vel).x);
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
            }else if(playingField[i][j] == 192){ //n�r bolden rammer det nederste venstre hjoerne
                if(playingField[i-1][j] == 217){ //Tjekker om de naerliggende bricks ligger vandret eller lodret
                    (b->vel).y = -((b->vel).y);
                }
                if(playingField[i][j+1] == 218){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if((b->vel).x<0 && (b->vel).y>0){ //if the ball hits the brick in an upward-left velocity
                        (b->vel).y = -((b->vel).y);
                    }
                    if((b->vel).x>0 && (b->vel).y<0){ //if the ball hits the brick in an downward-right velocity
                        (b->vel).x = -((b->vel).x);
                    }else{
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }

                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
                while(playingField[i][j] != 218){
                    j--;
                }
                removeBrick(i, j, playingField, bricks);
            }

            else if(playingField[i][j] == 218){ //n�r bolden rammer det oeverste venstre hjoerne
                if(playingField[i-1][j] == 191){ //Tjekker om de naerliggende bricks ligger vandret eller lodret
                    (b->vel).y = -((b->vel).y);
                }
                if(playingField[i][j-1] == 192){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if((b->vel).x<0 && (b->vel).y<0){ //if the ball hits the brick in an downward-left velocity
                        (b->vel).y = -((b->vel).y);
                    }if((b->vel).x>0 && (b->vel).y>0){ //if the ball hits the brick in an upward-right velocity
                        (b->vel).x = -((b->vel).x);
                    }else{
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                removeBrick(i, j, playingField, bricks);

                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;


            }else if(playingField[i][j] == 191){ //n�r bolden rammer det oeverste hoejre hjoerne
                if(playingField[i+1][j] == 218){ //Tjekker om de naerliggende bricks ligger vandret eller lodret
                    (b->vel).y = -((b->vel).y);
                }
                if(playingField[i][j-1] == 217){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if((b->vel).x<0 && (b->vel).y>0){ //if the ball hits the brick in an upward-left velocity
                        (b->vel).x = -((b->vel).x);
                    }if((b->vel).x>0 && (b->vel).y<0){ //if the ball hits the brick in an downward-right velocity
                        (b->vel).y = -((b->vel).y);
                    }else{
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;

                while(playingField[i][j] != 218){
                    i--;
                }
                removeBrick(i, j, playingField, bricks);
            }else if(playingField[i][j] == 217){ //n�r bolden rammer det nederste hoejre hjoerne
                if(playingField[i+1][j] == 192){ //Tjekker om de naerliggende bricks ligger vandret eller lodret
                    (b->vel).y = -((b->vel).y);
                }
                if(playingField[i][j+1] == 191){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if((b->vel).x<0 && (b->vel).y<0){ //if the ball hits the brick in an downward-left velocity
                        (b->vel).x = -((b->vel).x);
                    }if((b->vel).x>0 && (b->vel).y>0){ //if the ball hits the brick in an upward-right velocity
                        (b->vel).y = -((b->vel).y);
                    }else{
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
                while(playingField[i][j] != 192){
                    i--;
                }
                while(playingField[i][j] != 218){
                    j--;
                }
                removeBrick(i, j, playingField, bricks);

            }
        }
        (b->pos).x = cx; //boldens position bliver opdateret.
        (b->pos).y = cy;

    }
}





void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32], uint8_t *bricks) {
    uint8_t i, j;
            gotoxy(101, 25);
            //printf("Test6");
    for(i = x; i < x+3; i++){
        for(j = y; j < y+4; j++){
            playingField[i][j] = 0;
        }
    }
    (*bricks)--;
}

void ballToArray(struct ball_t *b, uint8_t playingField[128][32]){
    if(playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] == 0){
        playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 111;
    }
}

void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 0;
}
