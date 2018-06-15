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

void speakerBGMusic(uint16_t * n, uint8_t mode) {
    //*n *= 10; // Length of note multiplier
    switch(mode) {
        // Background music case
        case 0:
            switch( * n ) {
            // First
            case (1*TAKT):
                speakerNote('A', 4);
                break;
            case (2*TAKT):
                speakerNote('C', 5);
                break;
            case (3*TAKT):
                speakerNote('E', 5);
                break;
            case (4*TAKT):
                speakerNote('E', 4);
                break;
            // Second
            case (5*TAKT):
                speakerNote('C', 4);
                break;
            case (6*TAKT):
                speakerNote('A', 3);
                break;
            case (7*TAKT):
                speakerNote('A', 4);
                break;
            case (8*TAKT):
                speakerNote('C', 5);
                break;
            // Third
            case (9*TAKT):
                speakerNote('E', 5);
                break;
            case (10*TAKT):
                speakerNote('E', 4);
                break;
            case (11*TAKT):
                speakerNote('C', 4);
                break;
            case (12*TAKT):
                speakerNote('A', 3);
                break;
            // Fourth
            case (13*TAKT):
                speakerNote('A', 4);
                break;
            case (14*TAKT):
                speakerNote('C', 5);
                break;
            case (15*TAKT):
                speakerNote('G', 4);
                break;
            case (16*TAKT):
                speakerNote('B', 4);
                break;
            // Fifth
            case (17*TAKT):
                speakerNote('A', 4);
                break;
            case (18*TAKT):
                speakerNote('C', 5);
                break;
            case (19*TAKT):
                speakerNote('E', 5);
                break;
            case (20*TAKT):
                speakerNote('E', 4);
                break;
            // Sixth
            case (21*TAKT):
                speakerNote('C', 4);
                break;
            case (22*TAKT):
                speakerNote('A', 3);
                break;
            case (23*TAKT):
                speakerNote('A', 4);
                break;
            case (24*TAKT):
                speakerNote('C', 5);
                break;
            // Seventh
            case (25*TAKT):
                speakerNote('E', 5);
                break;
            case (26*TAKT):
                speakerNote('E', 4);
                break;
            case (27*TAKT):
                speakerNote('C', 4);
                break;
            case (28*TAKT):
                speakerNote('A', 5);
                break;
            // Eigth
            case (29*TAKT):
                speakerNote('B', 4);
                break;
            case (30*TAKT):
                speakerNote('D', 5);
                break;
            case (31*TAKT):
                speakerNote('F', 5);
                break;
            case (32*TAKT):
                speakerNote('F', 4);
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
