/**
 *******************************************************************************
 * @file    display.h
 * @author  Basile, Titouan, Guillaume
 * @date    11 mars 2026
 * @brief   Déclarations des fonctions de gestion de l'écran graphique LCD ILI9341.
 *******************************************************************************
 */

#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Etat d'activation du filtre fuzz, est modifié dans ui.c
 */
extern bool fuzz_actif;

/**
 * @brief  Initialise le bus, les broches de contrôle GPIO et l'orientation du contrôleur ILI9341.
 * @return Aucun.
 */
void DISPLAY_Init(void);

/**
 * @brief  Génère le fond d'écran et la grille pour le mode Oscilloscope graphique.
 * @return Aucun.
 */
void DISPLAY_DrawGraphScreen(void);

void DISPLAY_ShowRecordPrompt(void);     ///< Affiche l'invite de commande pour démarrer l'enregistrement
void DISPLAY_ShowRecording(void);        ///< Affiche l'écran animé d'enregistrement en cours
void DISPLAY_ShowSaving(void);           ///< Affiche le message de blocage durant l'écriture Flash
void DISPLAY_ShowPlayPrompt(void);       ///< Affiche l'erreur si la Flash ne contient aucune donnée
void DISPLAY_ShowPlaying(void);          ///< Affiche l'animation de lecture de la piste audio
void DISPLAY_ShowFinished(void);         ///< Affiche l'écran de fin de lecture audio
void DISPLAY_ShowRecordFinished(void);   ///< Affiche la fin de la capture analogique

/**
 * @brief  Trace la courbe temporelle des données audio enregistrées à l'écran.
 * @details Projette graphiquement le repère [Indice, Tension] sur la géométrie de l'afficheur.
 * @param  samples Tableau contenant les amplitudes 12 bits à dessiner.
 * @param  sample_count Quantité de points composants le vecteur.
 * @return Aucun.
 */
void DISPLAY_DrawRecordedSignal(const uint16_t *samples, uint32_t sample_count);

/**
 * @brief  Affiche le menu de sélection principal avec surbrillance dynamique.
 * @param  selected_index Index de la ligne actuellement pointée (0 à 2).
 * @return Aucun.
 */
void DISPLAY_DrawMenu(uint8_t selected_index);

#endif /* DISPLAY_H */
