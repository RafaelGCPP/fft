#include <math.h>
#include "fft_init.h"

void precompute_twiddle_factors(float *twiddle, int n)
{
    // float complex *twd = (float complex *)twiddle;
    for (int j = 0; j < n / 2; j++)
    {
        twiddle[2 * j] = cosf(-2.0 * M_PI * j / n);
        twiddle[2 * j + 1] = sinf(-2.0 * M_PI * j / n);
    }
}

void precompute_bitrev_table(int *bitrev, int n)
{
    bitrev[0] = 0;
    for (int i = 1, j = 0; i < n; i++)
    {
        int k = n >> 1;
        while (j >= k)
        {
            j -= k;
            k >>= 1;
        }
        j += k;
        bitrev[i] = j;
    }
}