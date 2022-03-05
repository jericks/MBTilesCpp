#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridDeleteCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, grid_delete_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGrid(mbtiles::Grid{0,0,0,std::vector<mbtiles::byte>{'a','b','c'}});

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDeleteCommand gridDeleteCommand{&app};
  commands.add(&gridDeleteCommand);

  int argc = 10;
  char const *argv[10] = {"mbtiles-cli", "grid-delete", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  EXPECT_TRUE(mbtiles.getGrid(0,0,0));
  gridDeleteCommand.execute(instream, outstream);
  EXPECT_FALSE(mbtiles.getGrid(0,0,0));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}