#pragma once

#include <fft.h>
#include <rfft.h>
#include <stdio.h>
#include <fix_fft.h>
#include <math.h>
#include <cordic.h>

void complex_fft_test();
void complex_fft_test_fix();

void real_fft_test();

void cordic_test();
void twiddle_test();
void fix_twiddle_test();
