#include "huffman.h"
#include "bitstream.h"
#include <iostream>

HuffmanTables::HuffmanTables() {
  number = 0;
  
}

void HuffmanTables::addTable(std::string data) {
  Bitstream stream {data};
  int i, j;
  int len = stream.readWord();
  unsigned char tableId = stream.readByte();
  huffTable* table = getTable(tableId);
  unsigned int code = 0;
  unsigned char numElements[16];
  for (i = 0; i < 16; i++) {
    numElements[i] = stream.readByte();
  }
  for (i = 0; i < 16; i++) {

    for (j = 0; j < numElements[i]; j++) {
      (*table)[huffKey(i + 1, code)] = stream.readByte();
      code++;
    }
    code <<= 1;
  }
}

HuffmanTables::huffTable* HuffmanTables::getTable(unsigned char byteId) {
  unsigned int tableType = (byteId >> 4) & 0x0F;
  unsigned int tableId = byteId & 0x0F;
  std::cout << tableType << " " << tableId << std::endl;
  huffTable* tableList = (tableType == 0? dcTables: acTables);
  return &(tableList[tableId]);
}