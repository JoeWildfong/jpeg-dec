#pragma once

#include <vector>

#include "stream.h"

class JPEGFrame {
    public:
        JPEGFrame(JPEGStream& data, std::streampos offset);
        struct {
            unsigned char precision;
            unsigned short height;
            unsigned short width;
            unsigned char component_count;
        } header;
        typedef struct {
            unsigned char h_sampling;
            unsigned char v_sampling;
            unsigned char q_table;
        } FrameComponent;
        std::vector<FrameComponent> components;
};