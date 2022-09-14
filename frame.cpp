#include <iostream>
#include "frame.h"

JPEGFrame::JPEGFrame(JPEGStream& stream, std::streampos offset) {
    stream.seekg(offset);
    stream.resetByteCounter();
    u16 length = stream.get16();
    precision = stream.get8();
    height = stream.get16();
    width = stream.get16();
    u8 component_count = stream.get8();
    std::cout << "number of frame components: " << +component_count << '\n';
    for (auto i = 0; i < component_count; i++) {
        u8 id = stream.get8();
        FrameComponent c;
        const auto [hs, vs] = stream.get4Pair();
        c.h_sampling = hs;
        c.v_sampling = vs;
        c.q_table = stream.get8();
        components.push_back(c);
    }
    if (stream.getByteCounter() != length) {
        std::cerr << "Warning: improper SOF frame length\n";
    }
}
