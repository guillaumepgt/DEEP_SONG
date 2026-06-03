/**
 *******************************************************************************
 * @file    boutton.h
 * @author  Basile, Titouan, Guillaume
 * @date    13 mars 2026
 * @brief   Gestionnaire des boutons de la carte de développement.
 *******************************************************************************
 */

#ifndef BOUTTON_H
#define BOUTTON_H

#include "stm32g4xx_hal.h"
#include <stdbool.h>

#define BUTTON_COUNT 5 ///< Nombre total de boutons configurés sur le système

/**
 * @enum ButtonId
 * @brief Identifiants uniques pour chaque bouton du joystick/clavier.
 */
typedef enum {
    BUTTON_CENTER = 0, ///< Bouton central (Validation / OK)
    BUTTON_UP = 1,     ///< Bouton Haut (Navigation)
    BUTTON_DOWN = 2,   ///< Bouton Bas (Navigation)
    BUTTON_LEFT = 3,   ///< Bouton Gauche (Retour)
    BUTTON_RIGHT = 4   ///< Bouton Droite
} ButtonId;

/**
 * @brief  Initialise les broches GPIO des 5 boutons en entrée numérique.
 * @return Aucun.
 */
void BUTTON_Init(void);

/**
 * @brief  Vérifie l'état de pression d'un bouton spécifique.
 * @param  button Identifiant du bouton à tester (de type ::ButtonId).
 * @return true si le bouton est pressé, false sinon.
 */
bool BUTTON_IsPressed(ButtonId button);

#endif