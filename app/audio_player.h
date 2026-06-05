/**
 *******************************************************************************
 * @file    audio_player.h
 * @author  Basile, Titouan, Guillaume
 * @date    Avril 2026
 * @brief   Générateur de signal de sortie (Lecteur audio) basé sur le DAC.
 *******************************************************************************
 */

#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "config.h"
#include "stm32g4_dac.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  Initialise le DAC périphérique et configure la base de temps matérielle DWT.
 * @return Aucun.
 */
void AudioPlayer_Init(void);

/**
 * @brief  Transfère les données Flash vers la RAM puis les joue en temps réel sur le Jack.
 * @return Aucun.
 */
void AudioPlayer_PlayFromFlash(bool activer_fuzz);

#endif
