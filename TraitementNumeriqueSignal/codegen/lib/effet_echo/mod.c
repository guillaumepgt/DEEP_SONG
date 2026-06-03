/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: mod.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 27-May-2026 15:18:31
 */

/* Include Files */
#include "mod.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double x
 * Return Type  : double
 */
double b_mod(double x)
{
  double r;
  if (rtIsNaN(x) || rtIsInf(x)) {
    r = rtNaN;
  } else {
    r = fmod(x, 10000.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (r < 0.0) {
      r += 10000.0;
    }
  }
  return r;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
