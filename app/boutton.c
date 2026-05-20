/*
 * boutton.c
 *
 *  Created on: 13 mars 2026
 *      Author: Basile
 */

#include "boutton.h"
#include "stm32g4_gpio.h"

static GPIO_TypeDef* buttonPorts[BUTTON_COUNT] = {
        GPIOA, //center
        GPIOB, //up
        GPIOB, //down
        GPIOB, //left
        GPIOC  //right
};

static uint16_t buttonPins[BUTTON_COUNT] = {
        GPIO_PIN_0, //center
        GPIO_PIN_0, //up
        GPIO_PIN_5, //down
        GPIO_PIN_6, //left
        GPIO_PIN_13 //right
};

void BUTTON_Init(void)
{
    for(int i = 0; i < BUTTON_COUNT; i++)
    {
    	__HAL_RCC_GPIOA_CLK_ENABLE();
    	__HAL_RCC_GPIOB_CLK_ENABLE();
    	__HAL_RCC_GPIOC_CLK_ENABLE();
        BSP_GPIO_pin_config(
                buttonPorts[i],
                buttonPins[i],
                GPIO_MODE_INPUT,
                GPIO_NOPULL,
                GPIO_SPEED_FREQ_LOW,
                GPIO_NO_AF
        );
    }
}

bool BUTTON_IsPressed(ButtonId button)
{
    uint8_t a= HAL_GPIO_ReadPin(buttonPorts[button], buttonPins[button]);
	if(!a)
        return true; // appuyé (pull-up)
    else
        return false;
}
