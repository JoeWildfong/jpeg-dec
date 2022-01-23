#pragma once

#include <array>
#include <bitset>
#include "stream.h"
#include "matrix.h"
#include "stream.h"

class QuantizationTables {
    public:
        QuantizationTables(JPEGStream& stream, const std::streampos offset);
        void addTable(JPEGStream& stream, const std::streampos offset);
        typedef Matrix8x8 QTable;
        std::array<QTable, 4> tables;
        std::bitset<4> defined;
};
