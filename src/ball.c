#include "ball.h"

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

void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    int32_t cx, cy, k = 1, len;
    len = (y2-y1)/5;

    cx = (b->pos).x + (b->vel).x;
    cy = (b->pos).y + (b->vel).y;


    if (cy <= ((y1+1) << FIX14_SHIFT) || cy >= ((y2) << FIX14_SHIFT)){ //bolden rammer top/bund
        (b->vel).y = -((b->vel).y);
        cx = (b->pos).x + (b->vel).x;
        cy = (b->pos).y + (b->vel).y;
    }



    if (cx <= ((x1+1) << FIX14_SHIFT) || cx >= ((x2-1) << FIX14_SHIFT)){ //når bolden rammer en striker
        /*gotoxy(50, 17);
        printf("          ");
        gotoxy(50, 18);
        printf("          ");
        gotoxy(50, 19);
        printf("          ");
        gotoxy(50, 20);
        printf("          ");
        gotoxy(50, 21);
        printf("          ");*/
        if(cy > ((y1) << FIX14_SHIFT) && cy <= ((len+y1) << FIX14_SHIFT)){  //toppen

            if((cx <= ((x1+1) << FIX14_SHIFT))?((b->vel).y>0):((b->vel).y<0)){ //tjekker om det er højre eller venstre
                rotate(&(b->vel), -85);
            }else{
                rotate(&(b->vel), 85);
                }
            gotoxy(50, 17);
            printf("hit top");
        }
        if(cy > (len+(y1)) && cy <= ((len*2)+(y1) << FIX14_SHIFT)){ //den næstøverste del
             if((cx <= ((x1+1) << FIX14_SHIFT))?((b->vel).y>0):((b->vel).y<0)){
                    rotate(&(b->vel), -107);
                }else{
                    rotate(&(b->vel), 107);
                }
            gotoxy(50, 18);
            printf("hit midtop");
            }
        if(cy > ((len*2)+(y1) << FIX14_SHIFT) && cy <= ((len*3)+(y1) << FIX14_SHIFT)){ //midten
                (b->vel).x = -((b->vel).x);
                gotoxy(50, 19);
                printf("hit mid");
        }
        if(cy > ((len*3)+(y1) << FIX14_SHIFT) && cy <= ((len*4)+(y1) << FIX14_SHIFT)){//den nestnederste del
             if((cx <= ((x1+1) << FIX14_SHIFT))?((b->vel).y>0):((b->vel).y<0)){
                rotate(&(b->vel), -149);
            }else{
                rotate(&(b->vel), 149);
            }
            gotoxy(50, 20);
            printf("hit midbot");
        }
        if(cy > (((len*4)+(y1)) << FIX14_SHIFT) && cy < (y2 << FIX14_SHIFT)){   //bunden
            if((cx <= ((x1+1) << FIX14_SHIFT))?((b->vel).y>0):((b->vel).y<0)){
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
    (b->pos).x = cx;
    (b->pos).y = cy;

}

void ballToArray(struct ball_t *b, uint8_t playingField[128][32]) {
    playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 111;
}
