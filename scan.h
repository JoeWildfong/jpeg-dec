#pragma once

#include <string>
#include <vector>

class JPEGScan {
  public:
    JPEGScan(std::string& data);
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