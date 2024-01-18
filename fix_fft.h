#pragma once

void fft_fix(int *data, int l2n, int *twiddle, int *bitrev);
void ifft_fix(int *data, int l2n, int *twiddle, int *bitrev);
