#include <math.h>
#include <complex.h>
#include "twiddle.h"

void precompute_twiddle_factors(float *twiddle, int n)
{
    float complex *twd = (float complex *)twiddle;
    for (int j = 0; j < n / 2; j++)
        twd[j] = cexp(-2 * M_PI * I * j / n);
}
