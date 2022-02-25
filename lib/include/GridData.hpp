#pragma once

#include <string>
#include <iostream>

namespace mbtiles {
    
    struct GridData {
        int zoom;
        int column;
        int row;
        std::string name;
        std::string json;
    };

    std::ostream& operator << (std::ostream& os, const GridData& g);

}