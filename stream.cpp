#include "stream.h"

const JPEGMarker& JPEGStream::getMarker() {
    const unsigned char ffbyte = this->get();
    if (ffbyte != 0xFF) {
        throw NotAMarkerException(this->tellg());
    }
    const unsigned char markerByte = this->get();
    return JPEGMarker{markerByte};
}

const std::string& JPEGStream::getHex() {
    char byteHex[2];
    sprintf(byteHex, "%x", this->get());
    return std::string(byteHex);
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
    while (!this->atMarker() && !this->eof()) {
        this->get();
    }
}

NotAMarkerException::NotAMarkerException(const std::streampos pos) : pos(pos) {}