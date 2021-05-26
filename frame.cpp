#include "frame.h"
#include "bitstream.h"
#include <iostream>

JPEGFrame::JPEGFrame(std::string& data) {
  Bitstream stream {data};
  unsigned short length = stream.readWord();
  if (data.size() != length) {
    std::cout << "Frame section is the wrong size" << std::endl;
  }
  header.precision = stream.readByte();
  header.height = stream.readWord();
  header.width = stream.readWord();
  header.component_count = stream.readByte();
  for (int i = 0; i < header.component_count; i++) {
    unsigned char id = stream.readByte();
    FrameComponent c;
    c.h_sampling = stream.readNibble();
    c.v_sampling = stream.readNibble();
    c.q_table = stream.readByte();
    components.push_back(c);
  }
}