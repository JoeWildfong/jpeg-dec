#include "quantize.h"
#include <iostream>

QuantizationTables::QuantizationTables(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    tables.empty();
    word length = stream.getWord();
    while (!stream.atMarker()) {
        addTable(stream, stream.tellg());
    }
}

void QuantizationTables::addTable(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    const auto [precision, id] = stream.getNybblePair();
    QTable table {stream, stream.tellg()};
    tables[id.to_ulong()] = table;
    defined.set(id.to_ulong());
}
