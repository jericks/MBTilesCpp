#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "ExportCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, export_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addTile(mbtiles::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
  mbtiles.addTile(mbtiles::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
  mbtiles.addTile(mbtiles::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
  mbtiles.addTile(mbtiles::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
  mbtiles.addTile(mbtiles::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  ExportCommand exportCommand{&app};
  commands.add(&exportCommand);

  int argc = 6;
  char const *argv[6] = {"mbtiles-cli", "export", "-f", fileName.c_str(), "-d", "tiles"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  exportCommand.execute(instream, outstream);
  EXPECT_TRUE(std::filesystem::exists("tiles/0/0/0.jpeg"));
  EXPECT_TRUE(std::filesystem::exists("tiles/1/1/1.jpeg"));

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}