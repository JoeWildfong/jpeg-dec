#include "bitstream.h"

unsigned short JPEGBitstream::getBits(int len) {
    unsigned short output;
    readIntoBuffer(len);

    // Shift the requested number of bytes down to the other end
    output = ((m_buf >> (32 - len)) & ((1 << len) - 1));

    m_bufsize -= len;
    m_buf <<= len;
    return output;
}

unsigned char JPEGBitstream::getNibble() {
    return static_cast<unsigned char>(getBits(4));
}

unsigned char JPEGBitstream::getByte() {
    return static_cast<unsigned char>(getBits(8));
}

unsigned char JPEGBitstream::get() {
    return this->getByte();
}

unsigned short JPEGBitstream::getWord() {
    return getBits(16);
}

void JPEGBitstream::readIntoBuffer(int len) {
    while (len > m_bufsize) {
        // Read a byte in, shift it up to join the queue
        unsigned char readByte = 0;
        if (!this->eof()) {
            readByte = this->get();
        }
        m_buf = m_buf | (readByte << (24 - m_bufsize));
        m_bufsize += 8;
    }
}

