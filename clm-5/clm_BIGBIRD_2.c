/* translate bigbird-2 in naive.lisp to C
 *   written Thu 6-Oct-22 at 2:36 by CLM of 8-May-18
 */

#include <mus-config.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <signal.h>
#include <cmus.h>

static sig_atomic_t got_sigint = 0; /* catch C-C if hung */
static void sig_err(int sig) {got_sigint = sig;}

int clm_bigbird_22 (double *clm_double, int datar_len, int *clm_int, int datai_len)
{
  /* The _clm_* variables are temporary values generated by the run macro */
  void (*old_SIGINT)(int);
  mus_long_t I;
  double _clm_5010, _clm_5011, _clm_5012, _clm_5013, _clm_5014, _clm_5015;
  mus_any *LOC = NULL, *FIL = NULL, *AMP_ENV = NULL, *OS = NULL, *GLS_ENV = NULL;
  void *all_gens = NULL;
  mus_long_t clm_beg, clm_end;
  
  all_gens = clm_make_genbag();
  clm_beg = clm_to_mus_long_t(clm_int, 1);
  clm_end = clm_to_mus_long_t(clm_int, 3);
  if (CLM_ENV_P(5))
    GLS_ENV = clm_add_gen_to_genbag(all_gens, 
      mus_make_env(
        (double *)(clm_double + CLM_RLOC(5) + 3), /* breakpoints */
        clm_int[CLM_ILOC(5) + 2], /* num points */
        clm_double[CLM_RLOC(5) + 1], /* scaler */
        clm_double[CLM_RLOC(5) + 2], /* offset */
        clm_double[CLM_RLOC(5)], /* base */
        0.0, /* dur useless here */
        clm_int[CLM_ILOC(5) + 3], /* end */
        NULL)); /* original data -- handled internally */
  if (CLM_POLYSHAPE_P(7))
    OS = clm_add_gen_to_genbag(all_gens, 
      mus_make_polyshape(
        mus_radians_to_hz(clm_double[CLM_RLOC(7)]),
        clm_double[CLM_RLOC(7) + 1],
        (double *)(clm_double + CLM_RLOC(7) + 2),
        clm_int[CLM_ILOC(7) + 2], MUS_CHEBYSHEV_FIRST_KIND));
  if (CLM_ENV_P(9))
    AMP_ENV = clm_add_gen_to_genbag(all_gens, 
      mus_make_env(
        (double *)(clm_double + CLM_RLOC(9) + 3), /* breakpoints */
        clm_int[CLM_ILOC(9) + 2], /* num points */
        clm_double[CLM_RLOC(9) + 1], /* scaler */
        clm_double[CLM_RLOC(9) + 2], /* offset */
        clm_double[CLM_RLOC(9)], /* base */
        0.0, /* dur useless here */
        clm_int[CLM_ILOC(9) + 3], /* end */
        NULL)); /* original data -- handled internally */
  if (CLM_ONE_POLE_P(11))
    FIL = clm_add_gen_to_genbag(all_gens, 
      mus_make_one_pole(
        clm_double[CLM_RLOC(11)],
        clm_double[CLM_RLOC(11) + 1]));
  if (CLM_LOCSIG_P(13))
    LOC = clm_add_gen_to_genbag(all_gens, 
      mus_make_locsig(
        clm_double[CLM_RLOC(13)],
        clm_double[CLM_RLOC(13) + 1],
        clm_double[CLM_RLOC(13) + 2],
        clm_int[CLM_ILOC(13) + 2],
        clm_output(), (clm_reverb()) ? mus_channels(clm_reverb()) : 0, clm_reverb(),
        clm_int[CLM_ILOC(13) + 3]));
  I = clm_int[17];
  if (clm_beg > clm_end) return(1);
  got_sigint = 0; old_SIGINT = clm_signal(SIGINT, sig_err);                     /* trap SIGINT */
  I = clm_beg;                                                                  /* pass counter */

SAMPLE_LOOP_BEGIN:
  if (got_sigint != 0) {clm_int[0] = (int)got_sigint; goto RUN_ALL_DONE;}
  if (I > clm_end) {I = clm_end; goto RUN_ALL_DONE;}
                                                                                /* (progn */
  _clm_5013 = mus_env(AMP_ENV);                                                 /* (env AMP-ENV) */
  _clm_5015 = mus_env(GLS_ENV);                                                 /* (env GLS-ENV) */
  _clm_5014 = mus_polyshape(OS, 1.0, _clm_5015);                                /* (polyshape OS 1.0 _clm_5015) */
                                                                                /* (* _clm_5013 _clm_5014) */
  _clm_5012 = ((_clm_5013) * (_clm_5014));
  _clm_5011 = mus_one_pole(FIL, _clm_5012);                                     /* (one-pole FIL _clm_5012) */
  _clm_5010 = clm_locsig(LOC, I, _clm_5011);
  I++;                                                                          /* increment pass counter and loop */
goto SAMPLE_LOOP_BEGIN;

RUN_ALL_DONE:
  clm_signal(SIGINT,old_SIGINT);
  if (all_gens) clm_free_genbag(all_gens);

  return(1);
}

