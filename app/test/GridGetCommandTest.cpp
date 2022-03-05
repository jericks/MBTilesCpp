#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridGetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, grid_get_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGrid(mbtiles::Grid{0,0,0,std::vector<mbtiles::byte>{'a','b','c'}});

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridGetCommand gridGetCommand{&app};
  commands.add(&gridGetCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "grid-get", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-o", "0.json"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  EXPECT_FALSE(std::filesystem::exists("0.json"));
  gridGetCommand.execute(instream, outstream);
  EXPECT_TRUE(std::filesystem::exists("0.json"));

  EXPECT_TRUE(std::filesystem::remove("0.json"));
  EXPECT_TRUE(std::filesystem::remove(fileName));
}