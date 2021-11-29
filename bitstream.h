#pragma once

#include "stream.h"

class JPEGBitstream : public JPEGStream {
    public:
        unsigned short getBits(int len);
        unsigned char getNibble();
        unsigned char getByte();
        unsigned char get();
        unsigned short getWord();

        using JPEGStream::JPEGStream;
        JPEGBitstream(std::ifstream&& stream) : JPEGStream(std::move(stream)) {};

        ~JPEGBitstream() = default;

        JPEGBitstream(const JPEGBitstream& copy) = default;
        JPEGBitstream(JPEGBitstream&& move) = default;
        
        JPEGBitstream& operator=(const JPEGBitstream& copy) = default;
        JPEGBitstream& operator=(JPEGBitstream&& move) = default;
    private:
        void readIntoBuffer(int len);
        unsigned int m_buf = 0;
        unsigned short m_bufsize = 0;
        unsigned int m_index = 0;
};