/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: effet_distorsion.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 20-May-2026 14:41:36
 */

/* Include Files */
#include "effet_distorsion.h"

/* Function Definitions */
/*
 * EFFET_DISTORSION : Applique un effet de saturation (Hard Clipping)
 *  signal_in : Tableau des échantillons provenant de l'ADC
 *  gain      : Facteur de multiplication du volume
 *  seuil     : Valeur maximale autorisée (pour simuler la limite matérielle)
 *
 * Arguments    : short signal_in
 *                short gain
 *                short seuil
 * Return Type  : short
 */
short effet_distorsion(short signal_in, short gain, short seuil)
{
  int i;
  int i1;
  short signal_out;
  /*  1. On amplifie le signal d'entrée */
  /*  2. Écrêtage (Hard Clipping) */
  /*  Tout ce qui dépasse le seuil positif est bloqué au seuil */
  i = signal_in * gain;
  i1 = i;
  if (i > 32767) {
    i1 = 32767;
  } else if (i < -32768) {
    i1 = -32768;
  }
  signal_out = (short)i1;
  if (i > 32767) {
    i = 32767;
  } else if (i < -32768) {
    i = -32768;
  }
  if ((short)i > seuil) {
    signal_out = seuil;
  }
  /*  Tout ce qui dépasse le seuil négatif est bloqué au seuil négatif */
  i = -seuil;
  if (-seuil > 32767) {
    i = 32767;
  }
  if (signal_out < (short)i) {
    i = -seuil;
    if (-seuil > 32767) {
      i = 32767;
    }
    signal_out = (short)i;
  }
  /*  3. On renvoie le signal traité vers le DAC */
  return signal_out;
}

/*
 * File trailer for effet_distorsion.c
 *
 * [EOF]
 */
