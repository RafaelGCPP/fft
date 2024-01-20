
cmake_minimum_required(VERSION 3.12)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(testset)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
set(CMAKE_C_STANDARD 99)

# Add your source files here
set(SOURCES
    main.c
    complex_fft_tests.c
    real_fft_tests.c
    utils_tests.c
)


# Add executable
add_executable(fft ${SOURCES})

# Add reference to libmath
target_link_libraries(fft PRIVATE float-fft fixed-fft)
