#include "ui.h"
#include "display.h"
#include "audio_recorder.h"
#include "audio_player.h"
#include "stm32g4_adc.h"
#include <stdio.h>

typedef enum
{
    UI_WAIT_RECORD = 0,
    UI_WAIT_PLAY
} UI_State_t;

static UI_State_t ui_state = UI_WAIT_RECORD;
static bool etat_bouton_prec = false;


/*
 * Renvoie true uniquement au moment où le bouton
 * vient juste d'être appuyé.
 */
static bool UI_ButtonPressedEvent(bool etat_bouton)
{
    bool nouvel_appui = (etat_bouton == true && etat_bouton_prec == false);

    etat_bouton_prec = etat_bouton;

    return nouvel_appui;
}


void UI_Init(void)
{
    DISPLAY_Init();

    BSP_ADC_init();
    AudioRecorder_Init();
    AudioPlayer_Init();

    ui_state = UI_WAIT_RECORD;
    etat_bouton_prec = false;

    DISPLAY_ShowRecordPrompt();
}


void UI_Process(bool etat_bouton)
{
    if (!UI_ButtonPressedEvent(etat_bouton))
    {
        return;
    }

    /*
     * État 1 :
     * L'utilisateur doit appuyer pour enregistrer.
     */
    if (ui_state == UI_WAIT_RECORD)
    {
        DISPLAY_ShowRecording();

        AudioRecorder_Record(ADC_2);

        for (uint32_t i = 0; i < AudioRecorder_GetSampleCount(); i++)
        {
            printf("%lu : %u\r\n", i, AudioRecorder_GetSample(i));
        }

        DISPLAY_ShowSaving();

        AudioRecorder_SaveToFlash();

        DISPLAY_DrawRecordedSignal(
            AudioRecorder_GetBuffer(),
            AudioRecorder_GetSampleCount()
        );

        ui_state = UI_WAIT_PLAY;
    }

    /*
     * État 2 :
     * L'utilisateur doit rappuyer pour lire.
     */
    else if (ui_state == UI_WAIT_PLAY)
    {
        DISPLAY_ShowPlaying();

        AudioPlayer_PlayFromFlash();

        DISPLAY_ShowFinished();

        ui_state = UI_WAIT_RECORD;
    }
}
