#include "stm32f30x_conf.h"
#include <string.h>
#include "trigonometri.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void inverse(uint8_t on);
void showCursor(uint8_t on);
void blink(uint8_t on);
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char name[], uint8_t style);
void drawWindowFromArray(uint8_t playingField[128][32]);
void drawChangeInArray(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32]);

void numberWrite(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t number);

#endif /* _ANSI_H_ */
