# Simple FFT for embedded use

This code implements a rudimentary Fast Fourier Transform (FFT) algorithm for both real and complex valued sequences. It is specifically designed for embedded systems, utilizing floating-point arithmetic and precomputed twiddle factors to optimize performance.



### What this code is:

- A simple implementation of a radix-2 decimation-in-time FFT
- Using in-place calculations
- An implementation of the real-valued FFT
- Capable of floating and fixed-point operations

### What this code isn't 

- Highly optimized (It is more an educational project)

## Notes:

This code was intended for use with my Raspberry Pi Pico board, as it does not have FPU nor MAC instructions. For usage on a Cortex-M4 or M7 processor (such as STM32x4, or STM32x7), I strongly suggest using the CMSIS-DSP library, as it might take advantage of the FPU and fixed-point DSP instructions. 

This code was built for my own entertainment only, and the most likely usage will be for "overlap-and-store" large FIR processing needed for efficient computation on IR simulators. I also plan on using it for a Morse code detector and decoder.

For usage, check the tests files, but I tried to keep in line with the function signatures used in the Numerical Recipes books.