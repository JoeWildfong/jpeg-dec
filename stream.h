#pragma once

#include <fstream>
#include <string>
#include <exception>

#include "markers.h"

class JPEGStream : public std::ifstream {
    public:
        const JPEGMarker&& getMarker();
        const std::string&& getHex();
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