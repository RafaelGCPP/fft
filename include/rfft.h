#pragma once

void rfft(float *data, int n, float *twiddle, int *bitrev);
void irfft(float *data, int n, float *twiddle, int *bitrev);

void precompute_twiddle_factors_rfft_fix(int *twiddle, int n);
void precompute_bitrev_table_rfft_fix(int *bitrev, int n);
