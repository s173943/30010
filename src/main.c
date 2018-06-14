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
#include "speaker.h"

extern volatile struct timer_t stopWatch;
extern uint8_t updateLCD;


void menuSquare(uint8_t playingField[128][32], int8_t x1, int8_t y1, int8_t x2, int8_t y2,int8_t val, int8_t *selector){
    uint8_t i;
    for(i = y1; i <= y2; i++){
        playingField[x1][i] = 124;
        playingField[x2][i] = 124;
    }
    for(i = x1; i <= x2; i++){
        playingField[i][y1] = 95;
        playingField[i][y2] = 95;
    }
    if (val == *selector){
        //blink
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
        uint8_t bgMusicState = 0, soundMode;
        struct ball_t b;
        uint8_t playingField[128][32], oldPlayingField[128][32];
        // test count

        init_usb_uart( 115200 ); // Initialize USB serial at 115200 baud
        init_spi_lcd(); // Init spi lcd
        setupLCD();

        initBall(&b, 6, 6, 1, -1);

        clrscr(); // Clear putty terminal
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset playing field (to 0)
        memset(oldPlayingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset old playing field (to 0)

        configTimer1();
        configTimer2();
        configADCS();
        configSpeaker();

        speakerHB();
        setFreq(0);

        TIM1->CR1 |= 0x0001; // Start timer

        simpleMapToArray(playingField);
        level_hard(playingField, 10, 3);
        level_easy(playingField, 50, 3);

        //convertArrayToBuffer(playingField);
        //lcd_push_buffer(lcdArray);





        soundMode = 0;

        while (1) {
            if (updateLCD == 1){
                xx = FIX14_MULT(FIX14_DIV(readADC1(),4088),(23));
                yy = FIX14_MULT(FIX14_DIV(readADC2(),4088),(23));

                //memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);

                //lcd_push_buffer(playingField);
                //menuSquare(playingField, 10, 5, 20, 20);
                //convertArrayToBuffer(playingField);
                //lcd_push_buffer(playingField);
                updatePlayer(playingField);
                updatePosition(&b, 1, 1, 100, 32);
                ballToArray(&b, playingField);
                drawChangeInArray(playingField, oldPlayingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);
                copyArray(*playingField, *oldPlayingField);
                speakerBGMusic(&bgMusicState, soundMode);
                updateLCD = 0;
                // lcd upadte noget
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
