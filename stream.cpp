#include "stream.h"

const std::pair<u4, u4> JPEGStream::get4Pair() {
    const u8 read = this->get();
    return {(read >> 4) & 0x0F, read & 0x0F};
}

const u8 JPEGStream::get8() {
    return this->get();
}

const u16 JPEGStream::get16() {
    return (this->get() << 8) + this->get();
}

const u32 JPEGStream::get32() {
    return (this->get() << 24) + (this->get() << 16) + (this->get() << 8) + this->get();
}

const JPEGMarker JPEGStream::getMarker() {
    const u8 ffbyte = this->get();
    if (ffbyte != 0xFF) {
        throw NotAMarkerException(this->tellg());
    }
    const u8 markerByte = this->get();
    return std::move(JPEGMarker{markerByte});
}

const std::string_view JPEGStream::getHex() {
    char byteHex[2];
    sprintf(byteHex, "%x", this->get());
    return std::string_view(byteHex);
}

const bool JPEGStream::atMarker() {
    bool out;
    const std::streampos startPos = this->tellg();
    const u8 ffbyte = this->get();
    if (ffbyte != 0xFF) {
        out = false;
    } else {
        const u8 markerByte = this->get();
        out = JPEGMarker::isRecognizedMarkerByte(markerByte);
    }
    this->seekg(startPos);
    return out;
}

void JPEGStream::skipToMarker() {
    for (u8 read; *this >> read;) {
        if (read == 0xFF && JPEGMarker::isRecognizedMarkerByte(this->peek())) {
            // place back FF
            this->unget();
            return;
        }
    }
}

NotAMarkerException::NotAMarkerException(const std::streampos pos) : pos(pos) {}
