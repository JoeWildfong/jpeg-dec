#include "markers.h"
#include <map>

static const std::map<JPEGMarkerByte, std::string> markerByteToName {
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

JPEGMarker::JPEGMarker(unsigned char byte) :
    JPEGMarker(static_cast<JPEGMarkerByte>(byte)) {}

JPEGMarker::JPEGMarker(JPEGMarkerByte byte) 
    try:
        m_byte(byte),
        m_name(markerByteToName.at(byte))
    {}
    catch(const std::out_of_range& e) {
        throw UnknownMarkerException(byte);
    }

const JPEGMarkerByte JPEGMarker::getMarkerByte() const {
    return m_byte;
}

const std::string& JPEGMarker::getName() const {
    return m_name;
}

const bool JPEGMarker::isRecognizedMarkerByte(const unsigned char byte) {
    const JPEGMarkerByte markerByte = static_cast<JPEGMarkerByte>(byte);
    return markerByteToName.count(markerByte) > 0;
}

bool JPEGMarker::operator<(const JPEGMarker& other) const {
    return this->getMarkerByte() < other.getMarkerByte();
}

bool JPEGMarker::operator=(const JPEGMarker& other) const {
    return this->getMarkerByte() == other.getMarkerByte();
}

bool JPEGMarker::operator>(const JPEGMarker& other) const {
    return this->getMarkerByte() > other.getMarkerByte();
}


UnknownMarkerException::UnknownMarkerException(unsigned char marker) :
    marker(marker)
    {};