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

void DISPLAY_ShowRecordPrompt(void);
void DISPLAY_ShowRecording(void);
void DISPLAY_ShowSaving(void);
void DISPLAY_ShowPlayPrompt(void);
void DISPLAY_ShowPlaying(void);
void DISPLAY_ShowFinished(void);
void DISPLAY_DrawRecordedSignal(const uint16_t *samples, uint32_t sample_count);


#endif /* DISPLAY_H */
