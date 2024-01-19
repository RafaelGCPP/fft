#pragma once

void rfft_fix(int *data, int l2n, int *twiddle, int *bitrev);
void irfft_fix(int *data, int l2n, int *twiddle, int *bitrev);

void precompute_twiddle_factors_rfft_fix(int *twiddle, int n);
void precompute_bitrev_table_rfft_fix(int *bitrev, int n);