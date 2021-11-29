#pragma once

#include <map>

#include "stream.h"

class HuffmanTables {
    public:
        HuffmanTables();
        void addTable(JPEGStream& stream, std::streampos offset);
        unsigned char number;
        typedef std::pair<int, unsigned int> HuffmanKey;
        typedef std::map<HuffmanKey, unsigned char> HuffmanTable;
        HuffmanTable dcTables[4];
        HuffmanTable acTables[4];
        HuffmanTable& getTable(unsigned char byteId);
};