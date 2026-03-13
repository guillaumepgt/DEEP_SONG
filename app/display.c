/*
 * display.c
 *
 *  Created on: 11 mars 2026
 *      Author: guillaume
 */

#include "display.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "stm32g4_gpio.h"

void DISPLAY_Init(void)
{
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);

    ILI9341_Init();

    ILI9341_Rotate(ILI9341_Orientation_Landscape_1);
    ILI9341_Fill(ILI9341_COLOR_GREEN);
}

void DISPLAY_Test(void)
{
    ILI9341_DrawFilledRectangle(10, 10, 200, 50, ILI9341_COLOR_BLUE);

    ILI9341_Puts(20, 25, "samba chui la", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_TRANSPARENT);

    ILI9341_DrawFilledCircle(120, 150, 40, ILI9341_COLOR_RED);
}
