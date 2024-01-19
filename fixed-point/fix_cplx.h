#pragma once

// This is a fixed-point implementation of complex numbers.
// Fixed point numbers will be S8.23, i.e. 8 bits for the integer part and 23 bits for the fractional part.

typedef struct s_fix_complex
{
    int real;
    int imag;
} fix_cplx;

#define fix_mul(x, y) ((int)((long long)x) * ((long long)y) >> 23)
#define fix_frac_mul(x, y) ((int)((long long)x) * ((long long)y) >> 31)

#define fix_cplx_scale(x, s) (         \
    (x).real = fix_mul((x).real, (s)), \
    (x).imag = fix_mul((x).imag, (s)), \
    (x))

#define fix_cplx_add(r, x, y) (     \
    (r).real = (x).real + (y).real, \
    (r).imag = (x).imag + (y).imag, \
    (r))

#define fix_cplx_sub(r, x, y) (     \
    (r).real = (x).real - (y).real, \
    (r).imag = (x).imag - (y).imag, \
    (r))

#define fix_cplx_mul(r, x, y) (                                           \
    (r).real = fix_mul((x).real, (y).real) - fix_mul((x).imag, (y).imag), \
    (r).imag = fix_mul((x).real, (y).imag) + fix_mul((x).imag, (y).real), \
    (r))

#define fix_frac_cplx_mul(r, x, y) (                                                \
    (r).real = fix_frac_mul((x).real, (y).real) - fix_frac_mul((x).imag, (y).imag), \
    (r).imag = fix_frac_mul((x).real, (y).imag) + fix_frac_mul((x).imag, (y).real), \
    (r))

#define fix_cplx_conj(r, x) ( \
    (r).real = (x).real,      \
    (r).imag = -(x).imag,     \
    (r))
