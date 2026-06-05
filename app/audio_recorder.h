/**
 *******************************************************************************
 * @file    audio_recorder.h
 * @author  Basile, Titouan, Guillaume
 * @date    Avril 2026
 * @brief   Module d'enregistrement audio via le convertisseur analogique-numérique (ADC).
 *******************************************************************************
 */

#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include "config.h"
#include "stm32g4_adc.h"
#include "stm32g4_flash.h"
#include <stdint.h>
#include <stdbool.h>

#define AUDIO_SAMPLE_RATE_HZ     1000U ///< Fréquence d'échantillonnage de la capture (1 kHz)
#define AUDIO_DURATION_MS        1920U ///< Durée maximale d'un enregistrement en millisecondes
#define AUDIO_SAMPLE_COUNT       ((AUDIO_SAMPLE_RATE_HZ * AUDIO_DURATION_MS) / 1000U) ///< Nombre total d'échantillons (1920 samples)

/**
 * @enum AudioStatus_t
 * @brief Codes de retour pour les opérations audio.
 */
typedef enum
{
    AUDIO_OK = 0,   ///< Opération réussie
    AUDIO_ERROR     ///< Une erreur est survenue
} AudioStatus_t;

/**
 * @brief  Initialise le module d'enregistrement audio (effacement des buffers).
 * @return Aucun.
 */
void AudioRecorder_Init(void);

/**
 * @brief  Démarre une capture audio bloquante sur le canal ADC spécifié.
 * @details La cadence est imposée par l'unité DWT du processeur.
 * @param  channel Identifiant du canal ADC d'entrée (provenance micro).
 * @return Statut de l'enregistrement de type ::AudioStatus_t.
 */
AudioStatus_t AudioRecorder_Record(adc_id_e channel);

/**
 * @brief  Compresse le buffer audio 12-bits en 8-bits et l'écrit dans la mémoire Flash.
 * @details Utilise le stockage par paquets de 64 bits (Double Word) requis par le STM32G4.
 * @return Statut de l'opération (::AUDIO_OK).
 */
AudioStatus_t AudioRecorder_SaveToFlash(void);

/**
 * @brief  Vérifie si la capture en cours est terminée.
 * @return true si l'enregistrement est fini, false sinon.
 */
bool AudioRecorder_IsFinished(void);

/**
 * @brief  Récupère un échantillon précis du buffer RAM.
 * @param  index Position de l'échantillon (0 à ::AUDIO_SAMPLE_COUNT - 1).
 * @return Valeur brute 12 bits de l'échantillon.
 */
uint16_t AudioRecorder_GetSample(uint32_t index);

/**
 * @brief  Renvoie le nombre d'échantillons total d'une session audio.
 * @return Taille du buffer en nombre d'échantillons.
 */
uint32_t AudioRecorder_GetSampleCount(void);

/**
 * @brief  Permet d'obtenir un pointeur direct vers le buffer de stockage RAM.
 * @return Pointeur constant vers le tableau d'échantillons 16-bits.
 */
const uint16_t *AudioRecorder_GetBuffer(void);

#endif