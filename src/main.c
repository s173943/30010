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

extern volatile struct timer_t stopWatch;
extern uint8_t updateLCD;





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

void simpleMapToArray(uint8_t playingField[128][32]){
    // 196 Horizontal line, 179 Vertical line.
    uint8_t i;
    for (i = 0; i <= 100; i++) {
        playingField[i][0] = 196;
        playingField[i][31] = 196;
    }
}

void copyArray(uint8_t * playingField, uint8_t * oldPlayingField) {
    uint16_t i;
    for (i = 0; i < 4096; i++) { // 128 * 32 = 4096
        oldPlayingField[i] = playingField[i];
    }
}

int main(void){

        uint8_t xsize = 32, ysize = 6, x, oldx, oldsec, i;
        uint32_t a;
        struct ball_t b;
        char * input;
        char str1[12];
        uint16_t xx, yy;
        uint8_t playingField[128][32], oldPlayingField[128][32];
        uint8_t testCount = 0,sonicCount = 0;

        uint16_t xtest;

        xx = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));
        yy = FIX14_MULT(FIX14_DIV(readADC2(),4088),(23));

        //uint8_t xsize = 32, ysize = 6, x, oldx, oldsec, i;
        //uint32_t a;
        //struct ball_t b;
        //char * input;
        //char str1[12];


        init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud
        init_spi_lcd(); // Init spi lcd
        setupLCD();

        clrscr(); // Clear putty terminal
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset playing field (to 0)
        memset(oldPlayingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset old playing field (to 0)

        configTimer();

        TIM2->CR1 |= 0x0001; // Start timer
        setScrolling(0x00); // No scrolling text on LCD

        //simpleMapToArray(playingField);
        //level_hard(playingField, 10, 3);
        //level_easy(playingField, 50, 3);
        //numberWrite(playingField, 50,15, 2);

        //sonicAni1(playingField, 2, 0);
        //sonicAni2(playingField, 30, 0);
        //sonicAni3(playingField, 60, 0);
        //convertArrayToBuffer(playingField);
        //lcd_push_buffer(lcdArray);





        while (1) {
            if (updateLCD == 1){
                gotoxy(2,2);
                xx = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));
                yy = FIX14_MULT(FIX14_DIV(readADC2(),4088),(23));
                printf("%d test",sonicCount);
                //memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);

                //lcd_push_buffer(playingField);
                //menuSquare(playingField, 10, 5, 20, 20);
                //convertArrayToBuffer(playingField);
                //lcd_push_buffer(playingField);
                drawSonicWinner(playingField,oldPlayingField,&sonicCount);
                drawSonicWinner(playingField,oldPlayingField,&sonicCount);
                updatePlayer(playingField);
                drawChangeInArray(playingField, oldPlayingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);
                copyArray(*playingField, *oldPlayingField);
                //lcd_update();
                //testCount++;
                sonicCount++;
                if(sonicCount == 80){
                    sonicCount = 0;
                }

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


