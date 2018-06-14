#include "speaker.h"

void configSpeaker() {
    // The speaker is located at PB10. TIM2 CH3
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock on bank B
    GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear
    GPIOB->MODER |= (0x00000002 << (10 * 2)); // Alternate function
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1); // Specify PWM mode
}

void setFreq(uint16_t freq) {
    uint32_t reload = 64e6 / freq / (9 + 1) - 1;

    TIM2->ARR = reload; // Set auto reload value
    TIM2->CCR3 = reload/2; // Set compare register

    TIM2->EGR |= 0x01;
}

void speakerPling() {
    setFreq(1500);
    wait();
    setFreq(2000);
    wait();
    setFreq(1500);
    wait();
    setFreq(0);
}

void speakerNote(char note, uint8_t octave) {
    uint16_t n;
    switch(note) {
    case 'A':
        n = 28;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'B':
        n = 31;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'C':
        n = 16;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'D':
        n = 18;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'E':
        n = 21;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'F':
        n = 21;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    case 'G':
        n = 24;
        switch(octave){
        case 0:
            n *= 1;
            break;
        case 1:
            n *= 2;
            break;
        case 2:
            n *= 4;
            break;
        case 3:
            n *= 8;
            break;
        case 4:
            n *= 16;
            break;
        case 5:
            n *= 32;
            break;
        case 6:
            n *= 64;
            break;
        case 7:
            n *= 128;
            break;
        case 8:
            n *= 256;
            break;
        }
        break;
    }
    setFreq(n);
    //wait();
}

void speakerHB() {
    speakerNote('D', 1);
    speakerNote('D', 2);
    speakerNote('E', 3);
    speakerNote('D', 4);
    speakerNote('G', 5);
    speakerNote('F', 6);

    speakerNote('D', 7);
    speakerNote('D', 8);
    speakerNote('E', 1);
    speakerNote('D', 2);
    speakerNote('A', 3);
    speakerNote('G', 4);

    speakerNote('D', 5);
    speakerNote('D', 6);
    speakerNote('D', 7);
    speakerNote('B', 8);
    speakerNote('G', 1);
    speakerNote('F', 2);
    speakerNote('E', 3);
    speakerNote('C', 4);
    speakerNote('C', 5);
    speakerNote('B', 6);
    speakerNote('G', 7);
    speakerNote('A', 8);
    speakerNote('G', 1);

    setFreq(0);
}

void speakerMario() {
    speakerNote('E', 4);
    speakerNote('E', 4);
    speakerNote('E', 4);
    speakerNote('C', 4);
    speakerNote('G', 4);
    speakerNote('G', 3);

    speakerNote('C', 4);
    speakerNote('G', 3);
    speakerNote('E', 3);
    speakerNote('A', 4);
    speakerNote('B', 4);
    speakerNote('B', 3);
    speakerNote('A', 3);

    speakerNote('G', 3);
    speakerNote('E', 4);
    speakerNote('G', 4);
    speakerNote('A', 4);

    speakerNote('F', 4);
    speakerNote('G', 4);
    speakerNote('E', 4);
    speakerNote('C', 4);
    speakerNote('D', 4);
    speakerNote('B', 3);

    setFreq(0);
}

void speakerBGMusicTest() {
    speakerNote('C', 5);
    speakerNote('D', 5);
    speakerNote('E', 4);
    speakerNote('D', 5);
    speakerNote('G', 5);
    speakerNote('E', 4);
    speakerNote('F', 5);
    speakerNote('D', 4);
}

void speakerBGMusic(uint8_t * n, uint8_t mode) {
    //*n *= 10; // Length of note multiplier
    switch(mode) {
        // Background music case
        case 0:
            switch( * n ) {
            case 10:
                speakerNote('F', 3);
                break;
            case 20:
                speakerNote('G', 2);
                break;
            case 30:
                speakerNote('A', 3);
                break;
            case 40:
                speakerNote('G', 3);
                break;
            case 50:
                speakerNote('A', 2);
                break;
            case 60:
                speakerNote('C', 4);
                break;
            case 70:
                speakerNote('D', 3);
                break;
            case 80:
                speakerNote('D', 4);
                break;
            case 90:
                speakerNote('F', 3);
                break;
            case 100:
                speakerNote('G', 3);
                *n = 0;
                break;
            }
            break;
        // Pling case
        case 1:
            switch( * n ) {
            case 2:
                speakerNote('A', 5);
                break;
            case 4:
                speakerNote('B', 5);
                break;
            case 6:
                speakerNote('D', 6);
                break;
            case 10:
                setFreq(0);
                *n = 0;
                break;
            }
            break;
    }
    (*n)++;
}
