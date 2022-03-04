#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridDataDeleteCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, griddata_delete_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGridData(mbtiles::GridData{0,0,0,"values","[1,2,3]"});
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDataDeleteCommand gridDataDeleteCommand{&app};
  commands.add(&gridDataDeleteCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "griddata-delete", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-n", "values"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  gridDataDeleteCommand.execute(instream, outstream);

  EXPECT_FALSE(mbtiles.getGridData(0,0,0,"values"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}