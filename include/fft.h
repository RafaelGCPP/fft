#pragma once

void precompute_twiddle_factors(float *twiddle, int n);
void precompute_twiddle_factors_sqrt(float *twiddle, int n);
void precompute_bitrev_table(int *bitrev, int n);

void fft(float *data, int n, float *twiddle, int *bitrev);
void ifft(float *data, int n, float *twiddle, int *bitrev);
