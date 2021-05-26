#include "bitstream.h"

Bitstream::Bitstream(std::string& source) {
  m_source = source;
  m_bufsize = 0;
  m_buf = 0;
  m_index = 0;
  eof = false;
  length = source.size();
}

unsigned short Bitstream::readBits(int len) {
  unsigned short output;
  readIntoBuffer(len);

  // Shift the requested number of bytes down to the other end
  output = ((m_buf >> (32 - len)) & ((1 << len) - 1));

  m_bufsize -= len;
  m_buf <<= len;
  return output;
}

unsigned char Bitstream::readNibble() {
  return static_cast<unsigned char>(readBits(4));
}

unsigned char Bitstream::readByte() {
  return static_cast<unsigned char>(readBits(8));
}

unsigned short Bitstream::readWord() {
  return readBits(16);
}

unsigned int Bitstream::remaining() {
  return length - m_index;
}

void Bitstream::readIntoBuffer(int len) {
  while (len > m_bufsize) {
    // Read a byte in, shift it up to join the queue
    unsigned char readByte = 0;
    if (m_index < m_source.size()){
      readByte = m_source[m_index];
      m_index++;
    } else {
      eof = true;
    }
    m_buf = m_buf | (readByte << (24 - m_bufsize));
    m_bufsize += 8;
  }
}