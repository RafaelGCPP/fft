#include "fft.h"
#include "rfft.h"
#include "fft_init.h"
#include <stdio.h>

int main()
{
    int n = 16;                                                                                              // Change this value for different sizes of the arrays (N)
    float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0}; // interleaved real and imaginary parts
    float twiddle[n];
    int bitrev[n];

    printf("-=-=-=-=-=-= Complex FFT test - floating point =-=-=-=-=-=-\n");
    // Precompute twiddle factors
    n = 8;
    precompute_twiddle_factors(twiddle, n);
    precompute_bitrev_table(bitrev, n);

    // Perform FFT
    fft(data, n, twiddle, bitrev);

    // Display the FFT results
    printf("FFT result:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.5f + %.5fi\n", data[2 * i], data[2 * i + 1]);
    }

    // Perform IFFT
    ifft(data, n, twiddle, bitrev);

    // Display the IFFT results
    printf("IFFT result:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.5f + %.5fi\n", data[2 * i], data[2 * i + 1]);
    }

    printf("-=-=-=-=-=-= Real FFT test - floating point =-=-=-=-=-=-\n");
    n = 16;

    // Precompute twiddle factors
    precompute_twiddle_factors(twiddle, n);

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

    return 0;
}
