
cmake_minimum_required(VERSION 3.12)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(fft)



set(CMAKE_C_COMPILER clang)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -ffixed-point)
set(CMAKE_C_STANDARD 99)

# Add your source files here
set(SOURCES
    main.c
    fft.c
    fft_core.c
    fft_init.c
    rfft.c
)



add_executable(fft ${SOURCES})

# Add reference to libmath
target_link_libraries(fft PRIVATE m)
