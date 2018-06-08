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
    uint8_t i;
    for (i = 0; i <= 100; i++) {
        playingField[i][0] = 1;
        playingField[i][31] = 1;
    }
    for (i = 2; i <= 10; i++) {
        playingField[0][i] = 2;
        playingField[100][31-i] = 2;
    }
}

int main(void)
    {
        uint8_t xsize = 32, ysize = 6, x, oldx, oldsec, i;
        uint32_t a;
        struct ball_t b;
        char * input;
        char str1[12];
        uint16_t xx, yy;
        uint8_t playingField[128][32];


        init_usb_uart( 115200 ); // Initialize USB serial at 9600 baud
        init_spi_lcd(); // Init spi lcd

        clrscr();
        showCursor(0);
        memset(playingField, 0x00, sizeof (uint8_t) * 128 * 32);

        simpleMapToArray(playingField);

        convertArrayToBuffer(playingField);
        lcd_push_buffer(lcdArray);

        drawWindowFromArray(playingField);

        //initBall(&b, 10, 20, 1, 1);
        //this is new


        /*
        setupLCD();

        resetTimer();
        lcd_write_string("Hej", 0x0002, 0x0000);
        lcd_write_string("Hej1", 0x0002, 0x0001);
        lcd_write_string("Hej2", 0x0002, 0x0002);
        lcd_write_string("Hej3", 0x0002, 0x0003);
        //lcd_push_buffer(&lcdArray);

        clrscr();
        showCursor(0);

        window(1, 1, xsize, ysize, "Stop Watch", 1);
        gotoxy(3, 3);
        printf("Time since start:");
        gotoxy(3, 4);
        printf("Split time 1:");
        gotoxy(3, 5);
        printf("Split time 2:");
        gotoxy(22, 3);
        printf("0:00:00.--");
        gotoxy(22, 4);
        printf("-:--:--.--");
        gotoxy(22, 5);
        printf("-:--:--.--");*/

        /*window(52, 12, 65, 14, "", 5);
        gotoxy(53,13);
        printf("Hits: 0");

        drawBall(&b, 59, 13);*/

        /*configJoy();
        configLed();
        configTimer();

        x = readJoystick();
        oldx = x;

        //gotoxy(5,5);
        //printf("%02X", x);

        oldsec = stopWatch.seconds;
        TIM2->CR1 |= 0x0001;
        setScrolling(0x0C);*/

        while (1) {
            /*
            if (updateLCD == 1)
            {
                gotoxy(1,1);
                xx = readADC1();
                printf("%d", xx);
                gotoxy(1,2);
                yy = readADC2();
                printf("%d", readADC2());

                sprintf(str1, "ADC1 = %04d", xx);
                lcd_write_string(str1,0x0000,0x0000);
                sprintf(str1, "ADC2 = %04d", yy);
                lcd_write_string(str1,0x0000,0x0001);

                lcd_update();
            }*/
            /*
            gotoxy(40, 1);
            printf("Input here:                 ");
            gotoxy(51, 1);
            showCursor(1);
            printf(" ");
            input = getInput();
            showCursor(0);
            gotoxy(40, 2);
            printf("Output here: %10s", input);

            if (oldsec != stopWatch.seconds) {
                gotoxy(22, 3);
                printf("%01d:%02d:%02d.--", stopWatch.hours, stopWatch.minutes, stopWatch.seconds);
                oldsec = stopWatch.seconds;
            }
            x = readJoystick();
            if (strcmp(input, "andet") == 0) { // 1 && x != oldx
                //setLed(1, 0, 0);
            } else if (strcmp(input, "reset") == 0) { // 2  && x != oldx
                resetTimer();
                gotoxy(22, 3);
                printf("%01d:%02d:%02d.--", stopWatch.hours, stopWatch.minutes, stopWatch.seconds);
                //setLed(0, 1, 0);
            } else if (strcmp(input, "split1") == 0) { // 4
                gotoxy(22, 4);
                printf("%01d:%02d:%02d.%02d", stopWatch.hours, stopWatch.minutes, stopWatch.seconds, stopWatch.dseconds);
                //setLed(0, 0, 1);
            } else if (strcmp(input, "split2") == 0) { // 8
                gotoxy(22, 5);
                printf("%01d:%02d:%02d.%02d", stopWatch.hours, stopWatch.minutes, stopWatch.seconds, stopWatch.dseconds);
                //setLed(1, 1, 1);
            } else if (strcmp(input, "stop") == 0) { // 16
                TIM2->CR1 &= ~(0x0001);
                //setLed(0, 0, 0);
            } else if (strcmp(input, "start") == 0) { // 16
                TIM2->CR1 |= 0x0001;
                //setLed(0, 0, 0);
            } else {
                gotoxy(40, 4);
                printf("Write \"stop\" to stop the Stop-Watch");
                gotoxy(40, 5);
                printf("Write \"start\" to start the Stop-Watch");
                gotoxy(40, 6);
                printf("Write \"split1\" to get split1");
                gotoxy(40, 7);
                printf("Write \"split2\" to get split2");
                gotoxy(40, 8);
                printf("Write \"reset\" to reset the Stop-Watch");
            }*/
            /*
            if (x != oldx) {
                gotoxy(5,10);
                printf("%02d", x);
                oldx =x;
            }*/

            /*
            if (a == 99999) {
                removeBall(&b);
            }
            if (a == 100000) {
                updatePosition(&b, 1, 1, xsize, ysize);
                drawBall(&b, 59, 13);
                a = 0;
            }
            a++;
            */
        }
}
