#include "menu.h"
#include "ansi.h"

void menu1(){

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
