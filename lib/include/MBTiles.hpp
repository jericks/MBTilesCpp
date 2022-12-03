#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <filesystem>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Tile.hpp"
#include "Metadatum.hpp"
#include "Grid.hpp"
#include "GridData.hpp"

namespace mbtiles {

    struct MBTilesOptions {
        std::string name = "world";
        std::string version = "1.0";
        std::string description = "Tiles";
        std::string attribution = "Create with MBTilesCpp";
        std::string type = "base_layer";
        std::string format = "jpeg";
        std::string bounds = "-179.99,-85.0511,179.99,85.0511";
        std::string minzoom = "0";
        std::string maxzoom = "1";
    };

    class MBTiles {

        private:

            std::string fileName;

            void createTables(); 

        public:

            MBTiles(std::string fileName);

            MBTiles(std::string fileName, MBTilesOptions options);

            ~MBTiles();

            int getMinZoom();

            int getMaxZoom();
            
            int countTiles();

            int countTiles(int zoom);
            
            void loadFromDirectory(std::string directory);

            void exportToDirectory(std::string directory);

            // Metadata

            void addMetadatum(const Metadatum& m);

            void updateMetadatum(const Metadatum& m);

            void setMetadatum(const Metadatum& m);

            void deleteMetadatum(const Metadatum& m);

            std::map<std::string,std::string> getMetadata();

            std::optional<Metadatum> getMetadatum(const std::string& name);    

            // Tiles

            void addTile(const Tile& t);

            void updateTile(const Tile& t);

            void setTile(const Tile& t);

            void deleteTile(const Tile& t);

            std::optional<Tile> getTile(int z, int c, int r);    

            void tiles(int zoom, std::function<void(Tile& t)> f);

            // Grid

            void addGrid(const Grid& g);

            void updateGrid(const Grid& g);

            void setGrid(const Grid& g);

            void deleteGrid(const Grid& g);

            std::optional<Grid> getGrid(int z, int c, int r);   

            void grids(int zoom, std::function<void(Grid& g)> f);

            // GridData

            void addGridData(const GridData& g);

            void updateGridData(const GridData& g);

            void setGridData(const GridData& g);

            void deleteGridData(const GridData& g);

            std::optional<GridData> getGridData(int z, int c, int r, std::string name);   

            std::map<std::string,std::string> getGridData(int z, int c, int r);

    };

    

}