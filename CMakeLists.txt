cmake_minimum_required(VERSION 3.13)
project(jpeg-dec)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
    bitstream.cpp
    frame.cpp
    huffman.cpp
    main.cpp
    markers.cpp
    matrix.cpp
    quantize.cpp
    scan.cpp
    skeleton.cpp
    stream.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(jpeg-dec ${SRCS})