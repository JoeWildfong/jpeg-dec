#include "skeleton.h"
#include <iostream>
#include <sstream>

JPEG::Skeleton::Skeleton(JPEGStream& data) {
    tags.clear();
    while (!data.eof()) {
        try {
            const JPEGMarker marker = data.getMarker();
            tags[marker].push_back(data.tellg());
            std::cout << "Found marker " << marker.getName() << " at " << data.tellg() << '\n';
        } catch (const NotAMarkerException& err) {
            std::cout << "Expected marker at byte " << err.pos << ", got " << data.getHex() << '\n';
        }
        data.skipToMarker();
    }
    std::cout << "finished parsing skeleton\n";
}

const std::vector<std::streampos>& JPEG::Skeleton::getTags(JPEGMarkerByte byte) const {
    return tags.at(JPEGMarker(byte));
}

const std::string JPEG::Skeleton::toString() const {
    std::ostringstream out;
    for (auto tagType = tags.begin(); tagType != tags.end(); tagType++) {
        auto tagName = tagType->first.getName();
        auto offsetList = tagType->second;
        for (auto offset = offsetList.begin(); offset != offsetList.end(); offset++) {
            out << tagName << " at offset " << std::to_string(*offset) << '\n';
        }
    }
    return out.str();
}
