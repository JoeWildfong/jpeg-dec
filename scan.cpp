#include "scan.h"
#include "stream.h"
#include <iostream>

JPEGScan::JPEGScan(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    word length = stream.getWord();
    byte numComponents = stream.getByte();
    for (int i = 0; i < numComponents.to_ulong(); i++) {
        byte id = stream.getByte();
        ScanComponent c;
        const auto [dcTable, acTable] = stream.getNybblePair();
        c.dcTable = dcTable;
        c.acTable = acTable;
        components.push_back(c);
    }
    ss = stream.getByte();
    se = stream.getByte();
    auto [ah, al] = stream.getNybblePair();
}