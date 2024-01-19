#pragma once

void rfft(float *data, int n, float *twiddle, int *bitrev);
void irfft(float *data, int n, float *twiddle, int *bitrev);

void precompute_twiddle_factors_rfft(float *twiddle, int n);
void precompute_bitrev_table_rfft(int *bitrev, int n);
