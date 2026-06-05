/**
 *******************************************************************************
 * @file    audio_storage.c
 * @author  Basile, Titouan, Guillaume
 * @date    Avril 2026
 * @brief   Lecture et décompression des données audio depuis la mémoire Flash.
 *******************************************************************************
 */

#include "audio_storage.h"

void AudioStorage_ReadFromFlash(uint16_t *buffer, uint32_t max_samples)
{
    uint32_t flash_index = 0;
    uint32_t sample_index = 0;
    uint64_t packed_data;
    uint8_t sample8b;

    if (buffer == 0)
    {
        return;
    }

    while ((sample_index < AUDIO_SAMPLE_COUNT) && (sample_index < max_samples))
    {
        packed_data = BSP_FLASH_read_doubleword(flash_index);

        for (uint8_t j = 0; j < 8; j++)
        {
            if ((sample_index >= AUDIO_SAMPLE_COUNT) || (sample_index >= max_samples)) break;

            sample8b = (uint8_t)((packed_data >> (8 * j)) & 0xFF);

            buffer[sample_index] = ((uint16_t)sample8b) << 4;
            sample_index++;
        }

        flash_index++;
    }
}

uint32_t AudioStorage_GetStoredSampleCount(void)
{
    return AUDIO_SAMPLE_COUNT;
}