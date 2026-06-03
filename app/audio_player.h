/*
 * audio_player.h
 *
 *  Created on: Apr 10, 2026
 *      Author: basil
 */

#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "config.h"
#include "stm32g4_dac.h"
#include <stdint.h>
#include <stdbool.h>

void AudioPlayer_Init(void);
void AudioPlayer_PlayFromFlash(bool activer_fuzz);

#endif
