#include "Tile.hpp"

namespace mbtiles {

    Tile::Tile(int z, int c, int r, std::vector<byte> d) : zoom(z), column(c), row(r), data(d) {}

    Tile::Tile(int z, int c, int r) : zoom(z), column(c), row(r), data(std::vector<byte>{}) {}

    Tile::Tile(int z, int c, int r, std::string fileName) : zoom(z), column(c), row(r), data(readFile(fileName)) {}

    void Tile::save(std::string fileName) {
        std::ofstream outfile(fileName, std::ios::out | std::ios::binary); 
        outfile.write(reinterpret_cast<const char*>(data.data()), data.size());
    }

    std::vector<byte> Tile::readFile(std::string filename) {
        std::ifstream file(filename.c_str(), std::ios::binary);
        file.unsetf(std::ios::skipws);
        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<byte> vec;
        vec.reserve(fileSize);
        vec.insert(
            vec.begin(),
            std::istream_iterator<byte>(file),
            std::istream_iterator<byte>()
        );
        return vec;
    }



    std::ostream& operator << (std::ostream& os, const Tile& t) {
        os << "TILE (" << t.zoom << ", " << t.column  << ", " << t.row  << ")";
        return os;
    }

}