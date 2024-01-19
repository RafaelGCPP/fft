#include <stdio.h>
#include <math.h>
#include "fix_fft_core.h"
#include "fix_cplx.h"

// This code assumes that n is a power of 2 and implements
// the real FFT algorithm. It is based on the fact that
// the FFT of a real signal is conjugate symmetric. Then you can
// consider the real input as interleaved complex data and perform
// a complex FFT. The even and odd parts are then computed.
// data - input as real data.
// n - number of real samples in the input data.
// twiddle - precomputed twiddle factors
// the result is stored in the input array, as half of the spectrum
// the N/2 sample is stored on the imaginary part of the first sample.
// Reference:
// Numerical Recipes in C, chapter 12.3
// this code uses no internal complex data types
void rfft_core_fix(int *data, int l2n, int *twiddle, int *bitrev, int direction)
{
    int n = 1 << l2n;
    fix_cplx *cdata = (fix_cplx *)data;
    fix_cplx *twd = (fix_cplx *)twiddle;

    fix_cplx even;
    fix_cplx odd;

    if (direction == 1)
    {
        radix_2_dit_fft_fix(data, l2n - 1, twiddle, bitrev, 2, 1); // the twiddle stride is 2 so we can reuse them when computing the real FFT

        // even = (cdata[0] + conj(cdata[0])) / 2;
        // odd = (cdata[0] - conj(cdata[0])) / 2;

        fix_cplx tmp;
        fix_cplx_conj(tmp, cdata[0]); // tmp = conj(cdata[0])
        fix_cplx_add(even, cdata[0], tmp);
        fix_cplx_sub(odd, cdata[0], tmp);

        even.real >>= 1;
        even.imag >>= 1;
        odd.real >>= 1;
        odd.imag >>= 1;

        // tmp = I * odd
        tmp.real = -odd.imag;
        tmp.imag = odd.real;

        // cdata[0] = even - I * odd;
        fix_cplx_sub(cdata[0], even, tmp);

        // tmp= I * even
        tmp.real = -even.imag;
        tmp.imag = even.real;

        // cdata[0] += I * even - odd; // stores FFT[N/2] on the imaginary part of FFT[0]
        fix_cplx_add(cdata[0], cdata[0], tmp);
        fix_cplx_sub(cdata[0], cdata[0], odd);
    }
    else // (direction == -1)
    {
        // even = (creal(cdata[0]) + cimag(cdata[0])) / 2;
        even.real = (cdata[0].real + cdata[0].imag) / 2;
        even.imag = 0;

        // odd = (creal(cdata[0]) - cimag(cdata[0])) / 2;
        odd.real = (cdata[0].real - cdata[0].imag) / 2;
        odd.imag = 0;

        // cdata[0] = even + I * odd; // since the input is real, the imaginary part of each is zero so
        cdata[0].real = even.real;
        cdata[0].imag = odd.real;
    }

    {
        fix_cplx tmp;
        fix_cplx_conj(tmp, cdata[n / 4]); // tmp = conj(cdata[n / 4])

        // even = (cdata[n / 4] + conj(cdata[n / 4])) / 2;
        fix_cplx_add(even, cdata[n / 4], tmp);
        even.real >>= 1;
        even.imag >>= 1;

        // odd = (cdata[n / 4] - direction * conj(cdata[n / 4])) / 2;
        if (direction == 1)
            fix_cplx_sub(odd, cdata[n / 4], tmp);
        else
            fix_cplx_add(odd, cdata[n / 4], tmp);

        odd.real >>= 1;
        odd.imag >>= 1;
    }

    if (direction == 1)
        // cdata[n / 4] = even - odd;
        fix_cplx_sub(cdata[n / 4], even, odd);
    else
    {
        // cdata[n / 4] = even + I * odd;
        fix_cplx tmp; // tmp = I * odd
        tmp.real = -odd.imag;
        tmp.imag = odd.real;
        fix_cplx_add(cdata[n / 4], even, tmp);
    }

    for (int i = 1; i < n / 4; i++)
    {
        fix_cplx even1, odd1, tmp1, tmp, w, w1;
        fix_cplx_conj(tmp, cdata[i]); // tmp = conj(cdata[i])

        // even1 = (cdata[n / 2 - i] + conj(cdata[i])) / 2;
        // odd1 = (cdata[n / 2 - i] - conj(cdata[i])) / 2;
        fix_cplx_add(even1, cdata[n / 2 - i], tmp);
        even1.real >>= 1;
        even1.imag >>= 1;

        fix_cplx_sub(odd1, cdata[n / 2 - i], tmp);
        odd1.real >>= 1;
        odd1.imag >>= 1;

        fix_cplx_conj(tmp, cdata[n / 2 - i]); // tmp = conj(cdata[n / 2 - i])

        // even = (cdata[i] + conj(cdata[n / 2 - i])) / 2;
        // odd = (cdata[i] - conj(cdata[n / 2 - i])) / 2;
        fix_cplx_add(even, cdata[i], tmp);
        even.real >>= 1;
        even.imag >>= 1;

        fix_cplx_sub(odd, cdata[i], tmp);
        odd.real >>= 1;
        odd.imag >>= 1;

        if (direction == 1)
        {
            // float complex w = twd[i];
            // float complex w1 = twd[n / 2 - i];
            w = twd[i];
            w1 = twd[n / 2 - i];

            // tmp1 = odd * w
            fix_cplx_mul(tmp1, odd, w, 31);
            // tmp = I * tmp1
            tmp.real = -tmp1.imag;
            tmp.imag = tmp1.real;

            // cdata[i] = even - I * odd * w;
            fix_cplx_sub(cdata[i], even, tmp);

            // tmp1 = odd1 * w1
            fix_cplx_mul(tmp1, odd1, w1, 31);
            // tmp = I * tmp1
            tmp.real = -tmp1.imag;
            tmp.imag = tmp1.real;

            // cdata[n / 2 - i] = even1 - I * odd1 * w1;
            fix_cplx_sub(cdata[n / 2 - i], even1, tmp);
        }
        else
        {
            // float complex w = conj(twd[i]);
            // float complex w1 = conj(twd[n / 2 - i]);
            fix_cplx_conj(w, twd[i]);
            fix_cplx_conj(w1, twd[n / 2 - i]);

            // tmp1 = odd * w
            fix_cplx_mul(tmp1, odd, w, 31);
            // tmp = I * tmp1
            tmp.real = -tmp1.imag;
            tmp.imag = tmp1.real;

            // cdata[i] = even + I * odd * w;
            fix_cplx_add(cdata[i], even, tmp);

            // tmp1 = odd1 * w1
            fix_cplx_mul(tmp1, odd1, w1, 31);
            // tmp = I * tmp1
            tmp.real = -tmp1.imag;
            tmp.imag = tmp1.real;

            // cdata[n / 2 - i] = even1 + I * odd1 * w1;
            fix_cplx_add(cdata[n / 2 - i], even1, tmp);
        }
    }
    if (direction == -1)
    {
        radix_2_dit_fft_fix(data, l2n - 1, twiddle, bitrev, 2, -1);
    }
}

void rfft_fix(int *data, int l2n, int *twiddle, int *bitrev)
{
    rfft_core_fix(data, l2n, twiddle, bitrev, 1);
}

void irfft_fix(int *data, int l2n, int *twiddle, int *bitrev)
{

    rfft_core_fix(data, l2n, twiddle, bitrev, -1);
}
