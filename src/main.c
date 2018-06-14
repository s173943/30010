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
        struct ball_t b;
        struct ball_t c;
        uint8_t playingField[128][32], oldPlayingField[128][32];

        init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud
        init_spi_lcd(); // Init spi lcd
        setupLCD();

        initBall(&b, 6, 6, 1, -1);
        initBall(&c, 80, 6, -1, -1);

        clrscr(); // Clear putty terminal
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset playing field (to 0)
        memset(oldPlayingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset old playing field (to 0)

        configTimer();

        TIM2->CR1 |= 0x0001; // Start timer
        setScrolling(0x00); // No scrolling text on LCD

        simpleMapToArray(playingField);

        while (1) {
            if (updateLCD == 1){
                updatePlayer(playingField);
                removeBallFromArray(&b, playingField);
                updatePosition(&b, 1, 1, 99, 31, playingField);
                ballToArray(&b, playingField);
                removeBallFromArray(&c, playingField);
                updatePosition(&c, 1, 1, 99, 31, playingField);
                ballToArray(&c, playingField);
                drawChangeInArray(playingField, oldPlayingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);
                copyArray(*playingField, *oldPlayingField);
                updateLCD = 0;
            }

        }

}
