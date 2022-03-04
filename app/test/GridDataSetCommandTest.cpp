#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridDataSetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, griddata_set_update_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGridData(mbtiles::GridData{0,0,0,"values","[1,2,3]"});
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDataSetCommand gridDataSetCommand{&app};
  commands.add(&gridDataSetCommand);

  int argc = 14;
  char const *argv[14] = {"mbtiles-cli", "griddata-set", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-n", "values", "-j", "[1,2,3,4,5]"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  gridDataSetCommand.execute(instream, outstream);

  EXPECT_EQ("[1,2,3,4,5]", mbtiles.getGridData(0,0,0,"values")->json);

  EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesCliTests, griddata_set_add_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDataSetCommand gridDataSetCommand{&app};
  commands.add(&gridDataSetCommand);

  int argc = 14;
  char const *argv[14] = {"mbtiles-cli", "griddata-set", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-n", "values", "-j", "[1,2,3,4,5]"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  gridDataSetCommand.execute(instream, outstream);

  EXPECT_EQ("[1,2,3,4,5]", mbtiles.getGridData(0,0,0,"values")->json);

  EXPECT_TRUE(std::filesystem::remove(fileName));
}