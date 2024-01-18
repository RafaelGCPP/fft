#include <complex.h>
#include <math.h>
#include <stdio.h>
#include "fix_fft.h"
#include "fix_fft_core.h"

void fft_fix(int *data, int l2n, int *twiddle, int *bitrev)
{
    radix_2_dit_fft_fix(data, l2n, twiddle, bitrev, 1, 1);
}

void ifft_fix(int *data, int l2n, int *twiddle, int *bitrev)
{
    radix_2_dit_fft_fix(data, l2n, twiddle, bitrev, 1, -1);
}
