#include "ui.h"
#include "display.h"
#include "stm32g4_adc.h"
#include "stm32g4_gpio.h"
#include <stdlib.h>

// Variables "static" pour qu'elles restent mémorisées entre chaque tour de boucle
// et qu'elles soient privées (visibles uniquement dans ce fichier)
static uint8_t ecran_actuel = 0;
static uint8_t ecran_doit_changer = 1;
static uint8_t etat_bouton_prec = 0;

void UI_Init(void)
{
    // Initialisation du matériel géré par l'UI
    DISPLAY_Init();
    BSP_ADC_init();

    // État initial
    ecran_actuel = 0;
    ecran_doit_changer = 1;
    etat_bouton_prec = 0;
}

void UI_Process(bool etat_bouton)
{

    if (etat_bouton == 1 && etat_bouton_prec == 0)
    {
        ecran_actuel++;
        if (ecran_actuel > 1) {
            ecran_actuel = 0;
        }
        ecran_doit_changer = 1;
    }
    etat_bouton_prec = etat_bouton;


    // 2. Changement d'écran si nécessaire
    if (ecran_doit_changer == 1)
    {
        if (ecran_actuel == 0) {
            DISPLAY_DrawBeautifulUI();
        }
        else if (ecran_actuel == 1) {
            DISPLAY_DrawGraphScreen();
        }
        ecran_doit_changer = 0;
    }

    // 3. Mise à jour de l'écran actif
    if (ecran_actuel == 0)
    {
        // Plus tard : Mettre à jour les textes du Dashboard ici
    }
    else if (ecran_actuel == 1)
    {
    	uint8_t fausses_frequences[8];

		// On simule de la musique avec des nombres aléatoires pour tester le visuel
		for(int i = 0; i < 8; i++) {
			// Génère un niveau aléatoire entre 10% et 90%
			fausses_frequences[i] = 10 + (rand() % 80);
		}

		// On envoie le tableau à l'écran !
		DISPLAY_UpdateSpectrum(fausses_frequences);
    }
}
