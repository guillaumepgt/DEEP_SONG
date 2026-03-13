/*
 * boutton.h
 *
 *  Created on: 13 mars 2026
 *      Author: Basile
 */
#ifndef BOUTTON_H
#define BOUTTON_H

#include "stm32g4xx_hal.h"

#define BUTTON_COUNT 5

typedef enum {
    BUTTON_CENTER = 0,
    BUTTON_UP = 1,
    BUTTON_DOWN = 2,
    BUTTON_LEFT = 3,
    BUTTON_RIGHT = 4
} ButtonId;

void BUTTON_Init(void);
uint8_t BUTTON_IsPressed(ButtonId button);

#endif
