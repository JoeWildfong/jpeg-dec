#include <iostream>
#include <memory>

#include "stream.h"
#include "skeleton.h"
#include "markers.h"
#include "huffman.h"
#include "quantize.h"
#include "frame.h"
#include "scan.h"


int main(int argc, char *argv[]) {
    std::ifstream file;
    std::string filename = "input.jpg";
    if (argc >= 2) {
        filename = argv[1];
    }
    std::cout << "JPEG File " << filename << ":\n";
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Unable to open input.jpg\n";
        return 1;
    }

    JPEGStream inFile {std::move(file)};
    
    auto skeleton = std::make_unique<JPEG::Skeleton>(inFile);

    HuffmanTables huffTables;

    const std::vector<std::streampos>& DHTs = skeleton->getTags(JPEGMarkerByte::DHT);
    for (int i = 0; i < DHTs.size(); i++) {
        huffTables.addTable(inFile, DHTs[i]);
    }
    for (int i = 0; i < 4; i++) {
        std::cout << "dc table " << i << ": length " << huffTables.dcTables[i].size() << '\n';
    }
    for (int i = 0; i < 4; i++) {
        std::cout << "ac table " << i << ": length " << huffTables.acTables[i].size() << '\n';
    }

    QuantizationTables qtables {inFile, skeleton->getTags(JPEGMarkerByte::DQT)[0]};
    for (int i = 0; i < 4; i++) {
        std::cout << "qtable " << i << ": " << (qtables.defined[i]? "defined\n" : "undefined\n");
    }

    JPEGFrame frame {inFile, skeleton->getTags(JPEGMarkerByte::SOF0)[0]};
    std::cout << "dimensions: " << frame.width << "x" << frame.height << '\n';
    std::cout << "component count: " << frame.components.size() << '\n';

    JPEGScan scan {inFile, skeleton->getTags(JPEGMarkerByte::SOS)[0]};
    for (int i = 0; i < scan.components.size(); i++) {
        std::cout << "component " << i
            << ": sampling " << +frame.components[i].h_sampling
            << "x" << +frame.components[i].v_sampling
            << ", qtable " << +frame.components[i].q_table
            << ", dcTable " << +scan.components[i].dcTable
            << ", acTable " << +scan.components[i].acTable
            << '\n';
    }

    inFile.close();
}
