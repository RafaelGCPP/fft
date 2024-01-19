#include "test_set.h"

void real_fft_test()
{
    int n = 16;                                                                                              // Change this value for different sizes of the arrays (N)
    float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0}; // interleaved real and imaginary parts
    float twiddle[n];
    int bitrev[n / 2];

    printf("-=-=-=-=-=-= Real FFT test - floating point =-=-=-=-=-=-\n");
    n = 16;

    // Precompute twiddle factors
    precompute_twiddle_factors_rfft(twiddle, n);
    precompute_bitrev_table_rfft(bitrev, n);

    rfft(data, n, twiddle, bitrev);
    printf("FFT result:\n");
    for (int i = 0; i < n / 2; i++)
    {
        printf("%.5f + %.5fi\n", data[2 * i], data[2 * i + 1]);
    }

    irfft(data, n, twiddle, bitrev);
    printf("IFFT result:\n");
    for (int i = 0; i < n / 2; i++)
    {
        printf("%.5f + %.5fi\n", data[2 * i], data[2 * i + 1]);
    }
}

void real_fft_test_fix()
{
    int n = 16, l2n = 4;                                                   // Change this value for different sizes of the arrays (N)
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, -8, -7, -6, -5, -4, -3, -2, -1}; // interleaved real and imaginary parts
    int twiddle[n];
    int bitrev[n / 2];

    for (int i = 0; i < n; i++)
    {
        data[i] = data[i] << 23;
    }

    printf("-=-=-=-=-=-= Real FFT test - fixed point =-=-=-=-=-=-\n");

    // Precompute twiddle factors
    precompute_twiddle_factors_rfft_fix(twiddle, l2n);
    precompute_bitrev_table_rfft_fix(bitrev, l2n);

    rfft_fix(data, l2n, twiddle, bitrev);
    printf("FFT result:\n");
    for (int i = 0; i < n / 2; i++)
    {
        printf("%.5f + %.5fi\n",
               (float)data[2 * i] / 0x800000,
               (float)data[2 * i + 1] / 0x800000);
    }

    irfft_fix(data, l2n, twiddle, bitrev);
    printf("IFFT result:\n");
    for (int i = 0; i < n / 2; i++)
    {
        printf("%.5f + %.5fi\n",
               (float)data[2 * i] / 0x800000,
               (float)data[2 * i + 1] / 0x800000);
    }
}
