#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "fft_core.h"

// This code assumes that n is a power of 2 and implements
// the real FFT algorithm. It is based on the fact that
// the FFT of a real signal is conjugate symmetric. Then you can
// consider the real input as interleaved complex data and perform
// a complex FFT. The even and odd parts are then computed.
// data - input as real data.
// n - number of real samples in the input data.
// twiddle - precomputed twiddle factors
// the result is stored in the input array, as half of the spectrum
// the N/2 sample is stored on the imaginary part of the first sample.
// Reference:
// Numerical Recipes in C, chapter 12.3
void rfft_core(float *data, int n, float *twiddle, int *bitrev, int direction)
{

    float complex *cdata = (float complex *)data;
    float complex *twd = (float complex *)twiddle;

    float complex even;
    float complex odd;

    if (direction == 1)
    {
        radix_2_dit_fft(data, n / 2, twiddle, bitrev, 2, 1); // the twiddle stride is 2 so we can reuse them when computing the real FFT

        even = (cdata[0] + conj(cdata[0])) / 2;
        odd = (cdata[0] - conj(cdata[0])) / 2;
        cdata[0] = even - I * odd;
        cdata[0] += I * even - odd; // stores FFT[N/2] on the imaginary part of FFT[0]
    }
    else // (direction == -1)
    {
        even = (creal(cdata[0]) + cimag(cdata[0])) / 2;
        odd = (creal(cdata[0]) - cimag(cdata[0])) / 2;
        cdata[0] = even + I * odd;
    }

    even = (cdata[n / 4] + conj(cdata[n / 4])) / 2;
    odd = (cdata[n / 4] - direction * conj(cdata[n / 4])) / 2;

    if (direction == 1)
        cdata[n / 4] = even - odd;
    else
        cdata[n / 4] = even + I * odd;

    for (int i = 1; i < n / 4; i++)
    {
        float complex even1 = (cdata[n / 2 - i] + conj(cdata[i])) / 2;
        float complex odd1 = (cdata[n / 2 - i] - conj(cdata[i])) / 2;

        even = (cdata[i] + conj(cdata[n / 2 - i])) / 2;
        odd = (cdata[i] - conj(cdata[n / 2 - i])) / 2;

        float complex w = (direction == 1) ? twd[i] : conj(twd[i]);
        float complex w1 = (direction == 1) ? twd[n / 2 - i] : conj(twd[n / 2 - i]);

        cdata[i] = even - direction * I * odd * w;
        cdata[n / 2 - i] = even1 - direction * I * odd1 * w1;
    }
    if (direction == -1)
    {
        radix_2_dit_fft(data, n / 2, twiddle, bitrev, 2, -1);
    }
}

void rfft(float *data, int n, float *twiddle, int *bitrev)
{
    rfft_core(data, n, twiddle, bitrev, 1);
}

void irfft(float *data, int n, float *twiddle, int *bitrev)
{

    rfft_core(data, n, twiddle, bitrev, -1);
}

