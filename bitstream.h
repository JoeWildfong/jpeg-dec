#pragma once

#include <string>

class Bitstream {
  public:
    Bitstream(std::string& source);
    unsigned short readBits(int len);
    unsigned char readNibble();
    unsigned char readByte();
    unsigned short readWord();
    unsigned int length;
    bool eof;
    unsigned int remaining();
  private:
    void readIntoBuffer(int len);
    std::string m_source;
    unsigned int m_buf;
    unsigned short m_bufsize;
    unsigned int m_index;
};