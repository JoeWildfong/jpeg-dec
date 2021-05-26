#include <iostream>
#include <fstream>

#include "parse.h"
#include "huffman.h"
#include "quantize.h"
#include "frame.h"
#include "scan.h"

using namespace std;

int main() {
  std::ifstream inFile;
  inFile.open("input.jpg", ios::binary);
  if (!inFile.is_open()) {
    cout << "Unable to open input.jpg" << endl;
    return 1;
  }
  
  JPEGParse* head = new JPEGParse(inFile);

  std::cout << "header parsed, tags:" << std::endl;
  std::cout << head->toString() << std::endl;

  HuffmanTables huffTables;

  std::vector<std::string> DHTs = head->getTags("DHT");
  for (int i = 0; i < DHTs.size(); i++) {
    huffTables.addTable(DHTs[i]);
  }
  for (int i = 0; i < 4; i++) {
    std::cout << "dc table " << i << ": length " << huffTables.dcTables[i].size() << std::endl;
  }
  for (int i = 0; i < 4; i++) {
    std::cout << "ac table " << i << ": length " << huffTables.acTables[i].size() << std::endl;
  }

  QuantizationTables qtables {head->getTags("DQT")[0]};
  for (int i = 0; i < 4; i++) {
    std::cout << "qtable " << i <<": " << (qtables.defined[i]? "defined":"undefined") << std::endl;
  }

  JPEGFrame frame {head->getTags("SOF0")[0]};
  std::cout << "dimensions: " << frame.header.width << "x" << frame.header.height << std::endl;

  JPEGScan scan {head->getTags("SOS")[0]};
  for (int i = 0; i < scan.components.size(); i++) {
    std::cout << "component " << i << ": sampling " << int(frame.components[i].h_sampling) << "x" << int(frame.components[i].v_sampling) << ", qtable " << int(frame.components[i].q_table) << ", dcTable " << int(scan.components[i].dcTable) << ", acTable " << int(scan.components[i].acTable) << std::endl;
  }

  inFile.close();
}