/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: _coder_effet_echo_api.h
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 27-May-2026 15:18:31
 */

#ifndef _CODER_EFFET_ECHO_API_H
#define _CODER_EFFET_ECHO_API_H

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
real_T effet_echo(real_T signal_in, real_T gain_echo,
                  real_T retard_echantillons);

void effet_echo_api(const mxArray *const prhs[3], const mxArray **plhs);

void effet_echo_atexit(void);

void effet_echo_initialize(void);

void effet_echo_terminate(void);

void effet_echo_xil_shutdown(void);

void effet_echo_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_effet_echo_api.h
 *
 * [EOF]
 */
