/*
 * boutton.c
 *
 *  Created on: 13 mars 2026
 *      Author: Basile
 */

#include "boutton.h"
#include "stm32g4_gpio.h"

static GPIO_TypeDef* buttonPorts[BUTTON_COUNT] = {
        GPIOA,
        GPIOA,
        GPIOB,
        GPIOB,
        GPIOC
};

static uint16_t buttonPins[BUTTON_COUNT] = {
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_13
};

void BUTTON_Init(void)
{
    for(int i = 0; i < BUTTON_COUNT; i++)
    {
        BSP_GPIO_pin_config(
                buttonPorts[i],
                buttonPins[i],
                GPIO_MODE_INPUT,
                GPIO_PULLUP,
                GPIO_SPEED_FREQ_LOW,
                GPIO_NO_AF
        );
    }
}

uint8_t BUTTON_IsPressed(ButtonId button)
{
    if(HAL_GPIO_ReadPin(buttonPorts[button], buttonPins[button]) == GPIO_PIN_RESET)
        return 1; // appuyé (pull-up)
    else
        return 0;
}
