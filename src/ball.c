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
    int32_t cx, cy, k = 1;

    cx = (b->pos).x + (b->vel).x*k;
    cy = (b->pos).y + (b->vel).y*k;

    if (cx <= ((x1+1) << FIX14_SHIFT) || cx >= ((x2-1) << FIX14_SHIFT)){
        (b->vel).x = -((b->vel).x);
        b->hits++;
        cx = (b->pos).x + (b->vel).x*k;
        cy = (b->pos).y + (b->vel).y*k;
    }
    if (cy <= (y1 << FIX14_SHIFT) || cy >= ((y2-1) << FIX14_SHIFT)){
        (b->vel).y = -((b->vel).y);
        b->hits++;
        cx = (b->pos).x + (b->vel).x*k;
        cy = (b->pos).y + (b->vel).y*k;
    }

    (b->pos).x = cx;
    (b->pos).y = cy;

}
