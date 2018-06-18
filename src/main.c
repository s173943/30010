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
#include "menu.h"

extern volatile struct timer_t stopWatch;
extern uint8_t updateLCD;

int main(void){
        uint16_t bgMusicState = 0;
        uint8_t bricks, lives, score = 0;
        struct ball_t b;
        uint8_t playingField[128][32], oldPlayingField[128][32], soundMode;
        uint16_t testCount = 0;
        int8_t menuSettings = 0;

        init_usb_uart( 460800 ); // Initialize USB serial at 115200 baud
        init_spi_lcd(); // Init spi lcd
        setupLCD();

        initBall(&b, 10, 5, 1, 1, 0);
        //initBall(&c, 80, 6, -1, -1);

        clrscr(); // Clear putty terminal
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset playing field (to 0)
        memset(oldPlayingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset old playing field (to 0)

        configTimer1();
        configTimer2();
        configADCS();
        configSpeaker();
        configJoy();

        TIM1->CR1 |= 0x0001; // Start timer
        setScrolling(0x00); // No scrolling

        soundMode = 0;

        while (1) {
            if (updateLCD == 1){
                // Will hang in menu till play is pressed
                menuTree(playingField,oldPlayingField, &menuSettings, &testCount, &bricks, &lives);
                // Update player and ball
                updatePlayer(playingField);
                removeBallFromArray(&b, playingField);
                updatePosition(&b, 1, 1, 99, 31, playingField, &bricks, &lives, &score);
                ballToArray(&b, playingField);
                livesToArray(playingField, 102, 17, lives);
                scoreToArray(playingField, 102, 0, score);
                // Draw change in array and push buffer
                drawChangeInArray(playingField, oldPlayingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);
                // Copy array into oldArray, for comparison
                copyArray(*playingField, *oldPlayingField);
                // Cycle background music
                //speakerBGMusic(&bgMusicState, soundMode);
                // Prepare for next update
                updateLCD = 0;
            }
        }
}
