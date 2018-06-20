#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h"
#include <stdio.h>
#include <string.h>
#include "charset.h"
#include "30010_io.h"
#include "ansi.h"
#include "ball.h"
#include "timer.h"
#include "speaker.h"

#define BLOCK 219

void drawLevel(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t bricksx, uint8_t bricksy, uint8_t *bricks);

void menuTree(uint8_t playingField[128][32],uint8_t oldPlayingField[128][32], uint8_t *menuSettings, uint8_t *menuSettingsCheck, uint16_t *testCount, uint8_t *lives, uint8_t *score, uint8_t *oldx);
void interpretMenuSettings(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32], uint8_t menuSettings, uint8_t * menuSettingsCheck,  uint8_t *bricks);

void simpleMapToArray(uint8_t playingField[128][32]);
void blinkSelect(uint8_t maxWindows, uint8_t *selector);
void menuSquare(uint8_t playingField[128][32], int8_t x1, int8_t y1, int8_t x2, int8_t y2,int8_t val, int8_t selector, uint16_t *testCount);
void modeMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);
void levelMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);
void helpMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount, uint8_t *menuTrack);

void youLoseScreen(uint8_t a[128][32], uint8_t score);
void youLose(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t score);
void youWin(uint8_t a[128][32], uint8_t x, uint8_t y);

void startMenu(uint8_t playingField[128][32], int8_t selector, uint16_t *testCount,uint8_t *menuTrack);
void help(uint8_t a[128][32], uint8_t x, uint8_t y);
void mode(uint8_t a[128][32], uint8_t x, uint8_t y);
void level(uint8_t a[128][32], uint8_t x, uint8_t y);
void play(uint8_t a[128][32], uint8_t x, uint8_t y);

void drawLine(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t length, uint8_t height);
void level_hard(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_medium(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_easy(uint8_t a[128][32], uint8_t x, uint8_t y);
void ugandanKnuckles(uint8_t a[128][32], uint8_t x, uint8_t y);
void sanik(uint8_t a[128][32], uint8_t x, uint8_t y);
void logo(uint8_t a[128][32], uint8_t x, uint8_t y);

void livesToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t lives);
void scoreToArray(uint8_t playingField[128][32], uint8_t x, uint8_t y, uint8_t score);
void drawHeart(uint8_t a[128][32], uint8_t x, uint8_t y);
void drawScore(uint8_t a[128][32], uint8_t x, uint8_t y);
void clearPartOfArray(uint8_t playingField[128][32], uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void copyArray(uint8_t * playingField, uint8_t * oldPlayingField);

void numberWrite(uint8_t a[128][32], uint8_t x, uint8_t y, uint8_t number);


void helpscreen(uint8_t a[128][32], uint8_t x, uint8_t y);
void charToArray(uint8_t a[128][32], uint8_t x, uint8_t y, char c);
#endif
