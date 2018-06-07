#include "ansi.h"
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

void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char name[], uint8_t style) {
    uint8_t i, xs = x2-x1, ys = y2-y1, center, offset;
    uint8_t vChar, hChar, ltChar, rtChar, dlcChar, drcChar, tlcChar, trcChar;
    switch (style)
    {
    case 1:
        vChar = 179;
        hChar = 196;
        ltChar = 180;
        rtChar = 195;
        tlcChar = 218;
        trcChar = 191;
        dlcChar = 192;
        drcChar = 217;
        center = 1;
        break;
    case 2:
        vChar = 186;
        hChar = 205;
        ltChar = 185;
        rtChar = 204;
        tlcChar = 201;
        trcChar = 187;
        dlcChar = 200;
        drcChar = 188;
        center = 2;
        break;
    case 3:
        vChar = 221;
        hChar = 240;
        ltChar = 123;
        rtChar = 125;
        tlcChar = 248;
        trcChar = 248;
        dlcChar = 248;
        drcChar = 248;
        center = 2;
        break;
    case 4:
        vChar = 186;
        hChar = 205;
        ltChar = 185;
        rtChar = 204;
        tlcChar = 201;
        trcChar = 187;
        dlcChar = 200;
        drcChar = 188;
        center = 3;
        break;
    case 5:
        vChar = 179;
        hChar = 196;
        ltChar = 180;
        rtChar = 195;
        tlcChar = 218;
        trcChar = 191;
        dlcChar = 192;
        drcChar = 217;
        center = 3;
        break;
    default:
        vChar = 179;
        hChar = 196;
        ltChar = 180;
        rtChar = 195;
        tlcChar = 218;
        trcChar = 191;
        dlcChar = 192;
        drcChar = 217;
        center = 2;
        break;
    }
    //Top line
    gotoxy(x1, y1);
    if (center == 1) {
        color(15, 0);
        printf("%c%c", tlcChar, ltChar);
        color(0, 2);
        printf("%s", name);
        for (i = 2+strlen(name); i < xs-1; i++){
            gotoxy(x1+i, y1);
            printf(" ");
        }
        color(15, 0);
        //Top right stuff
        gotoxy(x2-1,y1);
        printf("%c%c", rtChar, trcChar);
    } else if (center == 2) {
        offset = ((strlen(name) % 2) == 0)? 0:1;
        color(15, 0);
        printf("%c", tlcChar);
        for (i = 1; i < (xs/2)-strlen(name)/2-offset; i++){
            gotoxy(x1+i, y1);
            printf("%c", hChar);
        }
        printf("%c", ltChar);
        color(0, 2);
        printf("%s", name);
        color(15, 0);
        printf("%c", rtChar);
        for (i = (xs/2)+strlen(name)/2+(offset*2); i < xs; i++) {
            gotoxy(x1+i, y1);
            printf("%c", hChar);
        }
        color(15, 0);
        //Top right stuff
        gotoxy(x2,y1);
        printf("%c", trcChar);
    } else {
        gotoxy(x1,y1);
        printf("%c", tlcChar);
        for (i = 1; i < xs; i++) {
            gotoxy(x1+i, y1);
            printf("%c", hChar);
        }
        printf("%c", trcChar);
    }

    //Vertical lines
    for (i = 1; i < ys; i++) {
        gotoxy(x1, y1+i);
        printf("%c", vChar);
        gotoxy(x2, y1+i);
        printf("%c", vChar);
    }

    //Bottom left corner
    gotoxy(x1,y2);
    printf("%c", dlcChar);
    //Bottom line
    for (i = 1; i < xs; i++) {
        gotoxy(x1+i, y2);
        printf("%c", hChar);
    }
    //Bottom right corner
    printf("%c", drcChar);
}
