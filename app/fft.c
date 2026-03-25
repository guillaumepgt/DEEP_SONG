#include <math.h>
#include "stm32g4_adc.h"
#include "display.h"

#define SAMPLES 64
#define PI 3.14159265358979323846f

const int bins_cibles[8] = {1, 2, 4, 6, 9, 14, 20, 28};

void Traitement_Audio(void)
{
    static float echantillons[SAMPLES];
    float moyenne = 0;
    for (int i = 0; i < SAMPLES; i++) {
        echantillons[i] = (float)BSP_ADC_getValue(ADC_1);
        moyenne += echantillons[i];

        for(volatile int j = 0; j < 2000; j++);
    }

    moyenne /= SAMPLES;
    for (int i = 0; i < SAMPLES; i++) {
        echantillons[i] -= moyenne;
    }

    uint8_t barres_ecran[8] = {0};

    for (int b = 0; b < 8; b++) {
        float somme_reelle = 0;
        float somme_imaginaire = 0;
        int k = bins_cibles[b];

        for (int n = 0; n < SAMPLES; n++) {
            float angle = (2.0f * PI * k * n) / SAMPLES;
            somme_reelle += echantillons[n] * cosf(angle);
            somme_imaginaire += echantillons[n] * sinf(angle);
        }

        float puissance = sqrtf((somme_reelle * somme_reelle) + (somme_imaginaire * somme_imaginaire));
        if (puissance < 300.0f) {
				puissance = 0;
			}
        int niveau = (int)(puissance / 50.0f);

        if (niveau > 100) niveau = 100;
        if (niveau < 0) niveau = 0;

        static float barres_lissees[8] = {0};
        barres_lissees[b] = (0.2f * niveau) + (0.8f * barres_lissees[b]);

        barres_ecran[b] = (uint8_t)barres_lissees[b];
    }

    DISPLAY_UpdateSpectrum(barres_ecran);
}
