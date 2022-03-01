#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "TileGetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, tile_get_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  TileGetCommand tileGetCommand{&app};
  commands.add(&tileGetCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "tile-get", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-o", "0.jpeg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  tileGetCommand.execute(instream, outstream);
  EXPECT_TRUE(std::filesystem::exists("0.jpeg"));
  EXPECT_TRUE(std::filesystem::remove(fileName));
}