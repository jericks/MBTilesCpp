#include "GridData.hpp"

namespace mbtiles {

    std::ostream& operator << (std::ostream& os, const GridData& g) {
        os << "GRIDDATA (" << g.zoom << ", " << g.column  << ", " << g.row << ", " << g.name << " = " << g.json  << ")";
        return os;
    }

}