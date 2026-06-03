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



void AudioPlayer_PlayFromFlash(bool activer_fuzz)
{
    uint32_t cycles_per_sample;
    uint32_t i;

    // 1) Charger les données audio depuis la flash
    AudioStorage_ReadFromFlash(playback_buffer, AUDIO_SAMPLE_COUNT);

    cycles_per_sample = SystemCoreClock / AUDIO_SAMPLE_RATE_HZ;

    // 2) Sortir les samples sur le DAC
    for (i = 0; i < AUDIO_SAMPLE_COUNT; i++)
    {
        // On récupère l'échantillon brut de la mémoire
        uint16_t sample_a_jouer = playback_buffer[i];

        // --- TRAITEMENT DSP : L'EFFET FUZZ ---
        if (activer_fuzz == true)
        {
            // A. On centre le signal autour de 0 (le silence est à 2048)
            int16_t son_centre = (int16_t)sample_a_jouer - 2048;

            // B. On définit la violence de la distorsion
            int16_t seuil_fuzz = 400; // Plus c'est bas, plus le son est écrasé et saturé

            // C. Écrêtage (Clipping) : on coupe les sommets
            if (son_centre > seuil_fuzz)  son_centre = seuil_fuzz;
            if (son_centre < -seuil_fuzz) son_centre = -seuil_fuzz;

            // D. Remise à l'échelle pour compenser la perte de volume
            int32_t amplification = (son_centre * 2048) / seuil_fuzz;

            // E. Sécurité matérielle stricte (limites du DAC 12 bits)
            if (amplification > 2047)  amplification = 2047;
            if (amplification < -2048) amplification = -2048;

            // F. On repasse en valeurs numériques [0 - 4095]
            sample_a_jouer = (uint16_t)(amplification + 2048);
        }
        // -------------------------------------

        // 3) ÉCRITURE : Envoi du sample (modifié ou non) au DAC
        BSP_DAC_Set_value(DAC1_OUT1, sample_a_jouer);

        // 4) ATTENTE : On respecte la cadence pour ne pas lire l'audio trop vite
        AudioPlayer_WaitCycles(cycles_per_sample);
    }

    // Retour au milieu après lecture (Silence propre pour éviter un "clac" dans le haut-parleur)
    BSP_DAC_Set_value(DAC1_OUT1, 2048);
}

