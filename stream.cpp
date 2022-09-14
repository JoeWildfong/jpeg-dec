#include "stream.h"

const std::pair<u4, u4> JPEGStream::get4Pair() {
    const u8 read = this->get8();
    return {(read >> 4) & 0x0F, read & 0x0F};
}

const u8 JPEGStream::get8() {
    m_byteCounter++;
    const u8 read = m_stream.get();
    if (read == 0xFF && m_stream.peek() == 0x00) {
        // skip byte-stuffing 00 byte
        m_byteCounter++;
        m_stream.get();
    }
    return read;
}

const u16 JPEGStream::get16() {
    return (this->get8() << 8) + this->get8();
}

const u32 JPEGStream::get32() {
    return (this->get8() << 24) + (this->get8() << 16) + (this->get8() << 8) + this->get8();
}

const JPEGMarker JPEGStream::getMarker() {
    const u8 ffbyte = m_stream.get();
    if (ffbyte != 0xFF) {
        throw NotAMarkerException(m_stream.tellg());
    }
    const u8 markerByte = m_stream.get();
    return std::move(JPEGMarker{markerByte});
}

const std::string_view JPEGStream::getHex() {
    char byteHex[2];
    sprintf(byteHex, "%x", m_stream.get());
    return std::string_view(byteHex);
}

const bool JPEGStream::atMarker() {
    bool out;
    const std::streampos startPos = m_stream.tellg();
    const u8 ffbyte = m_stream.get();
    if (ffbyte != 0xFF) {
        out = false;
    } else {
        const u8 markerByte = m_stream.get();
        out = JPEGMarker::isRecognizedMarkerByte(markerByte);
    }
    m_stream.seekg(startPos);
    return out;
}

void JPEGStream::skipToMarker() {
    for (u8 read; m_stream >> read;) {
        if (read == 0xFF && JPEGMarker::isRecognizedMarkerByte(m_stream.peek())) {
            // place back FF
            m_stream.unget();
            return;
        }
    }
}

unsigned int JPEGStream::getByteCounter() {
    return m_byteCounter;
}

void JPEGStream::resetByteCounter() {
    m_byteCounter = 0;
}

void JPEGStream::clear() {
    m_stream.clear();
}

bool JPEGStream::eof() {
    return m_stream.eof();
}

JPEGStream& JPEGStream::seekg(std::streampos pos) {
    m_stream.seekg(pos);
    return *this;
}

std::streampos JPEGStream::tellg() {
    return m_stream.tellg();
}

void JPEGStream::close() {
    m_stream.close();
}

NotAMarkerException::NotAMarkerException(const std::streampos pos) : pos(pos) {}
