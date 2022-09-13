#include "quantize.h"
#include <iostream>

QuantizationTables::QuantizationTables(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    stream.resetByteCounter();
    u16 length = stream.get16();
    while (!stream.atMarker()) {
        addTable(stream, stream.tellg());
    }
    if (stream.getByteCounter() != length) {
        std::cerr << "Warning: improper DQT frame length" << std::endl;
    }
}

void QuantizationTables::addTable(JPEGStream& stream, const std::streampos offset) {
    stream.seekg(offset);
    const auto [precision, id] = stream.get4Pair();
    QTable table {stream, stream.tellg()};
    tables[id] = table;
    defined.set(id);
}
