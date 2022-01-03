#include <iostream>
#include "frame.h"

JPEGFrame::JPEGFrame(JPEGStream& stream, std::streampos offset) {
    stream.seekg(offset);
    word length = stream.getWord();
    header.precision = stream.getByte();
    header.height = stream.getWord();
    header.width = stream.getWord();
    header.component_count = stream.getByte();
    for (auto i = 0; i < header.component_count.to_ulong(); i++) {
        byte id = stream.getByte();
        FrameComponent c;
        const auto [hs, vs] = stream.getNybblePair();
        c.h_sampling = hs;
        c.v_sampling = vs;
        c.q_table = stream.getByte();
        components.push_back(c);
    }
}