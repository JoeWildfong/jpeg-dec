#include "matrix.h"

constexpr unsigned char zigzagMap[] {
  0,  1,  5,  6,  14, 15, 27, 28,
  2,  4,  7,  13, 16, 26, 29, 42,
  3,  8,  12, 17, 25, 30, 41, 43,
  9,  11, 18, 24, 31, 40, 44, 53,
  10, 19, 23, 32, 39, 45, 52, 54,
  20, 22, 33, 38, 46, 51, 55, 60,
  21, 34, 37, 47, 50, 56, 59, 61,
  35, 36, 48, 49, 57, 58, 62, 63
};

Matrix8x8::Matrix8x8() {
  values.empty();
}

Matrix8x8::Matrix8x8(Bitstream* stream) {
  values.empty();
  for (int i = 0; i < 64; i++) {
    unsigned char next = stream->readByte();
    if (stream->eof) {
      return;
    }
    values[i] = next;
  }
}

Matrix8x8::Matrix8x8(std::string& raw) {
  values.empty();
  for (int i = 0; i < 64; i++) {
    values[i] = raw[i];
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

void Matrix8x8::zigzag(Matrix8x8* mat) {
  unsigned char unmodified[64];
  std::copy(mat->values.begin(), mat->values.end(), unmodified);
  for (int i = 0; i < 64; i++) {
    mat->values[i] = unmodified[zigzagMap[i]];
  }
}

Matrix8x8 Matrix8x8::unzigzag(Matrix8x8& mat) {
  Matrix8x8 out;
  for (int i = 0; i < 64; i++) {
    out.values[zigzagMap[i]] = mat.values[i];
  }
  return out;
}

void Matrix8x8::unzigzag(Matrix8x8* mat) {
  unsigned char unmodified[64];
  std::copy(mat->values.begin(), mat->values.end(), unmodified);
  for (int i = 0; i < 64; i++) {
    mat->values[zigzagMap[i]] = unmodified[i];
  }
}