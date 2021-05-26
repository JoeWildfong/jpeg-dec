#include "scan.h"
#include "bitstream.h"
#include <iostream>

JPEGScan::JPEGScan(std::string& data) {
  Bitstream stream {data};
  unsigned short length = stream.readWord();
  unsigned char numComponents = stream.readByte();
  for (int i = 0; i < numComponents; i++) {
    unsigned char id = stream.readByte();
    ScanComponent c;
    c.dcTable = stream.readNibble();
    c.acTable = stream.readNibble();
    components.push_back(c);
  }
  ss = stream.readByte();
  se = stream.readByte();
  ah = stream.readNibble();
  al = stream.readNibble();
}