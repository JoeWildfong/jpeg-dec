#include "skeleton.h"
#include <iostream>

JPEG::Skeleton::Skeleton(JPEGStream& data) {
    tags.clear();
    while (true) {
        try {
            if (data.eof()) {
                break;
            }
            JPEGMarker marker = data.getMarker();
            tags[marker].push_back(data.tellg());
        } catch (const NotAMarkerException& err) {
            std::cout << "Expected marker at byte " << err.pos << ", got " << data.getHex() << std::endl;
        }
        data.skipToMarker();
    }
}

const std::vector<const std::streampos>& JPEG::Skeleton::getTags(JPEGMarkerByte byte) const {
    return tags.at(JPEGMarker(byte));
}

const std::string& JPEG::Skeleton::toString() const {
    std::string out = "";
    for (auto tagType = tags.begin(); tagType != tags.end(); tagType++) {
        auto tagName = tagType->first.getName();
        auto offsetList = tagType->second;
        for (auto offset = offsetList.begin(); offset != offsetList.end(); offset++) {
            out += tagName + " at offset " + std::to_string(*offset) + "\n";
        }
    }
    return out;
}