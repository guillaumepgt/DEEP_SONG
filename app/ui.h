/**
 *******************************************************************************
 * @file    ui.h
 * @author  Basile, Titouan, Guillaume
 * @date    Juin 2026
 * @brief   Déclarations des structures logiques de l'IHM (Interface Homme-Machine).
 *******************************************************************************
 */

#ifndef UI_H_
#define UI_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @struct UI_Input_t
 * @brief Conteneur logique de l'état d'activité des boutons d'action.
 */
typedef struct
{
    bool center; ///< État logique du bouton Central
    bool up;     ///< État logique du bouton Haut
    bool down;   ///< État logique du bouton Bas
    bool left;   ///< État logique du bouton Gauche
    bool right;  ///< État logique du bouton Droite
} UI_Input_t;

/**
 * @brief  Initialise l'afficheur, l'ADC, et dessine l'écran principal d'accueil du projet.
 * @return Aucun.
 */
void UI_Init(void);

/**
 * @brief  Machine à états exécutée périodiquement pour traiter la navigation IHM.
 * @details Filtre les fronts montants des boutons pour valider ou changer de page.
 * @param  input Copie instantanée de la structure ::UI_Input_t lue par les GPIO.
 * @return Aucun.
 */
void UI_Process(UI_Input_t input);

#endif /* UI_H_ */