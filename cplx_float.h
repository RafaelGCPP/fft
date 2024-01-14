#pragma once

// Although most compilers implement complex numbers as a struct with two floats,
// we can't rely on this on embedded systems.  So we define our own complex type.

// Also, it will make it easier to port to fixed-point if we ever need to.

typedef struct s_complex_float
{
    float real;
    float imag;
} cplx;

#define cplx_scale(x, s) ((x).real *= (s), (x).imag *= (s), (x))
#define cplx_add(r, x, y) ((r).real = (x).real + (y).real, (r).imag = (x).imag + (y).imag, (r))
#define cplx_sub(r, x, y) ((r).real = (x).real - (y).real, (r).imag = (x).imag - (y).imag, (r))
#define cplx_mul(r, x, y) ((r).real = (x).real * (y).real - (x).imag * (y).imag, (r).imag = (x).real * (y).imag + (x).imag * (y).real, (r))
#define cplx_conj(r,x) ((r).real = (x).real, (r).imag = -(x).imag, (r))