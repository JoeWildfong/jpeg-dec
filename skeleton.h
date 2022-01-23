#pragma once
#include <vector>
#include <string_view>
#include <map>

#include "stream.h"
#include "markers.h"

namespace JPEG {

class Skeleton {
    public:
        Skeleton(JPEGStream& data);
        const std::vector<std::streampos>& getTags(const JPEGMarkerByte byte) const;
        const std::string_view toString() const;
    private:
        std::map<const JPEGMarker, std::vector<std::streampos>> tags;
};

}
