#include "quantize.h"
#include <iostream>

QuantizationTables::QuantizationTables(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    JPEGBitstream& bitstream {std::move(stream)};
    tables.empty();
    defined.empty();
    unsigned short length = bitstream.getWord();
    while (!bitstream.atMarker()) {
        addTable(bitstream, bitstream.tellg());
    }
}

void QuantizationTables::addTable(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    JPEGBitstream& bitstream {std::move(stream)};
    unsigned char precision = bitstream.getNibble();
    unsigned char id = bitstream.getNibble();
    QTable table {bitstream};
    tables[id] = table;
    defined[id] = true;
}
