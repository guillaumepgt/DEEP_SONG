/**
 *******************************************************************************
 * @file    audio_player.c
 * @author  Basile, Titouan, Guillaume
 * @date    Avril 2026
 * @brief   Lecteur audio cadencé par cycles d'horloge sur sortie analogique DAC.
 *******************************************************************************
 */

#include "audio_player.h"
#include "audio_storage.h"
#include "audio_recorder.h"
#include "stm32g4_sys.h"

static uint16_t playback_buffer[AUDIO_SAMPLE_COUNT]; ///< Tampon local hébergeant la piste audio décompressée

/**
 * @brief  Initialise le compteur temporel matériel DWT dédié aux pauses calibrées.
 * @return Aucun.
 */
static void AudioPlayer_DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

/**
 * @brief  Génère un blocage d'exécution d'une durée précise calculée en cycles processeur.
 * @param  nb_cycles Nombre de tops d'horloge CPU à attendre.
 * @return Aucun.
 */
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
    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}

void AudioPlayer_PlayFromFlash(void)
{
    uint32_t cycles_per_sample;
    uint32_t i;

    AudioStorage_ReadFromFlash(playback_buffer, AUDIO_SAMPLE_COUNT);

    cycles_per_sample = SystemCoreClock / AUDIO_SAMPLE_RATE_HZ;

    for (i = 0; i < AUDIO_SAMPLE_COUNT; i++)
    {
        BSP_DAC_Set_value(DAC1_OUT1, playback_buffer[i]);
        AudioPlayer_WaitCycles(cycles_per_sample);
    }

    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}