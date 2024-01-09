#pragma once

void fft(float *data, int n, float *twiddle, int *bitrev);
void ifft(float *data, int n, float *twiddle, int *bitrev);
