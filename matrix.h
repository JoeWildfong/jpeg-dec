#pragma once

#include <array>
#include "stream.h"
#include "types.h"

class Matrix8x8 {
    public:
        Matrix8x8(JPEGStream& stream, const std::streampos offset);
        Matrix8x8();
        Matrix8x8 operator* (Matrix8x8& mat);
        Matrix8x8 operator/ (Matrix8x8& mat);
        static Matrix8x8 zigzag(Matrix8x8& mat);
        void zigzag();
        static Matrix8x8 unzigzag(Matrix8x8& mat);
        void unzigzag();
        std::array<u8, 64> values;
};
