#include "fft.h"
#include <stdio.h>

int main() {
    int n = 8; // Change this value for different sizes of the arrays (N)
    float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}; // interleaved real and imaginary parts
    float twiddle[n];
    

    // Precompute twiddle factors
    precompute_twiddle_factors(twiddle, n);
   
    // Perform FFT
    fft(data, twiddle, n, false);

    // Display the FFT results
    printf("FFT result:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f + %.5fi\n", data[2*i], data[2*i+1]);
    }

    // Perform IFFT
    fft(data, twiddle, n, true);

    // Display the IFFT results
    printf("IFFT result:\n");
    for (int i = 0; i < n; i++) {
        printf("%.5f + %.5fi\n", data[2*i], data[2*i+1]);
    }


    return 0;
}