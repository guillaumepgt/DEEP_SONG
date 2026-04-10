/*
 * audio_player.c
 *
 *  Created on: Apr 10, 2026
 *      Author: basil
 */
#include "audio_player.h"
#include "audio_storage.h"
#include "audio_recorder.h"
#include "stm32g4_sys.h"

/*
 * Buffer local du player
 * On charge ici tout l'audio lu depuis la flash
 */
static uint16_t playback_buffer[AUDIO_SAMPLE_COUNT];



static void AudioPlayer_DWT_Init(void) //merci chat je comprends pas ce que ça fait
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

static void AudioPlayer_WaitCycles(uint32_t nb_cycles)
{
    uint32_t start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < nb_cycles)
    {
    }
}


void AudioPlayer_Init(void)
{
    BSP_DAC_Init(DAC1_OUT1, DAC_MODE_NORMAL, false);
    BSP_DAC_Start_without_dma(DAC1_OUT1);

    AudioPlayer_DWT_Init();


    // Niveau moyen au repos

    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}



void AudioPlayer_PlayFromFlash(void)
{
    uint32_t cycles_per_sample;
    uint32_t i;


    // 1) Charger les données audio depuis la flash

    AudioStorage_ReadFromFlash(playback_buffer, AUDIO_SAMPLE_COUNT);

    cycles_per_sample = SystemCoreClock / AUDIO_SAMPLE_RATE_HZ;


    // 2) Sortir les samples sur le DAC

    for (i = 0; i < AUDIO_SAMPLE_COUNT; i++)
    {
        BSP_DAC_Set_value(DAC1_OUT1, playback_buffer[i]);
        AudioPlayer_WaitCycles(cycles_per_sample);
    }


    // Retour au milieu après lecture

    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}

