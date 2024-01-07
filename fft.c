#include <complex.h>
#include <math.h>
#include <stdio.h>
#include "fft.h"
#include "fft_core.h"


void fft(float *data, int n, float *twiddle)
{
    radix_2_dit_fft(data, n, twiddle, 1);
}

void ifft(float *data, int n, float *twiddle)
{
    float complex *cdata = (float complex *)data;

    for (int i = 0; i < n; i++)
        cdata[i] = conj(cdata[i]) / sqrt(n);

    radix_2_dit_fft(data, n, twiddle, 1);

    for (int i = 0; i < n; i++)
        cdata[i] = conj(cdata[i]) / sqrt(n);
}

