#include <iostream>
#include <memory>

#include "stream.h"
#include "skeleton.h"
#include "markers.h"
#include "huffman.h"
#include "quantize.h"
#include "frame.h"
#include "scan.h"

using namespace std;

int main() {
    JPEGStream inFile;
    inFile.open("input.jpg", ios::binary);
    if (!inFile.is_open()) {
        cout << "Unable to open input.jpg" << endl;
        return 1;
    }
    
    std::unique_ptr skeleton = make_unique<JPEG::Skeleton>(inFile);

    std::cout << "skeleton parsed, tags:" << std::endl;
    std::cout << skeleton->toString() << std::endl;

    HuffmanTables huffTables;

    const std::vector<std::streampos> DHTs = skeleton->getTags(JPEGMarkerByte::DHT);
    for (int i = 0; i < DHTs.size(); i++) {
        huffTables.addTable(inFile, DHTs[i]);
    }
    for (int i = 0; i < 4; i++) {
        std::cout << "dc table " << i << ": length " << huffTables.dcTables[i].size() << std::endl;
    }
    for (int i = 0; i < 4; i++) {
        std::cout << "ac table " << i << ": length " << huffTables.acTables[i].size() << std::endl;
    }

    QuantizationTables qtables {inFile, skeleton->getTags(JPEGMarkerByte::DQT)[0]};
    for (int i = 0; i < 4; i++) {
        std::cout << "qtable " << i <<": " << (qtables.defined[i]? "defined":"undefined") << std::endl;
    }

    JPEGFrame frame {inFile, skeleton->getTags(JPEGMarkerByte::SOF0)[0]};
    std::cout << "dimensions: " << frame.header.width << "x" << frame.header.height << std::endl;

    JPEGScan scan {inFile, skeleton->getTags(JPEGMarkerByte::SOS)[0]};
    for (int i = 0; i < scan.components.size(); i++) {
        std::cout << "component " << i << ": sampling " << int(frame.components[i].h_sampling) << "x" << int(frame.components[i].v_sampling) << ", qtable " << int(frame.components[i].q_table) << ", dcTable " << int(scan.components[i].dcTable) << ", acTable " << int(scan.components[i].acTable) << std::endl;
    }

    inFile.close();
}