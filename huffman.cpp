#include "huffman.h"
#include "bitstream.h"
#include <iostream>

HuffmanTables::HuffmanTables() : number(0) {}

void HuffmanTables::addTable(JPEGStream& stream, std::streampos offset) {
    stream.seekg(offset);
    JPEGBitstream& bitstream {std::move(stream)};
    int i, j;
    int len = bitstream.getWord();
    unsigned char tableId = bitstream.getByte();
    HuffmanTable table = getTable(tableId);
    unsigned int code = 0;
    unsigned char numElements[16];
    for (i = 0; i < 16; i++) {
        numElements[i] = bitstream.getByte();
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < numElements[i]; j++) {
            table[HuffmanKey(i + 1, code)] = bitstream.getByte();
            code++;
        }
        code <<= 1;
    }
}

HuffmanTables::HuffmanTable& HuffmanTables::getTable(unsigned char byteId) {
    unsigned int tableType = (byteId >> 4) & 0x0F;
    unsigned int tableId = byteId & 0x0F;
    std::cout << tableType << " " << tableId << std::endl;
    HuffmanTable* tableList = (tableType == 0? dcTables: acTables);
    return tableList[tableId];
}