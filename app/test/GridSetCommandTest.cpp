#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridSetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, grid_set_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridSetCommand gridSetCommand{&app};
  commands.add(&gridSetCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "grid-set", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-i", "../../../data/tms/0/0/0.jpeg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  EXPECT_FALSE(mbtiles.getGrid(0,0,0));
  gridSetCommand.execute(instream, outstream);
  EXPECT_TRUE(mbtiles.getGrid(0,0,0));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}