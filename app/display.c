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


void DISPLAY_DrawBeautifulUI(void)
{
    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);

    ILI9341_Fill(C_BACKGROUND);

    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, "SYSTEME DE CONTROLE", &Font_7x10, C_CARD_BG, C_HEADER);


    ILI9341_DrawFilledRectangle(14, 44, 151, 121, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(15, 45, 150, 120, C_CARD_BG);

    ILI9341_DrawFilledRectangle(15, 45, 150, 48, C_ACCENT_TEMP);

    ILI9341_Puts(25, 55, "Temp. Moteurrrrr", &Font_7x10, C_TEXT_LIGHT, C_CARD_BG);

    int temperature = 42;
    ILI9341_printf(45, 80, &Font_7x10, C_ACCENT_TEMP, C_CARD_BG, "%d C", temperature);

    ILI9341_DrawFilledRectangle(164, 44, 301, 121, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(165, 45, 300, 120, C_CARD_BG);

    ILI9341_DrawFilledRectangle(165, 45, 300, 48, C_ACCENT_HUM);

    ILI9341_Puts(175, 55, "Vitesse RPM", &Font_7x10, C_TEXT_LIGHT, C_CARD_BG);

    int vitesse = 1450;
    ILI9341_printf(185, 80, &Font_7x10, C_ACCENT_HUM, C_CARD_BG, "%d", vitesse);

    ILI9341_DrawFilledRectangle(14, 139, 301, 186, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(15, 140, 300, 185, C_CARD_BG);

    ILI9341_Puts(25, 150, "Etat du systeme", &Font_7x10, C_TEXT_LIGHT, C_CARD_BG);

    ILI9341_DrawFilledCircle(40, 170, 6, C_STATUS_OK);
    ILI9341_Puts(55, 165, "En fonctionnement normal", &Font_7x10, C_TEXT_MAIN, C_CARD_BG);
}

void DISPLAY_DrawGraphScreen(void)
{
    ILI9341_Fill(C_BACKGROUND);
    ILI9341_DrawFilledRectangle(0, 0, 320, 30, C_HEADER);
    ILI9341_Puts(10, 8, "OSCILLOSCOPE ADC", &Font_7x10, C_CARD_BG, C_HEADER);

    ILI9341_DrawFilledRectangle(19, 49, 301, 221, C_CARD_BORDER);
    ILI9341_DrawFilledRectangle(20, 50, 300, 220, C_CARD_BG);

    ILI9341_Puts(20, 35, "Signal brut (0-4095)", &Font_7x10, C_TEXT_LIGHT, C_BACKGROUND);
}

void DISPLAY_UpdateGraph(uint16_t adc_value)
{
    static uint16_t current_x = 21;

    if(adc_value > 4095) adc_value = 4095;

    uint16_t y = 220 - ((adc_value * 170) / 4095);

    uint16_t clear_x = current_x + 2;
    if(clear_x > 296) clear_x = 21;

    ILI9341_DrawFilledRectangle(clear_x, 50, clear_x + 3, 220, C_CARD_BG);

    ILI9341_DrawFilledRectangle(current_x, y-1, current_x+1, y+1, C_ACCENT_TEMP);

    current_x++;

    if(current_x > 298) {
        current_x = 21;
    }
}
