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

void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32]){
    int32_t cx, cy, yy, len;
    int8_t strikerLeft, strikerRight;
    cx = (b->pos).x + (b->vel).x;
    cy = (b->pos).y + (b->vel).y;
    len = 2;

    if (cy <= ((y1+1) << FIX14_SHIFT) || cy >= ((y2-1) << FIX14_SHIFT)){ //bolden rammer top/bund
        (b->vel).y = -((b->vel).y);
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }

    if (cx <= ((x1) << FIX14_SHIFT) || cx >= ((x2) << FIX14_SHIFT)){ //når bolden rammer en striker
        uint8_t i= 1; //ser om vi er til venstre eller højre. Hvis leftOrRight er 1, er vi til venstre.
        uint8_t leftOrRight = ((cx <= ((x1+1) << FIX14_SHIFT))?1:0);
        for(i=1; i<32; i++){
            if (playingField[0][i] == 179){
                strikerLeft = i;
              break;
            }
        }
        for(i=1; i<32; i++){
            if (playingField[100][i] == 179){
                strikerRight = i;
              break;
            }
        }

        if((leftOrRight)?(cy > ((strikerLeft) << FIX14_SHIFT) && cy <= ((len+strikerLeft) << FIX14_SHIFT)):(cy > (strikerRight << FIX14_SHIFT) && cy <= ((len+strikerRight) << FIX14_SHIFT))){  //toppen, tjekker
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -85);
            }else{
                rotate(&(b->vel), 85);
                }
            gotoxy(50, 17);
            printf("hit top");
        }
        else if((leftOrRight)?(cy > ((len+strikerLeft) << FIX14_SHIFT) && cy <= (((len*2)+strikerLeft) << FIX14_SHIFT)):(cy > ((len+strikerRight) << FIX14_SHIFT) && cy <= (((len*2)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -107);
            }else{
                rotate(&(b->vel), 107);
            }
            gotoxy(50, 18);
            printf("hit midtop");
        }
        else if((leftOrRight)?(cy > (((len*2)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*3)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*2)+strikerRight) << FIX14_SHIFT) && cy <= (((len*3)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
                (b->vel).x = -((b->vel).x);
                gotoxy(50, 19);
                printf("hit mid");
        }
        else if((leftOrRight)?(cy > (((len*3)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*4)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*3)+strikerRight) << FIX14_SHIFT) && cy <= (((len*4)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
             if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -149);
            }else{
                rotate(&(b->vel), 149);
            }
            gotoxy(50, 20);
            printf("hit midbot");
        }
        else if((leftOrRight)?(cy > (((len*4)+strikerLeft) << FIX14_SHIFT) && cy < ((len*5)+strikerLeft) << FIX14_SHIFT):(cy > (((len*4)+strikerRight) << FIX14_SHIFT) && cy <= (((len*5)+strikerRight) << FIX14_SHIFT))){  //nestøverste, tjekker
            if((leftOrRight)?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre. 0 er venstre, 1 er højre.
                rotate(&(b->vel), -171);
            }else{
                rotate(&(b->vel), 171);
            }
            gotoxy(50, 21);
            printf("%s", "hit bottom");
        }
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }

    if(cx < ((x1) << FIX14_SHIFT) || cx > ((x2) << FIX14_SHIFT)){ //uden for strikeren
            cx = 40 << FIX14_SHIFT;
            cy = 20 << FIX14_SHIFT;
    }


    if (playingField[cx][cy] == 111){ //bolden rammer top/bund
        (b->vel).x = -((b->vel).x);
        (b->vel).y = -((b->vel).y);
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }

    (b->pos).x = cx;
    (b->pos).y = cy;

}

void ballToArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 111;
}

void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 0;
}

