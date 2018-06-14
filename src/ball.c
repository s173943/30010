#include "ball.h"
#include "lcd.h"

void initVector(struct vector_t *v, int32_t x, int32_t y) {
    v->x = x << FIX14_SHIFT;
    v->y = y << FIX14_SHIFT;
}

void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy) {
    initVector(&(b->pos), x, y);
    initVector(&(b->vel), vx, vy);
    b->hits = 0;
}

void drawBall(struct ball_t *b, uint8_t hx, uint8_t hy) {
    gotoxy((b->pos).x >> FIX14_SHIFT,(b->pos).y >> FIX14_SHIFT);
    printf("%c", 111);
    gotoxy(hx, hy);
    printf("%d", b->hits);
}

void removeBall(struct ball_t *b) {
    gotoxy((b->pos).x >> FIX14_SHIFT, (b->pos).y >> FIX14_SHIFT);
    printf(" ");
}

void lvl1(uint8_t x, uint8_t y, uint8_t playingField[128][32]){

    for(int8_t i = x; i<60; i+=3){
            for(int8_t j = y; j<20; j+=4){
                drawBrick(i, j, playingField);
            }
    }


}

void drawBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32]){
    uint8_t vChar, hChar, dlcChar, drcChar, tlcChar, trcChar, i, j;
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



void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32]){
    int32_t cx, cy, yy, len;
    int8_t i, j;
    int8_t strikerLeft, strikerRight;
    cx = (b->pos).x + (b->vel).x;
    cy = (b->pos).y + (b->vel).y;
    len = 2;
    /*
    gotoxy(50, 10);
    printFix((b->vel).x);
    gotoxy(50, 11);
    printFix((b->vel).y);
    gotoxy(50, 13);
    printFix(MINVELX); //Burde printe 0.09425 laveste boldhastighed?
    gotoxy(50, 14);
    printFix(MINVElY); //Burde printe 0.34077 laveste boldhastighed?

*/

    if (cy <= ((y1+1) << FIX14_SHIFT) || cy >= ((y2-1) << FIX14_SHIFT)){ //bolden rammer top/bund
        (b->vel).y = -((b->vel).y);
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }

    if (cx <= ((x1) << FIX14_SHIFT) || cx >= ((x2) << FIX14_SHIFT)){ //når bolden rammer en striker
        uint8_t q= 1; //ser om vi er til venstre eller højre. Hvis leftOrRight er 1, er vi til venstre.
        uint8_t leftOrRight = ((cx <= ((x1+1) << FIX14_SHIFT))?1:0);
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
/*
        gotoxy(50, 25);
        printf("%03d", strikerLeft);
        gotoxy(50, 26);
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
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -85);
            }else{
                rotate(&(b->vel), 85);
                }

        }
        else if((leftOrRight)?(cy > ((len+strikerLeft) << FIX14_SHIFT) && cy <= (((len*2)+strikerLeft) << FIX14_SHIFT)):(cy > ((len+strikerRight) << FIX14_SHIFT) && cy <= (((len*2)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -107);
            }else{
                rotate(&(b->vel), 107);
            }

        }
        else if((leftOrRight)?(cy > (((len*2)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*3)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*2)+strikerRight) << FIX14_SHIFT) && cy <= (((len*3)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
                (b->vel).x = -((b->vel).x);

        }
        else if((leftOrRight)?(cy > (((len*3)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*4)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*3)+strikerRight) << FIX14_SHIFT) && cy <= (((len*4)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
             if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -149);
            }else{
                rotate(&(b->vel), 149);
            }

        }
        else if((leftOrRight)?(cy > (((len*4)+strikerLeft) << FIX14_SHIFT) && cy < ((len*5)+strikerLeft) << FIX14_SHIFT):(cy > (((len*4)+strikerRight) << FIX14_SHIFT) && cy <= (((len*5)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -171);
            }else{
                rotate(&(b->vel), 171);
            }
        }
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }

    if(cx < ((x1) << FIX14_SHIFT) || cx > ((x2) << FIX14_SHIFT)){ //uden for strikeren
            cx = 40 << FIX14_SHIFT;
            cy = 20 << FIX14_SHIFT;
    }


    i = cx >> FIX14_SHIFT;
    j = cy >> FIX14_SHIFT;

    if(playingField[i][j] != 0 && cy >= ((y1+2) << FIX14_SHIFT) && cy <= ((y2-2) << FIX14_SHIFT) && cx >= ((x1+2) << FIX14_SHIFT) && cx <= ((x2-2) << FIX14_SHIFT)){ //når bolden rammer en brick
    gotoxy(101, 20);
    printf("Test1");
        if(playingField[i][j]==196){
            printf("%c", playingField[i][j]);
            while(playingField[i][j] != 192 && playingField[i][j] != 218){
                i--;
                gotoxy(101, 21);
                printf("Test2");
            }if(playingField[i][j] == 192){
                gotoxy(101, 22);
                printf("Test3");
                while(playingField[i][j] != 218){
                    j--;
                }
                removeBrick(i, j, playingField);
            }else if(playingField[i][j] == 218){
                removeBrick(i, j, playingField);
            }

            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;

        }
        else if(playingField[i][j] == 179){
            while(playingField[i][j] != 218 && playingField[i][j] != 191){
                j--;
                 gotoxy(101, 23);
                printf("Test4");
            }if(playingField[i][j] == 191){
                while(playingField[i][j] != 218){
                    i--;

                 gotoxy(101, 24);
                printf("Test5");
                }
                removeBrick(i, j, playingField);
            }else if(playingField[i][j] == 218){
                removeBrick(i, j, playingField);
            }
            (b->vel).x = -((b->vel).x);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }else if(playingField[i][j] == 192){
            while(playingField[i][j] != 218){
                j--;
                 gotoxy(101, 23);
                printf("Test4");
            }
            removeBrick(i, j, playingField);
           (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }

        else if(playingField[i][j] == 218){
            removeBrick(i, j, playingField);
            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;


        }else if(playingField[i][j] == 191){
            while(playingField[i][j] != 218){
                i--;
                 gotoxy(101, 23);
                printf("Test4");
            }
            removeBrick(i, j, playingField);
            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }else if(playingField[i][j] == 217){
            while(playingField[i][j] != 192){
                i--;
                gotoxy(101, 21);
                printf("Test2");
            }
            while(playingField[i][j] != 218){
                    j--;
            }
            removeBrick(i, j, playingField);
            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }




    }

    (b->pos).x = cx;
    (b->pos).y = cy;

}

void removeBrick(uint8_t x, uint8_t y, uint8_t playingField[128][32]) {
    uint8_t i, j;
                     gotoxy(101, 25);
                printf("Test6");
    for(i = x; i < x+3; i++){
        for(j = y; j < y+4; j++){
            playingField[i][j] = 0;
        }
    }
}

void ballToArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 111;
}

void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 0;
}

