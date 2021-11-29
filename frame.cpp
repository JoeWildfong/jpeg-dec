#include "frame.h"
#include "bitstream.h"
#include <iostream>

JPEGFrame::JPEGFrame(JPEGStream& data, std::streampos offset) {
    data.seekg(offset);
    JPEGBitstream& stream {std::move(data)};
    unsigned short length = stream.getWord();
    header.precision = stream.getByte();
    header.height = stream.getWord();
    header.width = stream.getWord();
    header.component_count = stream.getByte();
    for (int i = 0; i < header.component_count; i++) {
        unsigned char id = stream.getByte();
        FrameComponent c;
        c.h_sampling = stream.getNibble();
        c.v_sampling = stream.getNibble();
        c.q_table = stream.getByte();
        components.push_back(c);
    }
}