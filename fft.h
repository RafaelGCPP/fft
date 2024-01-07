#pragma once
#include <stdbool.h>

void precompute_twiddle_factors(float *twiddle, int n);
void fft(float *data, float *twiddle, int n, bool inverse);