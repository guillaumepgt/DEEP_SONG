/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: _coder_effet_distorsion_api.h
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 20-May-2026 14:41:36
 */

#ifndef _CODER_EFFET_DISTORSION_API_H
#define _CODER_EFFET_DISTORSION_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int16_T effet_distorsion(int16_T signal_in, int16_T gain, int16_T seuil);

void effet_distorsion_api(const mxArray *const prhs[3], const mxArray **plhs);

void effet_distorsion_atexit(void);

void effet_distorsion_initialize(void);

void effet_distorsion_terminate(void);

void effet_distorsion_xil_shutdown(void);

void effet_distorsion_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_effet_distorsion_api.h
 *
 * [EOF]
 */
