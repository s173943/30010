#include "lcd.h"

void setupLCD() {
    reset_Buffer();
    lcd_reset();
    updateCount = 0;
    scrolling = 0;
}

void lcd_write_string(char * s, uint16_t slice, uint16_t line) {
    // line should be between 0x0000 - 0x0003
    // slice should be between 0x0000 - 0x0080
    uint16_t i, j, x;
    x = slice + (line << 0x07);
    for (j = 0; j < strlen(s); j++) {
        for(i = 0; i < 5; i++) {
            lcdArray[x + 6 * j + i] = character_data[s[j] - 0x20][i];
        }
    }
}

void reset_Buffer() {
    memset(lcdArray, 0x00, 512);
}

void lcd_update() {
    if (updateLCD == 1) {
        updateCount++;
        if (updateCount == 5) {
            leftScrollingText(scrolling);
            updateCount = 0;
        }
        lcd_push_buffer(lcdArray);
        updateLCD = 0;
    }
}

void leftScrollingText(uint8_t lineNumber) {
    uint16_t i;
    uint8_t temp[4];
    if ((lineNumber & 0x01) == 0x01)
        temp[0] = lcdArray[0];
    if ((lineNumber & 0x02) == 0x02)
        temp[1] = lcdArray[128];
    if ((lineNumber & 0x04) == 0x04)
        temp[2] = lcdArray[256];
    if ((lineNumber & 0x08) == 0x08)
        temp[3] = lcdArray[384];
    for (i = 0; i < 127; i++)
    {
        if ((lineNumber & 0x01) == 0x01)
            lcdArray[i] = lcdArray[i + 1];
        if ((lineNumber & 0x02) == 0x02)
            lcdArray[i + 128] = lcdArray[i + 129];
        if ((lineNumber & 0x04) == 0x04)
            lcdArray[i + 256] = lcdArray[i + 257];
        if ((lineNumber & 0x08) == 0x08)
            lcdArray[i + 384] = lcdArray[i + 385];
    }
    if ((lineNumber & 0x01) == 0x01)
        lcdArray[127] = temp[0];
    if ((lineNumber & 0x02) == 0x02)
        lcdArray[255] = temp[1];
    if ((lineNumber & 0x04) == 0x04)
        lcdArray[383] = temp[2];
    if ((lineNumber & 0x08) == 0x08)
        lcdArray[511] = temp[3];
}

void setScrolling(uint8_t x) {
    scrolling = x;
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
