/*
 * display.c
 *
 *  Created on: 11 mars 2026
 *      Author: guillaume
 */

#include "display.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "stm32g4_gpio.h"
#include "stm32g4_adc.h"

void DISPLAY_Init(void)
{
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);

    ILI9341_Init();

    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    ILI9341_Fill(ILI9341_COLOR_GREEN);
}


#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

#define C_BACKGROUND   RGB565(240, 244, 248)
#define C_CARD_BG      RGB565(255, 255, 255)
#define C_CARD_BORDER  RGB565(220, 225, 230)
#define C_HEADER       RGB565(44, 62, 80)
#define C_TEXT_MAIN    RGB565(52, 73, 94)
#define C_TEXT_LIGHT   RGB565(149, 165, 166)
#define C_ACCENT_TEMP  RGB565(231, 76, 60)
#define C_ACCENT_HUM   RGB565(52, 152, 219)
#define C_STATUS_OK    RGB565(46, 204, 113)


void DISPLAY_DrawGraphScreen(void)
{
    ILI9341_Fill(C_BACKGROUND);
    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, "OSCILLOSCOPE ADC", &Font_7x10, C_CARD_BG, C_HEADER);

    ILI9341_DrawFilledRectangle(19, 49, 301, 221, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(20, 50, 300, 220, C_CARD_BG);

    ILI9341_Puts(20, 35, "Signal brut (0-4095)", &Font_7x10, C_TEXT_LIGHT, C_BACKGROUND);
}


static void DISPLAY_DrawMessageScreen(char *title,
                                      char *line1,
                                      char *line2)
{
    ILI9341_Fill(C_BACKGROUND);

    /* Bandeau supérieur */
    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, title, &Font_7x10, C_CARD_BG, C_HEADER);

    /* Carte centrale */
    ILI9341_DrawFilledRectangle(19, 59, 301, 191, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(20, 60, 300, 190, C_CARD_BG);

    /* Texte */
    ILI9341_Puts(45, 105, line1, &Font_7x10, C_TEXT_MAIN, C_CARD_BG);

    if (line2 != 0)
    {
        ILI9341_Puts(45, 125, line2, &Font_7x10, C_TEXT_MAIN, C_CARD_BG);
    }
}


void DISPLAY_ShowRecordPrompt(void)
{
    DISPLAY_DrawMessageScreen(
        "ENREGISTREMENT AUDIO",
        "Appuyez sur le bouton",
        "pour demarrer"
    );
}


void DISPLAY_ShowRecording(void)
{
    DISPLAY_DrawMessageScreen(
        "ENREGISTREMENT AUDIO",
        "Enregistrement...",
        0
    );
}


void DISPLAY_ShowSaving(void)
{
    DISPLAY_DrawMessageScreen(
        "MEMORISATION AUDIO",
        "Sauvegarde en Flash...",
        0
    );
}


void DISPLAY_ShowPlayPrompt(void)
{
    DISPLAY_DrawMessageScreen(
        "ERREUR",
        "Veuillez enregistrer",
        "un signal d'abord"
    );
}


void DISPLAY_ShowPlaying(void)
{
    DISPLAY_DrawMessageScreen(
        "LECTURE AUDIO",
        "Lecture en cours...",
        0
    );
}


void DISPLAY_ShowFinished(void)
{
    DISPLAY_DrawMessageScreen(
        "LECTURE TERMINEE",
        "Appuyez pour",
        "recommencer"
    );
}

void DISPLAY_ShowRecordFinished(void)
{
    DISPLAY_DrawMessageScreen(
        "ENREGISTREMENT",
        "Enregistrement terminé",
		0
    );
}

void DISPLAY_DrawRecordedSignal(const uint16_t *samples, uint32_t sample_count)
{
    uint16_t x;
    uint32_t index;
    uint16_t adc_value;
    uint16_t y;

    if (samples == 0 || sample_count == 0)
    {
        DISPLAY_ShowPlayPrompt();
        return;
    }

    /*
     * On utilise l'écran de graphe
     */
    DISPLAY_DrawGraphScreen();

    /*
     * On remplace le titre par quelque chose de plus adapté.
     */
    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, "SIGNAL ENREGISTRE", &Font_7x10, C_CARD_BG, C_HEADER);

    /*
     * Petite indication à l'utilisateur.
     */
    ILI9341_Puts(175, 35, "Appuyez pour lire", &Font_7x10, C_TEXT_LIGHT, C_BACKGROUND);

    /*
     * La zone utile va environ de x = 21 à x = 298.
     * On "échantillonne" le buffer complet pour l'adapter
     * à la largeur de l'écran.
     */
    for (index = 0; index < sample_count; index++)
    {
        adc_value = samples[index];

        if (adc_value > 4095)
        {
            adc_value = 4095;
        }
        else if (adc_value<0)
        {
        	adc_value=0;
        }

        /*
         * Projection de tout le buffer sur la largeur du graphe :
         * x va de 21 à 298
         */
        x = 21 + ((index * (298 - 21)) / (sample_count - 1));

        /*
         * Projection ADC 0-4095 sur la hauteur du graphe :
         * y va de 220 à 50
         */
        y = 220 - ((adc_value * 170) / 4095);


        ILI9341_DrawFilledRectangle(
            x,
            y - 1,
            x + 1,
            y + 1,
            C_ACCENT_TEMP
        );
    }
}

void DISPLAY_DrawMenu(uint8_t selected_index)
{
    ILI9341_Fill(C_BACKGROUND);

    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, "MENU AUDIO", &Font_7x10, C_CARD_BG, C_HEADER);

    ILI9341_DrawFilledRectangle(19, 49, 301, 221, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(20, 50, 300, 220, C_CARD_BG);

    const char *items[] =
    {
        "Enregistrer",
        "Lire audio",
        "Afficher signal"
    };

    for (uint8_t i = 0; i < 3; i++)
    {
        uint16_t y = 75 + i * 35;

        if (i == selected_index)
        {
            ILI9341_DrawFilledRectangle(35, y - 5, 285, y + 18, C_ACCENT_HUM);
            ILI9341_Puts(45, y, ">", &Font_7x10, C_CARD_BG, C_ACCENT_HUM);
            ILI9341_Puts(65, y, (char *)items[i], &Font_7x10, C_CARD_BG, C_ACCENT_HUM);
        }
        else
        {
            ILI9341_Puts(65, y, (char *)items[i], &Font_7x10, C_TEXT_MAIN, C_CARD_BG);
        }
    }

    ILI9341_Puts(35, 200, "H/B: naviguer  Centre: OK", &Font_7x10, C_TEXT_LIGHT, C_CARD_BG);
}
