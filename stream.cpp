#include "stream.h"

const std::pair<nybble, nybble> JPEGStream::getNybblePair() {
    unsigned char read = this->get();
    return {(read >> 4) & 0x0F, read & 0x0F};
}

const byte JPEGStream::getByte() {
    return this->get();
}

const word JPEGStream::getWord() {
    return (this->get() << 8) + this->get();
}

const doubleword JPEGStream::getDoubleWord() {
    return (this->get() << 24) + (this->get() << 16) + (this->get() << 8) + this->get();
}

const JPEGMarker JPEGStream::getMarker() {
    const unsigned char ffbyte = this->get();
    if (ffbyte != 0xFF) {
        throw NotAMarkerException(this->tellg());
    }
    const unsigned char markerByte = this->get();
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
    const unsigned char ffbyte = this->get();
    if (ffbyte != 0xFF) {
        out = false;
    } else {
        const unsigned char markerByte = this->get();
        out = JPEGMarker::isRecognizedMarkerByte(markerByte);
    }
    this->seekg(startPos);
    return out;
}

void JPEGStream::skipToMarker() {
    for (unsigned char read; *this >> read;) {
        if (read == 0xFF && JPEGMarker::isRecognizedMarkerByte(this->peek())) {
            // place back FF
            this->unget();
            return;
        }
    }
}

NotAMarkerException::NotAMarkerException(const std::streampos pos) : pos(pos) {}