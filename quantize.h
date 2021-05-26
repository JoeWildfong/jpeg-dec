#pragma once

#include <string>
#include "matrix.h"
#include "bitstream.h"
#include <array>

class QuantizationTables {
  public:
    QuantizationTables(std::string& raw);
    QuantizationTables(Bitstream* stream);
    void addTable(std::string& raw);
    void addTable(Bitstream* stream);
    typedef Matrix8x8 QTable;
    std::array<QTable, 4> tables;
    std::array<bool, 4> defined;
};