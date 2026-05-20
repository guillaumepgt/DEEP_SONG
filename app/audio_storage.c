/*
 * audio_storage.c
 *
 *  Created on: Apr 10, 2026
 *      Author: basil
 */
#include "audio_storage.h"

/*
 * Lit l'audio stocké en flash et reconstruit les samples 12 bits
 * dans un buffer RAM.
 *
 * buffer      : buffer de destination
 * max_samples : taille max du buffer
 */
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
            if ((sample_index >= AUDIO_SAMPLE_COUNT) || (sample_index >= max_samples)) break;//on revérifie si jamais ça dépasse pendant la boucle et que ça a pas reverifié dans le while


            sample8b = (uint8_t)((packed_data >> (8 * j)) & 0xFF);


            //Reconvertit 8 bits -> 12 bits

            buffer[sample_index] = ((uint16_t)sample8b) << 4; //Dac et adc utilise du 12bits, donc on convertit en 12 bits pour simplifier l'utilisation
            sample_index++;
        }

        flash_index++;
    }
}


//Renvoie le nombre total de samples stockés

uint32_t AudioStorage_GetStoredSampleCount(void)
{
    return AUDIO_SAMPLE_COUNT;
}

