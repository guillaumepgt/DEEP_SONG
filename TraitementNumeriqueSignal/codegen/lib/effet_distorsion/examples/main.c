/*
 * Primary and Secondary School License - for use in teaching and meeting
 * course requirements at primary and secondary schools only.  Not for
 * government, commercial, university, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 25.2
 * C/C++ source code generated on  : 20-May-2026 14:41:36
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "effet_distorsion.h"
#include "effet_distorsion_initialize.h"
#include "effet_distorsion_terminate.h"

/* Function Declarations */
static short argInit_int16_T(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : short
 */
static short argInit_int16_T(void)
{
  return 0;
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* Initialize the application.
You do not need to do this more than one time. */
  effet_distorsion_initialize();
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_effet_distorsion();
  /* Terminate the application.
You do not need to do this more than one time. */
  effet_distorsion_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_effet_distorsion(void)
{
  short signal_in_tmp;
  /* Initialize function 'effet_distorsion' input arguments. */
  signal_in_tmp = argInit_int16_T();
  /* Call the entry-point 'effet_distorsion'. */
  signal_in_tmp = effet_distorsion(signal_in_tmp, signal_in_tmp, signal_in_tmp);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
