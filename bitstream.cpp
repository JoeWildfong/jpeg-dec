#include "bitstream.h"

u32 JPEGBitstream::getBits(unsigned int len) {
    u32 output;
    readIntoBuffer(len);

    // Shift the requested number of bytes down to the other end
    output = ((m_buf >> (32 - len)) & ((1 << len) - 1));

    m_bufsize -= len;
    m_buf <<= len;
    return output;
}

bool JPEGBitstream::eof() {
    return m_bufsize == 0 && m_source.eof();
}

void JPEGBitstream::readIntoBuffer(unsigned int len) {
    while (len > m_bufsize) {
        // Read a byte in, shift it up to join the queue
        u8 readByte = 0;
        if (!m_source.eof()) {
            readByte = m_source.get8();
        }
        m_buf = m_buf | (readByte << (24 - m_bufsize));
        m_bufsize += 8;
    }
}
