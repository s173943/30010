#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f30x_conf.h"
#include <stdio.h>
#include <string.h>
#include "charset.h"
#include "30010_io.h"

#define BLOCK 219

void menu1();

void help(uint8_t a[128][32], uint8_t x, uint8_t y);
void mode(uint8_t a[128][32], uint8_t x, uint8_t y);
void level(uint8_t a[128][32], uint8_t x, uint8_t y);
void play(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_medium(uint8_t a[128][32], uint8_t x, uint8_t y);
void level_easy(uint8_t a[128][32], uint8_t x, uint8_t y);
void ugandanKnuckles(uint8_t a[128][32], uint8_t x, uint8_t y);
void sanik(uint8_t a[128][32], uint8_t x, uint8_t y);

#endif
