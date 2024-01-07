#include "fft_core.h"
#include <math.h>
#include <complex.h>

// This code assumes that n is a power of 2 and implements
// a radix-2 DIT FFT algorithm.
// data - input as real and imaginary interleaved.
// n - number of complex samples in the input data.
// twiddle - precomputed twiddle factors.
// ts - twiddle stride, used when computing the real FFT.
void radix_2_dit_fft(float *data, int n, float *twiddle, int ts)
{
    float complex *cdata = (float complex *)data;
    float complex *twd = (float complex *)twiddle;

    // Bit-reverse the input data

    for (int i = 1, j = 0; i < n - 1; i++)
    {
        int k = n >> 1;
        while (j >= k)
        {
            j -= k;
            k >>= 1;
        }
        j += k;
        if (i < j)
        {
            float complex tmp = cdata[i];
            cdata[i] = cdata[j];
            cdata[j] = tmp;
        }
    }

    // Perform the butterfly operations

    for (int k = 0, stride = 1, tw_index = n >> 1; stride < n; k++, stride <<= 1, tw_index >>= 1)
    {
        int jmax = n - stride;
        for (int j = 0; j < jmax; j += (stride << 1))
        {
            for (int i = 0; i < stride; i++)
            {
                complex float a, b, w;
                int index = j + i;
                w = twd[i * tw_index * ts];
                a = cdata[index];
                b = cdata[index + stride];
                b = b * w;
                cdata[index] = a + b;
                cdata[index + stride] = a - b;
            }
        }
    }
}