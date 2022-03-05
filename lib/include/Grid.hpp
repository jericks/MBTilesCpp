#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

namespace mbtiles {
    
    using byte = unsigned char;

    struct Grid {

        int zoom;
        int column;
        int row;
        std::vector<byte> data;

        Grid(int z, int c, int r, std::vector<byte> d);

        Grid(int z, int c, int r);

        Grid(int z, int c, int r, std::string fileName);

        void save(std::string fileName);    

        private:

            std::vector<byte> readFile(std::string filename);   

    };

    std::ostream& operator << (std::ostream& os, const Grid& g);

}