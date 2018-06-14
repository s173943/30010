#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "stm32f30x_conf.h"
#include "timer.h"

void configSpeaker();
void setFreq(uint16_t freq);
void speakerPling();
void speakerNote(char note, uint8_t octave);
void speakerHB();
void speakerMario();
void speakerBGMusic(uint8_t * n, uint8_t mode);
void speakerBGMusicTest();

#endif /* _SPEAKER_H_ */
