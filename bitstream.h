#pragma once

#include "stream.h"
#include "types.h"

class JPEGBitstream {
    public:
        u32 getBits(unsigned int len);
        bool eof();

        JPEGBitstream(JPEGStream& stream) : m_source(stream) {};

        ~JPEGBitstream() = default;

        JPEGBitstream(const JPEGBitstream& copy) = default;
        JPEGBitstream(JPEGBitstream&& move) = default;
        
        JPEGBitstream& operator=(const JPEGBitstream& copy) = delete;
        JPEGBitstream& operator=(JPEGBitstream&& move) = delete;
    private:
        JPEGStream& m_source;
        void readIntoBuffer(unsigned int len);
        u32 m_buf = 0;
        u32 m_bufsize = 0;
        u32 m_index = 0;
};
