#include "huffman.h"

#include <iostream>

HuffmanTables::HuffmanTables() {}

void HuffmanTables::addTable(JPEGStream& stream, std::streampos offset) {
    stream.clear();
    stream.seekg(offset);
    word len = stream.getWord();
    byte tableId = stream.getByte();
    HuffmanTable& table = getTable(tableId);
    unsigned int code = 0;
    unsigned char numElements[16];
    for (auto i = 0; i < 16; i++) {
        numElements[i] = stream.get();
    }
    for (auto i = 0; i < 16; i++) {
        for (auto j = 0; j < numElements[i]; j++) {
            table[HuffmanKey(i + 1, code)] = stream.getByte();
            code++;
        }
        code <<= 1;
    }
}

HuffmanTables::HuffmanTable& HuffmanTables::getTable(byte byteId) {
    nybble tableType = (byteId.to_ulong() >> 4) & 0x0F;
    nybble tableId = byteId.to_ulong() & 0x0F;
    std::array<HuffmanTable, 4>& tableList = (tableType == 0? dcTables: acTables);
    return tableList[tableId.to_ulong()];
}