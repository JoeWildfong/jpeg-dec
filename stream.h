#pragma once

#include <fstream>
#include <string_view>
#include <exception>
#include <tuple>

#include "types.h"
#include "markers.h"

class JPEGStream : public std::ifstream {
    public:
        const std::pair<u4, u4> get4Pair();
        const u8 get8();
        const u16 get16();
        const u32 get32();
        const JPEGMarker getMarker();
        const std::string_view getHex();
        const bool atMarker();
        void skipToMarker();
        
        using std::ifstream::ifstream;
        JPEGStream(std::ifstream&& stream) : std::ifstream(std::move(stream)) {};

        ~JPEGStream() = default;

        JPEGStream(const JPEGStream& copy) = delete;
        JPEGStream(JPEGStream&& move) = default;
        
        JPEGStream& operator=(const JPEGStream& copy) = delete;
        JPEGStream& operator=(JPEGStream&& move) = default;
};

class NotAMarkerException : std::exception {
    public:
        NotAMarkerException(const std::streampos pos);
        const std::streampos pos;
};
