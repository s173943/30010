#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "trigonometri.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _ANSI_H_
#define _ANSI_H_

#define ESC 0x1B

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void showCursor(uint8_t on);
void drawWindowFromArray(uint8_t playingField[128][32]);
void drawChangeInArray(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32]);

#endif /* _ANSI_H_ */
