#include "quantize.h"
#include <iostream>

QuantizationTables::QuantizationTables(std::string& raw) : QuantizationTables(new Bitstream(raw)) {}

QuantizationTables::QuantizationTables(Bitstream* stream) {
  tables.empty();
  defined.empty();
  unsigned short length = stream->readWord();
  while (stream->remaining() > 0) {
    addTable(stream);
  }
}

void QuantizationTables::addTable(std::string& raw) {
  addTable(new Bitstream(raw));
}

void QuantizationTables::addTable(Bitstream* stream) {
  unsigned char precision = stream->readNibble();
  unsigned char id = stream->readNibble();
  QTable table {stream};
  tables[id] = table;
  defined[id] = true;
}
