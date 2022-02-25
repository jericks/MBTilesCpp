#pragma once

#include <string>
#include <iostream>

namespace mbtiles {
    
    struct Metadatum {
        std::string name;
        std::string value;
    };

    std::ostream& operator << (std::ostream& os, const Metadatum& m);

}