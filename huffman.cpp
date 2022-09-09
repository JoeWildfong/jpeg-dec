#include "huffman.h"

#include <iostream>

HuffmanTables::HuffmanTables() {}

void HuffmanTables::addTable(JPEGStream& stream, std::streampos offset) {
    stream.clear();
    stream.seekg(offset);
    u16 length = stream.get16();
    u8 tableId = stream.get8();
    HuffmanTable& table = getTable(tableId);
    u32 code = 0;
    u8 numElements[16];
    for (auto i = 0; i < 16; i++) {
        numElements[i] = stream.get8();
    }
    for (auto i = 0; i < 16; i++) {
        for (auto j = 0; j < numElements[i]; j++) {
            table[HuffmanKey(i + 1, code)] = stream.get8();
            code++;
        }
        code <<= 1;
    }
}

HuffmanTables::HuffmanTable& HuffmanTables::getTable(u8 byteId) {
    u4 tableType = (byteId >> 4) & 0x0F;
    u4 tableId = byteId & 0x0F;
    std::array<HuffmanTable, 4>& tableList = (tableType == 0? dcTables: acTables);
    return tableList[tableId];
}
