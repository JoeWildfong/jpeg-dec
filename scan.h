#pragma once

#include <vector>

#include "stream.h"

class JPEGScan {
    public:
        JPEGScan(JPEGStream& stream, const std::streampos offset);
        typedef struct {
            nybble dcTable;
            nybble acTable;
        } ScanComponent;
        std::vector<ScanComponent> components;
        byte ss;
        byte se;
        nybble ah;
        nybble al;
};