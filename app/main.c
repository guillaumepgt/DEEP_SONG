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
    	bool up = BUTTON_IsPressed(BUTTON_UP);
    	UI_Process(up);
    	HAL_Delay(10);

    }
}
