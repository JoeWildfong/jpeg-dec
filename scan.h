#pragma once

#include <vector>

#include "stream.h"

class JPEGScan {
    public:
        JPEGScan(JPEGStream& stream, const std::streampos offset);
        typedef struct {
            u4 dcTable;
            u4 acTable;
        } ScanComponent;
        std::vector<ScanComponent> components;
        u8 ss;
        u8 se;
        u4 ah;
        u4 al;
};
