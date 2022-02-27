#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "InfoCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, info_test) {
  
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
  InfoCommand infoCommand{&app};
  commands.add(&infoCommand);

  int argc = 4;
  char const *argv[4] = {"mbtiles-cli", "info", "-f", fileName.c_str()};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  infoCommand.execute(instream, outstream);
  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("Metadata"));
  ASSERT_NE(std::string::npos, result.find("Tiles"));

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}