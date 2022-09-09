#include "matrix.h"

static constexpr u8 zigzagMap[] {
    0,  1,  5,  6,  14, 15, 27, 28,
    2,  4,  7,  13, 16, 26, 29, 42,
    3,  8,  12, 17, 25, 30, 41, 43,
    9,  11, 18, 24, 31, 40, 44, 53,
    10, 19, 23, 32, 39, 45, 52, 54,
    20, 22, 33, 38, 46, 51, 55, 60,
    21, 34, 37, 47, 50, 56, 59, 61,
    35, 36, 48, 49, 57, 58, 62, 63
};

Matrix8x8::Matrix8x8() {}

Matrix8x8::Matrix8x8(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    for (int i = 0; i < 64; i++) {
        u8 next = stream.get8();
        if (stream.eof()) {
            return;
        }
        values[i] = next;
    }
}

Matrix8x8 Matrix8x8::operator*(Matrix8x8& mat) {
    Matrix8x8 out;
    for (int i = 0; i < 64; i++) {
        out.values[i] = values[i] * mat.values[i];
    }
    return out;
}

Matrix8x8 Matrix8x8::zigzag(Matrix8x8& mat) {
    Matrix8x8 out;
    for (int i = 0; i < 64; i++) {
        out.values[i] = mat.values[zigzagMap[i]];
    }
    return out;
}

void Matrix8x8::zigzag() {
    u8 unmodified[64];
    std::copy(this->values.begin(), this->values.end(), unmodified);
    for (int i = 0; i < 64; i++) {
        this->values[i] = unmodified[zigzagMap[i]];
    }
}

Matrix8x8 Matrix8x8::unzigzag(Matrix8x8& mat) {
    Matrix8x8 out;
    for (int i = 0; i < 64; i++) {
        out.values[zigzagMap[i]] = mat.values[i];
    }
    return out;
}

void Matrix8x8::unzigzag() {
    u8 unmodified[64];
    std::copy(this->values.begin(), this->values.end(), unmodified);
    for (int i = 0; i < 64; i++) {
        this->values[zigzagMap[i]] = unmodified[i];
    }
}
