#include "scan.h"
#include "bitstream.h"
#include <iostream>

JPEGScan::JPEGScan(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    JPEGBitstream&& bitstream {std::move(stream)};
    unsigned short length = bitstream.getWord();
    unsigned char numComponents = bitstream.getByte();
    for (int i = 0; i < numComponents; i++) {
        unsigned char id = bitstream.getByte();
        ScanComponent c;
        c.dcTable = bitstream.getNibble();
        c.acTable = bitstream.getNibble();
        components.push_back(c);
    }
    ss = bitstream.getByte();
    se = bitstream.getByte();
    ah = bitstream.getNibble();
    al = bitstream.getNibble();
}