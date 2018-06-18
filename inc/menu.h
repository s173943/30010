#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h"
#include <stdio.h>
#include <string.h>
#include "charset.h"
#include "30010_io.h"

#define BLOCK 219

void menuTree(uint8_t playingField[128][32],uint8_t oldPlayingField[128][32], int8_t *menuSettings, uint16_t *testCount);

void blinkSelect(int8_t maxWindows, int8_t *selector);
void menuSquare(uint8_t playingField[128][32], int8_t x1, int8_t y1, int8_t x2, int8_t y2,int8_t val, int8_t selector, uint16_t *testCount);
void modeMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);
void levelMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);
void helpMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);

void startMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount,uint8_t *menuTrack);
void help(uint8_t a[128][32], uint8_t x, uint8_t y);
void mode(uint8_t a[128][32], uint8_t x, uint8_t y);
void level(uint8_t a[128][32], uint8_t x, uint8_t y);
void play(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_medium(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_easy(uint8_t a[128][32], uint8_t x, uint8_t y);
void ugandanKnuckles(uint8_t a[128][32], uint8_t x, uint8_t y);
void sanik(uint8_t a[128][32], uint8_t x, uint8_t y);
void logo(uint8_t a[128][32], uint8_t x, uint8_t y);
void sonicAni1(uint8_t a[128][32], uint8_t x, uint8_t y);
void sonicAni2(uint8_t a[128][32], uint8_t x, uint8_t y);
void sonicAni3(uint8_t a[128][32], uint8_t x, uint8_t y);
#endif
