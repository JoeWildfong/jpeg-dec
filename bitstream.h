// #pragma once

// #include "stream.h"

// class JPEGBitstream {
//     public:
//         unsigned short getBits(int len);
//         unsigned char getNibble();
//         unsigned char getByte();
//         unsigned short getWord();

//         JPEGBitstream(std::ifstream& stream) : m_source(stream) {};

//         ~JPEGBitstream() = default;

//         JPEGBitstream(const JPEGBitstream& copy) = default;
//         JPEGBitstream(JPEGBitstream&& move) = default;
        
//         JPEGBitstream& operator=(const JPEGBitstream& copy) = default;
//         JPEGBitstream& operator=(JPEGBitstream&& move) = default;
//     private:
//         std::ifstream& m_source;
//         void readIntoBuffer(int len);
//         unsigned int m_buf = 0;
//         unsigned short m_bufsize = 0;
//         unsigned int m_index = 0;
// };