#include "lcd.h"

void setupLCD() {
    reset_Buffer();
    lcd_reset();
}

void reset_Buffer() {
    memset(lcdArray, 0x00, 512);
}

void convertArrayToBuffer(uint8_t a[128][32]) {
    // takes a big array (128x32) and sets the correct bits in
    // the 512x8 bit buffer, updates the buffer, but does not push!
    uint8_t i, j, h;
    memset(lcdArray, 0x00, 512);
    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 127; j++) {
            for (h = 0; h <= 7; h++) {
                if (a[j][h+(i*8)] != 0x00) {
                    lcdArray[j+(128*i)] |= (0x01 << (h));
                }
            }
        }
    }
}
