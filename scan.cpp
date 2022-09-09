#include "scan.h"
#include "stream.h"
#include <iostream>

JPEGScan::JPEGScan(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    u16 length = stream.get16();
    u8 numComponents = stream.get8();
    for (int i = 0; i < numComponents; i++) {
        u8 id = stream.get8();
        ScanComponent c;
        std::tie(c.dcTable, c.acTable) = stream.get4Pair();
        components.push_back(c);
    }
    ss = stream.get8();
    se = stream.get8();
    std::tie(ah, al) = stream.get4Pair();
}
