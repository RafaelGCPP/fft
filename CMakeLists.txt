
cmake_minimum_required(VERSION 3.12)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(fft)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
set(CMAKE_C_STANDARD 99)

# Add your source files here
set(SOURCES
    main.c
)

# Add include directory to the include path
include_directories(include)

# Add subdirectories
add_subdirectory(floating-point)
add_subdirectory(fixed-point)

# Add executable
add_executable(fft ${SOURCES})

# Add reference to libmath
target_link_libraries(fft PRIVATE m float-fft fixed-fft)
