/**
 *******************************************************************************
 * @file    audio_storage.h
 * @author  Basile, Titouan, Guillaume
 * @date    Avril 2026
 * @brief   Gestionnaire de la mémoire non-volatile pour les données audio.
 *******************************************************************************
 */

#ifndef AUDIO_STORAGE_H
#define AUDIO_STORAGE_H

#include "config.h"
#include "stm32g4_flash.h"
#include "audio_recorder.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  Lit les octets stockés en Flash et recrée les mots de 12 bits en RAM.
 * @param  buffer Table de destination en RAM pour les échantillons 12 bits restaurés.
 * @param  max_samples Capacité maximale de stockage du buffer de destination.
 * @return Aucun.
 */
void AudioStorage_ReadFromFlash(uint16_t *buffer, uint32_t max_samples);

/**
 * @brief  Retourne la quantité globale de samples définis dans la configuration.
 * @return Nombre d'échantillons (::AUDIO_SAMPLE_COUNT).
 */
uint32_t AudioStorage_GetStoredSampleCount(void);

#endif