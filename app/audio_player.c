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

/** @brief Tampon local hébergeant la piste audio décompressée avant lecture */
static uint16_t playback_buffer[AUDIO_SAMPLE_COUNT];

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

/**
 * @brief  Exécute la lecture audio avec application optionnelle d'un filtre DSP.
 * @param  activer_fuzz Booléen activant l'effet de distorsion matérielle.
 * @return Aucun.
 */
void AudioPlayer_PlayFromFlash(bool activer_fuzz)
{
    uint32_t cycles_per_sample;
    uint32_t i;

    AudioStorage_ReadFromFlash(playback_buffer, AUDIO_SAMPLE_COUNT);
    cycles_per_sample = SystemCoreClock / AUDIO_SAMPLE_RATE_HZ;

    for (i = 0; i < AUDIO_SAMPLE_COUNT; i++)
    {
        uint16_t sample_a_jouer = playback_buffer[i];

        if (activer_fuzz == true)
        {
            int16_t son_centre = (int16_t)sample_a_jouer - 2048;
            int16_t seuil_fuzz = 400;

            if (son_centre > seuil_fuzz)  son_centre = seuil_fuzz;
            if (son_centre < -seuil_fuzz) son_centre = -seuil_fuzz;

            int32_t amplification = (son_centre * 2048) / seuil_fuzz;

            if (amplification > 2047)  amplification = 2047;
            if (amplification < -2048) amplification = -2048;

            sample_a_jouer = (uint16_t)(amplification + 2048);
        }

        BSP_DAC_Set_value(DAC1_OUT1, sample_a_jouer);
        AudioPlayer_WaitCycles(cycles_per_sample);
    }

    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}