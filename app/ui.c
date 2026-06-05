/**
 *******************************************************************************
 * @file    ui.c
 * @author  Basile, Titouan, Guillaume
 * @date    Juin 2026
 * @brief   Implémentation de la machine à états de l'IHM.
 *******************************************************************************
 */

#include "ui.h"
#include "display.h"
#include "audio_recorder.h"
#include "audio_player.h"
#include "stm32g4_adc.h"

#include <stdbool.h>


/**
 * @enum UI_MenuItem_t
 * @brief Liste des actions disponibles dans le menu principal.
 */
typedef enum
{
    MENU_RECORD = 0,
    MENU_PLAY,
    MENU_SHOW_SIGNAL,
    MENU_COUNT
} UI_MenuItem_t;


/**
 * @enum UI_State_t
 * @brief Liste des états possibles de l'IHM.
 */
typedef enum
{
    UI_STATE_MENU = 0,
    UI_STATE_RECORDING,
    UI_STATE_SAVING,
    UI_STATE_PLAYING,
    UI_STATE_SHOW_SIGNAL,
    UI_STATE_NO_AUDIO
} UI_State_t;


/* Variables internes */
static uint8_t menu_index = 0;
static UI_State_t ui_state = UI_STATE_MENU;
static bool audio_available = false;

bool fuzz_actif = false;

static UI_Input_t previous_input;


/**
 * @brief Détecte un front montant sur un bouton.
 *
 * @param current État courant du bouton.
 * @param previous État précédent du bouton.
 *
 * @return true si le bouton vient d'être appuyé, false sinon.
 */
static bool UI_RisingEdge(bool current, bool previous)
{
    return (current == true) && (previous == false);
}


/**
 * @brief Initialise l'IHM.
 */
void UI_Init(void)
{
    DISPLAY_Init();
    BSP_ADC_init();
    AudioRecorder_Init();

    menu_index = 0;
    ui_state = UI_STATE_MENU;
    audio_available = false;
    fuzz_actif = false;

    previous_input.center = false;
    previous_input.up = false;
    previous_input.down = false;
    previous_input.left = false;
    previous_input.right = false;

    DISPLAY_DrawMenu(menu_index);
}


/**
 * @brief Machine à états exécutée périodiquement.
 *
 * @param input État actuel des boutons.
 */
void UI_Process(UI_Input_t input)
{
    bool event_center;
    bool event_up;
    bool event_down;
    bool event_left;
    bool event_right;

    bool continue_state_machine = true;

    event_center = UI_RisingEdge(input.center, previous_input.center);
    event_up     = UI_RisingEdge(input.up, previous_input.up);
    event_down   = UI_RisingEdge(input.down, previous_input.down);
    event_left   = UI_RisingEdge(input.left, previous_input.left);
    event_right  = UI_RisingEdge(input.right, previous_input.right);

    previous_input = input;

    while (continue_state_machine)
    {
        continue_state_machine = false;

        if (event_right){
        	fuzz_actif = !fuzz_actif;
        }

        switch (ui_state)
        {
            case UI_STATE_MENU:  //On affiche que à chaque appui pour eviter le scintillement
                if (event_up && menu_index > 0)
                {
					menu_index--;
					DISPLAY_DrawMenu(menu_index);

                }
                else if (event_down && menu_index < (MENU_COUNT - 1))
                {
                        menu_index++;
                        DISPLAY_DrawMenu(menu_index);
                }
                else if (event_left) //Retourne sur le menu si on a pas actualisé après l'enregistrement (après l'enregisterment ou l'affichage on revient dans state_menu mais on n'affiche pas le menu tant qu'un bouton n'est pas pressé)
                {
                    DISPLAY_DrawMenu(menu_index);
                }
                else if (event_center)
                {
                    if (menu_index == MENU_RECORD)
                    {
                        ui_state = UI_STATE_RECORDING;
                        continue_state_machine = true;
                    }
                    else if (menu_index == MENU_PLAY)
                    {
                        if (audio_available)
                        {
                            ui_state = UI_STATE_PLAYING;
                        }
                        else
                        {
                            ui_state = UI_STATE_NO_AUDIO;
                        }

                        continue_state_machine = true;
                    }
                    else if (menu_index == MENU_SHOW_SIGNAL)
                    {
                        if (audio_available)
                        {
                            ui_state = UI_STATE_SHOW_SIGNAL;
                        }
                        else
                        {
                            ui_state = UI_STATE_NO_AUDIO;
                        }

                        continue_state_machine = true;
                    }
                }
                break;

            case UI_STATE_RECORDING:
                DISPLAY_ShowRecording();
                AudioRecorder_Record(ADC_2);

                ui_state = UI_STATE_SAVING;
                continue_state_machine = true;
                break;

            case UI_STATE_SAVING:
                DISPLAY_ShowSaving();
                AudioRecorder_SaveToFlash();

                audio_available = true;

                DISPLAY_ShowRecordFinished();

                ui_state = UI_STATE_MENU;
                break;

            case UI_STATE_PLAYING:
                DISPLAY_ShowPlaying();

                AudioPlayer_Init();
                AudioPlayer_PlayFromFlash(fuzz_actif);

                DISPLAY_Init();
                DISPLAY_ShowFinished();

                ui_state = UI_STATE_MENU;
                break;

            case UI_STATE_SHOW_SIGNAL:
                DISPLAY_DrawRecordedSignal(
                    AudioRecorder_GetBuffer(),
                    AudioRecorder_GetSampleCount()
                );

                ui_state = UI_STATE_MENU;
                break;

            case UI_STATE_NO_AUDIO:
                DISPLAY_ShowPlayPrompt();

                ui_state = UI_STATE_MENU;
                break;

            default:
                ui_state = UI_STATE_MENU;
                DISPLAY_DrawMenu(menu_index);
                break;
        }
    }
}
