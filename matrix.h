#pragma once

#include <string>
#include <array>
#include "bitstream.h"

class Matrix8x8 {
  public:
    Matrix8x8(Bitstream* stream);
    Matrix8x8(std::string& raw);
    Matrix8x8();
    Matrix8x8 operator* (Matrix8x8& mat);
    Matrix8x8 operator/ (Matrix8x8& mat);
    Matrix8x8 zigzag(Matrix8x8& mat);
    void zigzag(Matrix8x8* mat);
    Matrix8x8 unzigzag(Matrix8x8& mat);
    void unzigzag(Matrix8x8* mat);
    std::array<unsigned char, 64> values;
};