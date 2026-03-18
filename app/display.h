/*
 * display.h
 *
 *  Created on: 11 mars 2026
 *      Author: guillaume
 */

#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>

void DISPLAY_Init(void);
void DISPLAY_DrawBeautifulUI(void);
void DISPLAY_DrawGraphScreen(void);
void DISPLAY_UpdateGraph(uint16_t adc_value);

#endif /* DISPLAY_H */
