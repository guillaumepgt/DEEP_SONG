/**
 *******************************************************************************
 * @file    ui.c
 * @author  Basile, Titouan, Guillaume
 * @date    Juin 2026
 * @brief   Implémentation de l'ordonnanceur logique et visuel de l'IHM.
 *******************************************************************************
 */

#include "ui.h"
#include "display.h"
#include "audio_recorder.h"
#include "audio_player.h"
#include "stm32g4_adc.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @enum UI_MenuItem_t
 * @brief Liste ordonnée des pages accessibles via l'arborescence du menu principal.
 */
typedef enum
{
    MENU_RECORD = 0,   ///< Index de la commande d'enregistrement
    MENU_PLAY,         ///< Index de la commande de lecture haut-parleur
    MENU_SHOW_SIGNAL,  ///< Index de la commande d'affichage de l'oscilloscope
    MENU_COUNT         ///< Indicateur de limite supérieure du menu
} UI_MenuItem_t;

static uint8_t menu_index = 0;       ///< Position actuelle de l'index dans le menu
static bool audio_available = false; ///< Drapeau de validité indiquant la présence d'une onde en Flash

bool fuzz_actif=false;

static UI_Input_t previous_input;

/**
 * @brief  Détecteur interne de front montant (Rising Edge) pour isoler une impulsion unique.
 * @param  current État logique courant du bouton.
 * @param  previous État logique mémorisé au cycle précédent.
 * @return true si une transition de 0 vers 1 est repérée, false sinon.
 */
static bool UI_RisingEdge(bool current, bool previous)
{
    return current == true && previous == false;
}

void UI_Init(void)
{
    DISPLAY_Init();
    BSP_ADC_init();
    AudioRecorder_Init();

    menu_index = 0;
    audio_available = false;
    fuzz_actif=false;

    previous_input.center = false;
    previous_input.up = false;
    previous_input.down = false;
    previous_input.left = false;
    previous_input.right = false;

    DISPLAY_DrawMenu(menu_index);
}

void UI_Process(UI_Input_t input)
{
    bool event_center = UI_RisingEdge(input.center, previous_input.center);
    bool event_up     = UI_RisingEdge(input.up, previous_input.up);
    bool event_down   = UI_RisingEdge(input.down, previous_input.down);
    bool event_left   = UI_RisingEdge(input.left, previous_input.left);
    bool event_right  = UI_RisingEdge(input.right, previous_input.right);

    previous_input = input;

    if (event_up)
    {
        if (menu_index > 0)
        {
            menu_index--;
            DISPLAY_DrawMenu(menu_index);
        }
    }
    else if (event_down)
    {
        if (menu_index < MENU_COUNT-1)
        {
            menu_index++;
            DISPLAY_DrawMenu(menu_index);
        }
    }
    else if (event_left)
    {
        DISPLAY_DrawMenu(menu_index);
    }
    else if (event_right)
    {
    	if(menu_index==MENU_PLAY)
    	{
    	fuzz_actif= !fuzz_actif;
    	}
    }
    else if (event_center)
    {
        if (menu_index == MENU_RECORD)
        {
            DISPLAY_ShowRecording();
            AudioRecorder_Record(ADC_2);
            DISPLAY_ShowSaving();
            AudioRecorder_SaveToFlash();
            audio_available = true;
            DISPLAY_ShowRecordFinished();
        }
        else if (menu_index == MENU_PLAY)
        {
            if (audio_available)
            {
                DISPLAY_ShowPlaying();
                AudioPlayer_Init();
                AudioPlayer_PlayFromFlash(fuzz_actif);
                DISPLAY_Init();
                DISPLAY_ShowFinished();
            }
            else
            {
                DISPLAY_ShowPlayPrompt();
            }
        }
        else if (menu_index == MENU_SHOW_SIGNAL)
        {
            if (audio_available)
            {
                DISPLAY_DrawRecordedSignal(
                    AudioRecorder_GetBuffer(),
                    AudioRecorder_GetSampleCount()
                );
            }
            else
            {
                DISPLAY_ShowPlayPrompt();
            }
        }
    }
}
