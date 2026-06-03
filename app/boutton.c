/**
 *******************************************************************************
 * @file    boutton.c
 * @author  Basile, Titouan, Guillaume
 * @date    13 mars 2026
 * @brief   Implémentation des fonctions de lecture des boutons poussoirs.
 *******************************************************************************
 */

#include "boutton.h"
#include "stm32g4_gpio.h"

/** @brief Tableau des ports GPIO associés à chaque bouton (aligné sur l'énumération ButtonId) */
static GPIO_TypeDef* buttonPorts[BUTTON_COUNT] = {
        GPIOA, // center
        GPIOB, // up
        GPIOB, // down
        GPIOB, // left
        GPIOA  // right
};

/** @brief Tableau des numéros de broches associés à chaque bouton */
static uint16_t buttonPins[BUTTON_COUNT] = {
        GPIO_PIN_0,  // center
        GPIO_PIN_0,  // up
        GPIO_PIN_4,  // down
        GPIO_PIN_6,  // left
        GPIO_PIN_12  // right
};

void BUTTON_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    for(int i = 0; i < BUTTON_COUNT; i++)
    {
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
    uint8_t a = HAL_GPIO_ReadPin(buttonPorts[button], buttonPins[button]);

    if(!a)
        return true;
    else
        return false;
}