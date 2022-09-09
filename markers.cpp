#include "markers.h"

#include <unordered_map>

using namespace std::literals;

static const std::unordered_map<JPEGMarkerByte, std::string_view> markerByteToName {
    {JPEGMarkerByte::SOI,  "SOI"sv },
    {JPEGMarkerByte::EOI,  "EOI"sv },
    {JPEGMarkerByte::SOF0, "SOF0"sv},
    {JPEGMarkerByte::SOF2, "SOF2"sv},
    {JPEGMarkerByte::DHT,  "DHT"sv },
    {JPEGMarkerByte::RST0, "RST0"sv},
    {JPEGMarkerByte::RST1, "RST1"sv},
    {JPEGMarkerByte::RST2, "RST2"sv},
    {JPEGMarkerByte::RST3, "RST3"sv},
    {JPEGMarkerByte::RST4, "RST4"sv},
    {JPEGMarkerByte::RST5, "RST5"sv},
    {JPEGMarkerByte::RST6, "RST6"sv},
    {JPEGMarkerByte::RST7, "RST7"sv},
    {JPEGMarkerByte::SOS,  "SOS"sv },
    {JPEGMarkerByte::DQT,  "DQT"sv },
    {JPEGMarkerByte::DRI,  "DRI"sv },
    {JPEGMarkerByte::APP0, "APP0"sv},
    {JPEGMarkerByte::APP1, "APP1"sv},
    {JPEGMarkerByte::APP2, "APP2"sv},
    {JPEGMarkerByte::APP3, "APP3"sv},
    {JPEGMarkerByte::APP4, "APP4"sv},
    {JPEGMarkerByte::APP5, "APP5"sv},
    {JPEGMarkerByte::APP6, "APP6"sv},
    {JPEGMarkerByte::APP7, "APP7"sv},
    {JPEGMarkerByte::APP8, "APP8"sv},
    {JPEGMarkerByte::APP9, "APP9"sv},
    {JPEGMarkerByte::APPA, "APPA"sv},
    {JPEGMarkerByte::APPB, "APPB"sv},
    {JPEGMarkerByte::APPC, "APPC"sv},
    {JPEGMarkerByte::APPD, "APPD"sv},
    {JPEGMarkerByte::APPE, "APPE"sv},
    {JPEGMarkerByte::APPF, "APPF"sv},
    {JPEGMarkerByte::COM,  "COM"sv },
};

JPEGMarker::JPEGMarker(const u8 byte) :
    JPEGMarker(static_cast<JPEGMarkerByte>(byte)) {}

JPEGMarker::JPEGMarker(const JPEGMarkerByte byte) : m_byte(byte) {
    if (markerByteToName.count(byte) == 0) {
        throw new UnknownMarkerException(byte);
    }
}

const JPEGMarkerByte JPEGMarker::getMarkerByte() const {
    return m_byte;
}

const std::string_view JPEGMarker::getName() const {
    return markerByteToName.at(m_byte);
}

const bool JPEGMarker::isRecognizedMarkerByte(const u8 byte) {
    return isRecognizedMarkerByte(static_cast<JPEGMarkerByte>(byte));
}

const bool JPEGMarker::isRecognizedMarkerByte(const JPEGMarkerByte byte) {
    const JPEGMarkerByte markerByte = byte;
    return markerByteToName.count(markerByte) > 0;
}

bool JPEGMarker::operator<(const JPEGMarker& other) const {
    return this->getMarkerByte() < other.getMarkerByte();
}

bool JPEGMarker::operator==(const JPEGMarker& other) const {
    return this->getMarkerByte() == other.getMarkerByte();
}

bool JPEGMarker::operator>(const JPEGMarker& other) const {
    return this->getMarkerByte() > other.getMarkerByte();
}


UnknownMarkerException::UnknownMarkerException(const JPEGMarkerByte marker) :
    marker(marker) {};
