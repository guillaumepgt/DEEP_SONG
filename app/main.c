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
#include "stm32g4_adc.h"
#include "stm32g4_flash.h"
#include "stm32g4_dac.h"

#include <stdio.h>

#include "audio_recorder.h"
#include "audio_player.h"

int main(void)
{
    HAL_Init();

    BSP_GPIO_enable();
    BSP_UART_init(UART2_ID, 115200);
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
    BSP_ADC_init();

    AudioRecorder_Init();
    AudioPlayer_Init();

    printf("Debut enregistrement...\r\n");

    AudioRecorder_Record(ADC_2);

    printf("Enregistrement termine\r\n");

    if (AudioRecorder_SaveToFlash() == AUDIO_OK)
    {
        printf("Sauvegarde flash OK\r\n");
    }
    else
    {
        printf("Erreur sauvegarde flash\r\n");
    }

    printf("Lecture en boucle...\r\n");
    int i=0;
    while (1)
    {

        printf("Lecture %d ...\r\n",i++);
    	//AudioPlayer_PlayFromFlash();

        // petite pause entre deux lectures (optionnel)
        //HAL_Delay(200);
    }
}
