#pragma once

#include <exception>
#include <string_view>

#include "types.h"

enum class JPEGMarkerByte {
    SOI  = 0xD8,
    EOI  = 0xD9,
    SOF0 = 0xC0,
    SOF2 = 0xC2,
    DHT  = 0xC4,
    RST0 = 0xD0,
    RST1 = 0xD1,
    RST2 = 0xD2,
    RST3 = 0xD3,
    RST4 = 0xD4,
    RST5 = 0xD5,
    RST6 = 0xD6,
    RST7 = 0xD7,
    SOS  = 0xDA,
    DQT  = 0xDB,
    DRI  = 0xDD,
    APP0 = 0xE0,
    APP1 = 0xE1,
    APP2 = 0xE2,
    APP3 = 0xE3,
    APP4 = 0xE4,
    APP5 = 0xE5,
    APP6 = 0xE6,
    APP7 = 0xE7,
    APP8 = 0xE8,
    APP9 = 0xE9,
    APPA = 0xEA,
    APPB = 0xEB,
    APPC = 0xEC,
    APPD = 0xED,
    APPE = 0xEE,
    APPF = 0xEF,
    COM  = 0xFE,
};

class JPEGMarker {
    public:
        JPEGMarker(const u8 byte);
        JPEGMarker(const JPEGMarkerByte byte);

        const JPEGMarkerByte getMarkerByte() const;
        const std::string_view getName() const;
        bool operator<(const JPEGMarker& other) const;
        bool operator==(const JPEGMarker& other) const;
        bool operator>(const JPEGMarker& other) const;

        static const bool isRecognizedMarkerByte(const u8 byte);
        static const bool isRecognizedMarkerByte(const JPEGMarkerByte byte);
    private:
        const JPEGMarkerByte m_byte;
};

class UnknownMarkerException : std::exception {
    public:
        UnknownMarkerException(const JPEGMarkerByte marker);
        const JPEGMarkerByte marker;
};
