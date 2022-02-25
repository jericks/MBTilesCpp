#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace mbtiles {

    using byte = unsigned char;

    struct Tile {

        int zoom;
        int column;
        int row;
        std::vector<byte> data;

        Tile(int z, int c, int r, std::vector<byte> d);

        Tile(int z, int c, int r);

        Tile(int z, int c, int r, std::string fileName);

        void save(std::string fileName);

        private:

            std::vector<byte> readFile(std::string filename);    

    };

    std::ostream& operator << (std::ostream& os, const Tile& tile);

}