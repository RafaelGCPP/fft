# Simple FFT for embedded use

This code implements a simple radix-2 decimation-in-time (DIT) in-place Fast Fourier Transform (FFT) algorithm for both real and complex valued sequences. It is specifically designed for embedded systems, utilizing floating and fixed-point arithmetic and precomputed twiddle factors to optimize performance.

Compared to [KissFFT](https://github.com/mborgerding/kissfft), this code offers a smaller memory footprint by utilizing a single buffer for both input and output (in-place transformation). It also avoids dynamic memory allocation, which can be problematic in small microcontrollers. However, it should be noted that KissFFT supports arbitrary length FFTs through the use of mixed-radix transforms.

Compared do CMSIS-DSP, it is 10000x slower. Really. 

## Features:

- Supports real and complex valued sequences
- Optimized for embedded systems
- Utilizes floating and fixed-point arithmetic
- Precomputed twiddle factors for improved performance
- In-place computation for smaller memory footprint

## Limitations:

- Not highly optimized, intended for educational purposes
- Only supports power-of-2 length FFTs
- No input checking or array boundary validation

## Usage:

This code was primarily developed for use with the Raspberry Pi Pico board, which lacks FPU and MAC instructions. For Cortex-M4 or M7 processors, such as STM32x4 or STM32x7, it is recommended to use the CMSIS-DSP library, which can take advantage of FPU and fixed-point DSP instructions.

The test code can be built using CMake and gcc or clang in Linux. Follow these steps:

1. Run `cmake -B build -D BUILD_TESTSET=1` to generate the makefiles.
2. Run `cmake --build build` to build the code.
3. Run `build/testset/fft` to run the test suite.

Please refer to the test files for usage examples. Note that no input checking or array boundary validation is performed in the functions.

## Potential Applications:

- "Overlap-save" or "Overlap-add" large FIR processing for efficient computation on IR simulators
- Morse code detection and decoding


