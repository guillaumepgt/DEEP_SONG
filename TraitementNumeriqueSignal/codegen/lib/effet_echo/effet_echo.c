/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: effet_echo.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 27-May-2026 15:18:31
 */

/* Include Files */
#include "effet_echo.h"
#include "effet_echo_data.h"
#include "effet_echo_initialize.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Variable Definitions */
static double buffer_circulaire[10000];

static double index_ecriture;

/* Function Definitions */
/*
 * Arguments    : double signal_in
 *                double gain_echo
 *                double retard_echantillons
 * Return Type  : double
 */
double effet_echo(double signal_in, double gain_echo,
                  double retard_echantillons)
{
  double signal_out;
  if (!isInitialized_effet_echo) {
    effet_echo_initialize();
  }
  signal_out =
      signal_in + buffer_circulaire[(int)(b_mod(((index_ecriture - 1.0) -
                                                 retard_echantillons) +
                                                10000.0) +
                                          1.0) -
                                    1] *
                      gain_echo;
  buffer_circulaire[(int)index_ecriture - 1] = signal_out;
  index_ecriture = b_mod(index_ecriture) + 1.0;
  return signal_out;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void effet_echo_init(void)
{
  memset(&buffer_circulaire[0], 0, 10000U * sizeof(double));
  index_ecriture = 1.0;
}

/*
 * File trailer for effet_echo.c
 *
 * [EOF]
 */
