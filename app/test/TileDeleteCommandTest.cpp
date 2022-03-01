#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "TileDeleteCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, tile_delete_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
  EXPECT_TRUE(mbtiles.getTile(0,0,0));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  TileDeleteCommand tileDeleteCommand{&app};
  commands.add(&tileDeleteCommand);

  int argc = 10;
  char const *argv[10] = {"mbtiles-cli", "tile-delete", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  tileDeleteCommand.execute(instream, outstream);
  EXPECT_FALSE(mbtiles.getTile(0,0,0));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}