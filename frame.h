#pragma once

#include <vector>

#include "types.h"
#include "stream.h"

class JPEGFrame {
    public:
        JPEGFrame(JPEGStream& stream, std::streampos offset);
        u8 precision;
        u16 height;
        u16 width;
        typedef struct {
            u4 h_sampling;
            u4 v_sampling;
            u8 q_table;
        } FrameComponent;
        std::vector<FrameComponent> components;
};
