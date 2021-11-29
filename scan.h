#pragma once

#include <vector>

#include "stream.h"

class JPEGScan {
    public:
        JPEGScan(JPEGStream& data, const std::streampos offset);
        typedef struct {
            unsigned char dcTable;
            unsigned char acTable;
        } ScanComponent;
        std::vector<ScanComponent> components;
        unsigned char ss;
        unsigned char se;
        unsigned char ah;
        unsigned char al;
};