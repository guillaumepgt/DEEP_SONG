/**
 *******************************************************************************
 * @file    main.c
 * @author  Basile, Titouan, Guillaume
 * @date    Juin 2026
 * @brief   Fichier d'entrée principal (Main Loop) du projet Carte Son STM32.
 * @details Lance la boucle d'exécution logicielle et cadence le scrutation IHM.
 *******************************************************************************
 */

#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include <stdio.h>
#include "boutton.h"
#include <stdlib.h>
#include "ui.h"

/**
 * @brief  Point d'entrée de l'application embarquée.
 * @return Entier (jamais atteint en embarqué).
 */
int main(void)
{
    HAL_Init();
    BSP_GPIO_enable();
    BSP_UART_init(UART2_ID, 115200);
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

    UI_Init();
    BUTTON_Init();

    while (1)
    {
        UI_Input_t input;

        input.center = BUTTON_IsPressed(BUTTON_CENTER);
        input.up     = BUTTON_IsPressed(BUTTON_UP);
        input.down   = BUTTON_IsPressed(BUTTON_DOWN);
        input.left   = BUTTON_IsPressed(BUTTON_LEFT);
        input.right  = BUTTON_IsPressed(BUTTON_RIGHT);

        UI_Process(input);

        HAL_Delay(10);
    }
    return 1;
}
