#include <math.h>
#include <fft.h>

void precompute_twiddle_factors(float *twiddle, int n)
{
    for (int j = 0; j < n / 2; j++)
    {
        twiddle[2 * j] = cosf(-2.0 * M_PI * j / n);
        twiddle[2 * j + 1] = sinf(-2.0 * M_PI * j / n);
    }
}

void precompute_twiddle_factors_sqrt(float *twiddle, int n)
{
    twiddle[0] = 1.0; // 0 rad - i=0
    twiddle[1] = 0.0;
    twiddle[n / 2] = 0.0; // -pi/2 rad - i=n/4
    twiddle[n / 2 + 1] = -1.0;

    for (int m = n / 4; m > 1; m >>= 1)
    {
        int j = m / 2;
        twiddle[2 * j] = sqrtf((1.0 + twiddle[2 * (2 * j)]) / 2.0);
        twiddle[2 * j + 1] = -sqrtf((1.0 - twiddle[2 * (2 * j)]) / 2.0);

        for (int i = m + j; i < n / 2; i += j)
        {
            twiddle[2 * i] = twiddle[2 * (i - j)] * twiddle[m] - twiddle[2 * (i - j) + 1] * twiddle[m + 1];
            twiddle[2 * i + 1] = twiddle[2 * (i - j)] * twiddle[m + 1] + twiddle[2 * (i - j) + 1] * twiddle[m];
        }
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
