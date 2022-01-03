#pragma once

#include <vector>

#include "stream.h"

class JPEGFrame {
    public:
        JPEGFrame(JPEGStream& stream, std::streampos offset);
        struct {
            byte precision;
            word height;
            word width;
            byte component_count;
        } header;
        typedef struct {
            nybble h_sampling;
            nybble v_sampling;
            byte q_table;
        } FrameComponent;
        std::vector<FrameComponent> components;
};