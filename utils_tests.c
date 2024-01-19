#include "test_set.h"

void cordic_test()
{
    int n = 16;
    int t, s, c;
    printf("-=-=-=-=-=-= Cordic test =-=-=-=-=-=-\n");
    for (int i = -n; i <= n; i++)
    {
        t = i * (0x80000000l >> 4); // 1/16
        cordic_sin_cos(t, &s, &c);
        printf("sin(%f) = %f, cos(%d) = %f\n", (double)t / 0x80000000l, (double)s / 0x80000000l, t, (double)c / 0x80000000l);
    }
}

void twiddle_test()
{
    int n = 64;
    float twiddle[n];
    printf("-=-=-=-=-=-= Twiddle test =-=-=-=-=-=-\n");
    precompute_twiddle_factors(twiddle, n);
    for (int i = 0; i < n / 2; i++)
    {
        printf("cos(%d) = %f, sin(%d) = %f\n", i, twiddle[2 * i], i, twiddle[2 * i + 1]);
    }
}

void fix_twiddle_test()
{
    int n = 128, l2n = 7;
    int twiddle[n];
    float twiddle_f[n];
    printf("-=-=-=-=-=-= Fix twiddle test =-=-=-=-=-=-\n");
    precompute_twiddle_factors_fix(twiddle, l2n);
    for (int i = 0; i < n / 2; i++)
    {
        printf("cos(%d) = %f, sin(%d) = %f\n",
               i, (double)twiddle[2 * i] / 0x80000000l,
               i, (double)twiddle[2 * i + 1] / 0x80000000l);
    }
    printf("-=-=-=-=-=-= Fix twiddle error test =-=-=-=-=-=-\n");

    precompute_twiddle_factors(twiddle_f, n);
    for (int i = 0; i < n / 2; i++)
    {
        printf("cos(%d) = %f, sin(%d) = %f\n",
               i, (double)twiddle[2 * i] / 0x80000000l - twiddle_f[2 * i],
               i, (double)twiddle[2 * i + 1] / 0x80000000l - twiddle_f[2 * i + 1]);
    }
}
