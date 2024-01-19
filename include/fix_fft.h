#pragma once

void fft_fix(int *data, int l2n, int *twiddle, int *bitrev);
void ifft_fix(int *data, int l2n, int *twiddle, int *bitrev);

void precompute_twiddle_factors_fix(int *twiddle, int n);
void precompute_bitrev_table_fix(int *bitrev, int n);
