#pragma once

#include <map>
#include <array>

#include "stream.h"

class HuffmanTables {
    public:
        HuffmanTables();
        void addTable(JPEGStream& stream, std::streampos offset);
        byte number;
        typedef std::pair<unsigned short, unsigned int> HuffmanKey;
        typedef std::map<HuffmanKey, byte> HuffmanTable;
        std::array<HuffmanTable, 4> dcTables;
        std::array<HuffmanTable, 4> acTables;
        HuffmanTable& getTable(byte byteId);
};