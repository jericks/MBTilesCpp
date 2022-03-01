#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "TileSetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, tile_set_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  TileSetCommand tileSetCommand{&app};
  commands.add(&tileSetCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "tile-set", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-i", "../../../data/tms/0/0/0.jpeg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  EXPECT_FALSE(mbtiles.getTile(0,0,0));
  tileSetCommand.execute(instream, outstream);
  EXPECT_TRUE(mbtiles.getTile(0,0,0));
  EXPECT_TRUE(std::filesystem::remove(fileName));
}