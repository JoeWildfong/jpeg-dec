#pragma once

#include <map>
#include <array>

#include "stream.h"
#include "types.h"

class HuffmanTables {
    public:
        HuffmanTables();
        void addTable(JPEGStream& stream, std::streampos offset);
        typedef std::pair<u16, u32> HuffmanKey;
        typedef std::map<HuffmanKey, u8> HuffmanTable;
        std::array<HuffmanTable, 4> dcTables;
        std::array<HuffmanTable, 4> acTables;
        HuffmanTable& getTable(u8 byteId);
};
