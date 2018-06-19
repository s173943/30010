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
#include "ball.h"
#include "pin_io.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "speaker.h"
#include "menu.h"

extern volatile struct timer_t stopWatch;
extern uint8_t updateLCD;

int main(void){
        uint16_t bgMusicState = 0;
        uint8_t bricks, lives, score = 0, oldJoy = 0, balls = 1;
        struct ball_t b, c, d, e, f;
        struct powerUp_t p;
        uint8_t playingField[128][32], oldPlayingField[128][32], soundMode;
        uint16_t testCount = 0;
        uint8_t menuSettings = 0x04, menuSettingsCheck = 0, workorPlay = 0;

        init_usb_uart( 460800 ); // Initialize USB serial at 115200 baud
        init_spi_lcd(); // Init spi lcd
        setupLCD();

        initBall(&b, 10, 5, 1, 1, 0);
        initBall(&c, 10, 5, 1, 1, 3);
        initBall(&d, 10, 5, 1, 1, 3);
        initBall(&e, 10, 5, 1, 1, 3);
        initBall(&f, 10, 5, 1, 1, 3);
        initPowerUp(&p, 0, 0, 0); // Reset the powerup

        clrscr(); // Clear putty terminal
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset playing field (to 0)
        memset(oldPlayingField, 0x00, sizeof (uint8_t) * 128 * 32); // Reset old playing field (to 0)

        configTimer1(); // Config TIM1 and IRQ16 for timer stuff
        configTimer2(); // Config TIM2 for PWM control
        configADCS(); // Config general ADC settings
        configSpeaker(); // Config speaker and wire TIM2 with it
        configJoy(); // Config Joystick

        setSpeed(10); // Initial update speed = 10 times per second
        TIM1->CR1 |= 0x0001; // Start timer

        soundMode = 10; // Muted = 10, 0 = background music

        while(1){
            if (updateLCD == 1){
                // Will hang in menu till play is pressed, then draw map and stuff
                menuTree(playingField,oldPlayingField, &menuSettings, &menuSettingsCheck, &testCount, &lives, &score, &oldJoy);
                interpretMenuSettings(playingField, oldPlayingField, menuSettings, &menuSettingsCheck, &bricks);
                bossKeyEN(&workorPlay,playingField,oldPlayingField, &oldJoy);

                // Update player
                updatePlayer(playingField);

                // Remove balls and powerup
                removeBallFromArray(&b, playingField); // Could be made smaller with a function + loop
                removeBallFromArray(&c, playingField);
                removeBallFromArray(&d, playingField);
                removeBallFromArray(&e, playingField);
                removeBallFromArray(&f, playingField);
                removePowerUpFromArray(&p, playingField);

                // Update balls and powerup
                updatePosition(&b, 1, 1, 99, 31, playingField, &bricks, &lives, &score, &p, &balls, &menuSettings);
                updatePosition(&c, 1, 1, 99, 31, playingField, &bricks, &lives, &score, &p, &balls, &menuSettings);
                updatePosition(&d, 1, 1, 99, 31, playingField, &bricks, &lives, &score, &p, &balls, &menuSettings);
                updatePosition(&e, 1, 1, 99, 31, playingField, &bricks, &lives, &score, &p, &balls, &menuSettings);
                updatePosition(&f, 1, 1, 99, 31, playingField, &bricks, &lives, &score, &p, &balls, &menuSettings);
                powerUpdate(&p, 1, 99, &b, &c, &d, &e, &f, playingField, &balls);

                // Put powerups and balls into array
                powerToArray(&p, playingField);
                ballToArray(&b, playingField);
                ballToArray(&c, playingField);
                ballToArray(&d, playingField);
                ballToArray(&e, playingField);
                ballToArray(&f, playingField);

                // Add score and life to the array
                livesToArray(playingField, 102, 17, lives);
                scoreToArray(playingField, 102, 0, score);

                // Draw change in array and push buffer
                drawChangeInArray(playingField, oldPlayingField);
                convertArrayToBuffer(playingField);
                lcd_push_buffer(lcdArray);

                // Copy array into oldArray, for comparison
                copyArray(*playingField, *oldPlayingField);

                // Cycle background music
                speakerBGMusic(&bgMusicState, soundMode);

                // Prepare for next update
                updateLCD = 0;
            }
        }
}
