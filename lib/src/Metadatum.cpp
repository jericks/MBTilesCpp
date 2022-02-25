#include "Metadatum.hpp"

namespace mbtiles {

    std::ostream& operator << (std::ostream& os, const Metadatum& m) {
        os << "METADATUM (" << m.name << " = " << m.value  << ")";
        return os;
    }

}