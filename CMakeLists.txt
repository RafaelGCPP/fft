
cmake_minimum_required(VERSION 3.12)
project(fft)


set(CMAKE_C_STANDARD 99)

# Add your source files here
set(SOURCES
    main.c
    fft.c
)



add_executable(fft ${SOURCES})

# Add reference to libmath
target_link_libraries(fft PRIVATE m)
