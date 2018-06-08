// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef _TRIGONOMETRI_H_
#define _TRIGONOMETRI_H_

#include "stm32f30x_conf.h"
#include <stdio.h>

// === LUT SIZES ===
#define SIN_SIZE 512
#define FIX14_SHIFT 14

#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( (a) << FIX14_SHIFT / b )

struct vector_t {
    int32_t x, y;
};

// === LUT DECLARATIONS ===
extern const signed short SIN[512];
// === Other functions
void printFix(int32_t i);
int32_t expand(int32_t i);
int32_t sinus(int32_t n);
int32_t cosinus(int32_t n);
void rotate(struct vector_t *v, int32_t angle);

#endif	// _TRIGONOMETRI_H_
