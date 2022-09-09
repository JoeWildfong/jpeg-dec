#pragma once

#include <fstream>
#include <string_view>
#include <exception>
#include <tuple>

#include "types.h"
#include "markers.h"

class JPEGStream {
    public:
        const std::pair<u4, u4> get4Pair();
        const u8 get8();
        const u16 get16();
        const u32 get32();
        const JPEGMarker getMarker();
        const std::string_view getHex();
        const bool atMarker();
        void skipToMarker();
        void clear();
        bool eof();
        JPEGStream& seekg(std::streampos pos);
        std::streampos tellg();
        void close();
        
        JPEGStream(std::ifstream&& stream) : m_stream(std::move(stream)) {};

        ~JPEGStream() = default;

        JPEGStream(const JPEGStream& copy) = delete;
        JPEGStream(JPEGStream&& move) = default;
        
        JPEGStream& operator=(const JPEGStream& copy) = delete;
        JPEGStream& operator=(JPEGStream&& move) = default;

    private:
        std::ifstream m_stream;
};

class NotAMarkerException : std::exception {
    public:
        NotAMarkerException(const std::streampos pos);
        const std::streampos pos;
};
