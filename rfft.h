#pragma once

void rfft(float *data, int n, float *twiddle, int *bitrev);
void irfft(float *data, int n, float *twiddle, int *bitrev);
