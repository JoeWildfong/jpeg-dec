#include "quantize.h"
#include <iostream>

QuantizationTables::QuantizationTables(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    tables.empty();
    u16 length = stream.get16();
    while (!stream.atMarker()) {
        addTable(stream, stream.tellg());
    }
}

void QuantizationTables::addTable(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    const auto [precision, id] = stream.get4Pair();
    QTable table {stream, stream.tellg()};
    tables[id] = table;
    defined.set(id);
}
