#pragma once

#include <array>
#include <utility>
#include <map>
#include <string>

class HuffmanTables {
  public:
    HuffmanTables();
    void addTable(std::string data);
    unsigned char number;
    typedef std::pair<int, unsigned int> huffKey;
    typedef std::map<huffKey, unsigned char> huffTable;
    huffTable dcTables[4];
    huffTable acTables[4];
    huffTable* getTable(unsigned char byteId);
};