/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: effet_echo_initialize.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 27-May-2026 15:18:31
 */

/* Include Files */
#include "effet_echo_initialize.h"
#include "effet_echo.h"
#include "effet_echo_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void effet_echo_initialize(void)
{
  effet_echo_init();
  isInitialized_effet_echo = true;
}

/*
 * File trailer for effet_echo_initialize.c
 *
 * [EOF]
 */
