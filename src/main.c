/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "trigonometri.h"
#include "ball.h"
#include "pin_io.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "charset.h"


#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

extern volatile struct timer_t stopWatch;
extern uint8_t updateLCD;

void menuSquare(uint8_t playingField[128][32], int8_t x1, int8_t y1, int8_t x2, int8_t y2){
    uint8_t i;
    for(i = y1; i <= y2; i++){
        playingField[x1][i] = 124;

        playingField[x2][i] = 124;
    }
    for(i = x1; i <= x2; i++){
        playingField[i][y1] = 95;
        playingField[i][y2] = 95;
    }
}

char * getInput() {
    char * line = malloc(32 * sizeof (char));
    uint8_t x;
    line[0] = uart_getc();
    x = 1;
    while (line[x - 1] != 0x0D)     {
        line[x] = uart_getc();
        x++;
    }
    line[x-1] = '\0';
    return line;
}

void simpleMapToArray(uint8_t playingField[128][32],uint16_t x,uint16_t y){
    uint8_t i;
    for (i = 0; i <= 100; i++) {
        playingField[i][0] = 1;
        playingField[i][31] = 1;
    }

    for (i = x; i < 8+x; i++) {
        playingField[0][x] = 2;
    }
    for (i = y; i < 8+y; i++){
        playingField[100][y] = 2;
    }
}

int main(void){

        uint8_t xsize = 32, ysize = 6, x, oldx, oldsec, i;
        uint32_t a;
        struct ball_t b;
        char * input;
        char str1[12];
        uint16_t xx, yy;
        uint8_t playingField[128][32];
        uint8_t testCount = 0;

        uint16_t xtest;

        xx = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));
        yy = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));

        init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud
        init_spi_lcd(); // Init spi lcd

        clrscr();
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);

        configTimer();

        TIM2->CR1 |= 0x0001;
        setScrolling(0x00);

        simpleMapToArray(playingField,xx,yy);

        convertArrayToBuffer(playingField);
        lcd_push_buffer(lcdArray);

        drawWindowFromArray(playingField);

        setupLCD();






        while (1) {

            if (updateLCD == 1){

                xx = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));
                yy = FIX14_MULT(FIX14_DIV(readADC2(),4088),(23));

                //player(xx,yy,playingField);
                menuSquare(playingField, 10, 5, 20, 20);
                lcd_update();
                //testCount++;
            }
            /*
            if(testCount == 1){
                memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);

                lcd_push_buffer(playingField);
                menuSquare(playingField, 10, 5, 20, 20);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(playingField);

                testCount = 0;
            }
            */
        }
}
