#include "cordic.h"
#include "fix_fft_init.h"

void precompute_twiddle_factors_fix(int *twiddle, int l2n)
{
    // defining twiddle factor for 0 rad, although it will not be needed
    twiddle[0] = 0x7fffffff; // cos(0)==1 in Q31
    twiddle[1] = 0x00000000; // sin(0)==0 in Q31

    int angle = (int)(0x80000000l >> l2n); // pi/n in Q31
    int theta = angle;
    for (int j = 1; j < (n >> 2); j++)
    {
        // twiddle factors are calculated in the interval [0,-pi)
        // cordic expects angles scaled so that pi/2 = 1.0
        // which means we need to scale by 2/pi
        // thus -2*pi*j/n * 2/pi = -4*j/n
        // as cordic implements only first quadrant, we need to
        // reduce the angle to [0,pi/2) and change signs accordingly
        // also we can use the first octant symmetry to evaluate 4 values at a time

        int c, s;
        cordic_sin_cos(theta, &s, &c);
        twiddle[2 * j] = c;
        twiddle[2 * j + 1] = -s;
        theta += angle;
    }
}