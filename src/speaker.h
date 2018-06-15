#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "stm32f30x_conf.h"
#include "timer.h"

#define TAKT 3

void configSpeaker();
void setFreq(uint16_t freq);
void speakerPling();
void speakerNote(char note, uint8_t octave);
void speakerBGMusic(uint16_t * n, uint8_t mode);

#endif /* _SPEAKER_H_ */
