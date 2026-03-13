/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */

#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"

#include <stdio.h>
#include "display.h"
#include "boutton.h"


int main(void)
{
	HAL_Init();

	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID, 115200);
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

    DISPLAY_Init();
    BUTTON_Init();


	while (1)
	{
		 if (BUTTON_IsPressed(BUTTON_UP))
			 DISPLAY_ShowBoolText(1);
		 else
		     DISPLAY_ShowBoolText(0);
		 HAL_Delay(50);
	}
}
