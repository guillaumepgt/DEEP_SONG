/*
 * audio_storage.h
 *
 *  Created on: Apr 10, 2026
 *      Author: basil
 */

#ifndef AUDIO_STORAGE_H
#define AUDIO_STORAGE_H

#include "config.h"
#include "stm32g4_flash.h"
#include "audio_recorder.h"
#include <stdint.h>
#include <stdbool.h>

void AudioStorage_ReadFromFlash(uint16_t *buffer, uint32_t max_samples);
uint32_t AudioStorage_GetStoredSampleCount(void);

#endif
