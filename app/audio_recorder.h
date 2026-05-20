#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include "config.h"
#include "stm32g4_adc.h"
#include "stm32g4_flash.h"
#include <stdint.h>
#include <stdbool.h>

#define AUDIO_SAMPLE_RATE_HZ     1000U
#define AUDIO_DURATION_MS        1920U
#define AUDIO_SAMPLE_COUNT       ((AUDIO_SAMPLE_RATE_HZ * AUDIO_DURATION_MS) / 1000U)

typedef enum
{
    AUDIO_OK = 0,
    AUDIO_ERROR
} AudioStatus_t;

void AudioRecorder_Init(void);
AudioStatus_t AudioRecorder_Record(adc_id_e channel);
AudioStatus_t AudioRecorder_SaveToFlash(void);
bool AudioRecorder_IsFinished(void);
uint16_t AudioRecorder_GetSample(uint32_t index);
uint32_t AudioRecorder_GetSampleCount(void);
const uint16_t *AudioRecorder_GetBuffer(void);

#endif
