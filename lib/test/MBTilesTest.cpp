#include <sstream>
#include <iostream>
#include <filesystem>
#include "MBTiles.hpp"
#include "gtest/gtest.h"

TEST(MBTilesLibTests, mbtiles_create) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_min_zoom) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    EXPECT_EQ(0, mbtiles.getMinZoom());
    EXPECT_EQ(1, mbtiles.getMaxZoom());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_count_tiles) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    EXPECT_EQ(1, mbtiles.countTiles(0));
    EXPECT_EQ(4, mbtiles.countTiles(1));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_export) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    mbtiles.exportToDirectory("tms");
    // @TODO Needs EXPECTS

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_import) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    mbtiles.loadFromDirectory("../../../data/tms");
    
    
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Metadata

TEST(MBTilesLibTests, metadatum_str) {
    mbtiles::Metadatum m{"alt_name","Tiles"};
    std::stringstream str;
    str << m;
    EXPECT_EQ("METADATUM (alt_name = Tiles)", str.str());
}

TEST(MBTilesLibTests, mbtiles_add_metadatum) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_update_metadatum) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m1 = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m1.has_value());
    EXPECT_EQ("Tiles", m1.value().value);

    mbtiles.updateMetadatum(mbtiles::Metadatum{"alt_name","MBTiles"});
    std::optional<mbtiles::Metadatum> m2 = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m2.has_value());
    EXPECT_EQ("MBTiles", m2.value().value);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_set_metadatum) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.setMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m.has_value());
    EXPECT_EQ("Tiles", m->value);

    mbtiles.setMetadatum(mbtiles::Metadatum{"alt_name","Tiles 2"});
    m = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m.has_value());
    EXPECT_EQ("Tiles 2", m->value);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_delete_metadatum) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m1 = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m1.has_value());
    EXPECT_EQ("Tiles", m1.value().value);

    mbtiles.deleteMetadatum(m1.value());
    std::optional<mbtiles::Metadatum> m2 = mbtiles.getMetadatum("alt_name");
    EXPECT_FALSE(m2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_metadatum) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<mbtiles::Metadatum> m1 = mbtiles.getMetadatum("alt_name");
    EXPECT_FALSE(m1.has_value());
    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m2 = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_metadata) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_name","Tiles"});
    std::optional<mbtiles::Metadatum> m1 = mbtiles.getMetadatum("alt_name");
    EXPECT_TRUE(m1.has_value());

    mbtiles.addMetadatum(mbtiles::Metadatum{"alt_description","A set of tiles"});
    std::optional<mbtiles::Metadatum> m2 = mbtiles.getMetadatum("alt_description");
    EXPECT_TRUE(m2.has_value());

    std::map<std::string,std::string> metadata = mbtiles.getMetadata();
    EXPECT_FALSE(metadata.empty());
    EXPECT_EQ("Tiles", metadata["alt_name"]);
    EXPECT_EQ("A set of tiles", metadata["alt_description"]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Tiles

TEST(MBTilesLibTests, tile_str) {
    mbtiles::Tile t{0,1,2};
    std::stringstream str;
    str << t;
    EXPECT_EQ("TILE (0, 1, 2)", str.str());
}

TEST(MBTilesLibTests, mbtiles_add_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getTile(0,1,2));
    mbtiles.addTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_set_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getTile(0,1,2));
    mbtiles.setTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));
    EXPECT_EQ(1, mbtiles.countTiles(0));

    mbtiles.setTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));
    EXPECT_EQ(1, mbtiles.countTiles(0));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_add_tile_file) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addMetadatum(mbtiles::Metadatum{"name","world"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"version","1.0"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"description","The world"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"attribution","Create with MBTilesCpp"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"type","base_layer"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"format","jpeg"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"bounds","-179.99,-85.0511,179.99,85.0511"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"minzoom","0"});
    mbtiles.addMetadatum(mbtiles::Metadatum{"maxzoom","1"});

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));
    
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_update_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getTile(0,1,2));
    mbtiles.addTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));

    mbtiles.updateTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c','e','f','g'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_delete_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getTile(0,1,2));
    mbtiles.addTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));

    mbtiles.deleteTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{}});  
    EXPECT_FALSE(mbtiles.getTile(0,1,2));    

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getTile(0,1,2));
    mbtiles.addTile(mbtiles::Tile{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getTile(0,1,2));
    EXPECT_EQ(0, mbtiles.getTile(0,1,2).value().zoom);
    EXPECT_EQ(1, mbtiles.getTile(0,1,2).value().column);
    EXPECT_EQ(2, mbtiles.getTile(0,1,2).value().row);
    EXPECT_EQ('a', mbtiles.getTile(0,1,2).value().data[0]);
    EXPECT_EQ('b', mbtiles.getTile(0,1,2).value().data[1]);
    EXPECT_EQ('c', mbtiles.getTile(0,1,2).value().data[2]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_tile_for_zoom) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    int counter = 0;    
    mbtiles.tiles(1, [&](mbtiles::Tile& t) {
        counter++;
    });
    EXPECT_EQ(4, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_save_tile) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    
    const std::string imageFileName = "0.jpeg";
    mbtiles.getTile(0,0,0)->save(imageFileName);
    
    std::ifstream imageFile(imageFileName);
    EXPECT_TRUE(imageFile.good());
    EXPECT_TRUE(std::filesystem::remove(imageFileName));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Grid

TEST(MBTilesLibTests, grid_str) {
    mbtiles::Grid g{0,1,2};
    std::stringstream str;
    str << g;
    EXPECT_EQ("GRID (0, 1, 2)", str.str());
}

TEST(MBTilesLibTests, mbtiles_add_grid) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGrid(0,1,2));
    mbtiles.addGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_set_grid) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGrid(0,1,2));
    mbtiles.setGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));

    mbtiles.setGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_update_grid) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGrid(0,1,2));
    mbtiles.addGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));
    EXPECT_EQ('a', mbtiles.getGrid(0,1,2).value().data[0]);
    mbtiles.updateGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'d','e','f'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));
    EXPECT_EQ('d', mbtiles.getGrid(0,1,2).value().data[0]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_delete_grid) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGrid(0,1,2));
    mbtiles.addGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));
    mbtiles.deleteGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{}});
    EXPECT_FALSE(mbtiles.getGrid(0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_grid) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGrid(0,1,2));
    mbtiles.addGrid(mbtiles::Grid{0,1,2,std::vector<mbtiles::byte>{'a','b','c'}});
    EXPECT_TRUE(mbtiles.getGrid(0,1,2));
    EXPECT_EQ(0, mbtiles.getGrid(0,1,2).value().zoom);
    EXPECT_EQ(1, mbtiles.getGrid(0,1,2).value().column);
    EXPECT_EQ(2, mbtiles.getGrid(0,1,2).value().row);
    EXPECT_EQ('a', mbtiles.getGrid(0,1,2).value().data[0]);
    EXPECT_EQ('b', mbtiles.getGrid(0,1,2).value().data[1]);
    EXPECT_EQ('c', mbtiles.getGrid(0,1,2).value().data[2]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_grids_for_zoom) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addGrid(mbtiles::Grid{1,0,0,std::vector<mbtiles::byte>{'a','b','c'}});
    mbtiles.addGrid(mbtiles::Grid{1,0,1,std::vector<mbtiles::byte>{'a','b','c'}});
    mbtiles.addGrid(mbtiles::Grid{1,1,0,std::vector<mbtiles::byte>{'a','b','c'}});
    mbtiles.addGrid(mbtiles::Grid{1,1,1,std::vector<mbtiles::byte>{'a','b','c'}});

    int counter = 0;    
    mbtiles.grids(1, [&](mbtiles::Grid& t) {
        counter++;
    });
    EXPECT_EQ(4, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_grids_save) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    mbtiles.addGrid(mbtiles::Grid{1,0,0,std::vector<mbtiles::byte>{'a','b','c'}});

    const std::string dataFileName = "file.dat";
    mbtiles.getGrid(1,0,0)->save(dataFileName);
    
    std::ifstream dataFile(dataFileName);
    EXPECT_TRUE(dataFile.good());
    EXPECT_TRUE(std::filesystem::remove(dataFileName));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Grid Data

TEST(MBTilesLibTests, griddata_str) {
    mbtiles::GridData g{0,1,2,"name","[1,2,3]"};
    std::stringstream str;
    str << g;
    EXPECT_EQ("GRIDDATA (0, 1, 2, name = [1,2,3])", str.str());
}

TEST(MBTilesLibTests, mbtiles_add_grid_data) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_set_grid_data) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.setGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.setGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_update_grid_data) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));
    EXPECT_EQ("[1,2,3]",mbtiles.getGridData(0,1,2,"name").value().json);

    mbtiles.updateGridData(mbtiles::GridData{0,1,2,"name","[4,5,6]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));
    EXPECT_EQ("[4,5,6]",mbtiles.getGridData(0,1,2,"name").value().json);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}


TEST(MBTilesLibTests, mbtiles_delete_grid_data) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.deleteGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));    

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_grid_data) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    EXPECT_TRUE(mbtiles.getGridData(0,1,2,"name"));
    EXPECT_EQ(0, mbtiles.getGridData(0,1,2,"name").value().zoom);
    EXPECT_EQ(1, mbtiles.getGridData(0,1,2,"name").value().column);
    EXPECT_EQ(2, mbtiles.getGridData(0,1,2,"name").value().row);
    EXPECT_EQ("name", mbtiles.getGridData(0,1,2,"name").value().name);
    EXPECT_EQ("[1,2,3]", mbtiles.getGridData(0,1,2,"name").value().json);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesLibTests, mbtiles_get_grid_data_map) {
    const std::string fileName = "tiles.mbtiles";
    mbtiles::MBTiles mbtiles { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    EXPECT_FALSE(mbtiles.getGridData(0,1,2,"name"));
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"name","[1,2,3]"});
    mbtiles.addGridData(mbtiles::GridData{0,1,2,"description","[4,5,6]"});
    std::map<std::string,std::string> data = mbtiles.getGridData(0,1,2);
    EXPECT_EQ("[1,2,3]", data["name"]);
    EXPECT_EQ("[4,5,6]", data["description"]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}