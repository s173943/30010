#include "ansi.h"
#include "string.h"
#define ESC 0x1B


void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
    printf("%c[2J", ESC);
}

void clreol() {
    printf("%c[K", ESC);
}

void gotoxy(uint8_t x, uint8_t y) {
    printf("%c[%d;%dH", ESC, y, x);
}

void underline(uint8_t on) {
    printf("%c[%dm", ESC, (on == 1)? 04:24);
}

void inverse(uint8_t on){
    if (on == 1){
        color(15,0);
    } else {
        color(0, 2);
    }
}

void showCursor(uint8_t on) {
    if (on == 1){
        printf("%c[?25h", ESC);
    } else {
        printf("%c[?25l", ESC);
    }
}

void blink(uint8_t on){
    printf("%c[%dm", ESC, (on == 1)? 05:25);
}

void drawWindowFromArray(uint8_t playingField[128][32]) {
    // Takes a 128x32 array and outputs characters to the UART
    // depending on the value in the array
    uint8_t i, j;
    for (i = 0; i <= 127; i++) {
        for (j = 0; j <= 31; j++) {
            if (playingField[i][j] != 0) {
                gotoxy(i+1,j+1);
                printf("%c", playingField[i][j]);
            }
        }
    }
}

void drawChangeInArray(uint8_t playingField[128][32], uint8_t oldPlayingField[128][32]) {
    uint8_t i, j;
    for (i = 0; i <= 127; i++) {
        for (j = 0; j <= 31; j++) {
            if (playingField[i][j] != oldPlayingField[i][j]) {
                gotoxy(i+1,j+1);
                if (playingField[i][j] == 0) {
                    printf("%c", 32);
                } else {
                    printf("%c", playingField[i][j]);
                }
            }
        }
    }
}
