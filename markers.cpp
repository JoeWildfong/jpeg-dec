#include "markers.h"

#include <unordered_map>

static const std::unordered_map<JPEGMarkerByte, std::string> markerByteToName {
    {JPEGMarkerByte::SOI,  "SOI" },
    {JPEGMarkerByte::EOI,  "EOI" },
    {JPEGMarkerByte::SOF0, "SOF0"},
    {JPEGMarkerByte::SOF2, "SOF2"},
    {JPEGMarkerByte::DHT,  "DHT" },
    {JPEGMarkerByte::RST0, "RST0"},
    {JPEGMarkerByte::RST1, "RST1"},
    {JPEGMarkerByte::RST2, "RST2"},
    {JPEGMarkerByte::RST3, "RST3"},
    {JPEGMarkerByte::RST4, "RST4"},
    {JPEGMarkerByte::RST5, "RST5"},
    {JPEGMarkerByte::RST6, "RST6"},
    {JPEGMarkerByte::RST7, "RST7"},
    {JPEGMarkerByte::SOS,  "SOS" },
    {JPEGMarkerByte::DQT,  "DQT" },
    {JPEGMarkerByte::DRI,  "DRI" },
    {JPEGMarkerByte::APP0, "APP0"},
    {JPEGMarkerByte::APP1, "APP1"},
    {JPEGMarkerByte::APP2, "APP2"},
    {JPEGMarkerByte::APP3, "APP3"},
    {JPEGMarkerByte::APP4, "APP4"},
    {JPEGMarkerByte::APP5, "APP5"},
    {JPEGMarkerByte::APP6, "APP6"},
    {JPEGMarkerByte::APP7, "APP7"},
    {JPEGMarkerByte::APP8, "APP8"},
    {JPEGMarkerByte::APP9, "APP9"},
    {JPEGMarkerByte::APPA, "APPA"},
    {JPEGMarkerByte::APPB, "APPB"},
    {JPEGMarkerByte::APPC, "APPC"},
    {JPEGMarkerByte::APPD, "APPD"},
    {JPEGMarkerByte::APPE, "APPE"},
    {JPEGMarkerByte::APPF, "APPF"},
    {JPEGMarkerByte::COM,  "COM" },
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
