#include "menu.h"
#include "ansi.h"

void menu1(){

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

void level(uint8_t a[128][32], uint8_t x, uint8_t y){
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

void mode(uint8_t a[128][32], uint8_t x, uint8_t y){
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

