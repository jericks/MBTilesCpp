#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GridDataGetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, griddata_get_by_name_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGridData(mbtiles::GridData{0,0,0,"values","[1,2,3]"});
  mbtiles.addGridData(mbtiles::GridData{0,0,0,"config","{\"name\": \"value\"}"});
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDataGetCommand gridDataGetCommand{&app};
  commands.add(&gridDataGetCommand);

  int argc = 12;
  char const *argv[12] = {"mbtiles-cli", "griddata-get", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0", "-n", "config"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  gridDataGetCommand.execute(instream, outstream);
  EXPECT_EQ("{\"name\": \"value\"}", outstream.str());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(MBTilesCliTests, griddata_get_all_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  mbtiles.addGridData(mbtiles::GridData{0,0,0,"values","[1,2,3]"});
  mbtiles.addGridData(mbtiles::GridData{0,0,0,"config","{\"name\": \"value\"}"});
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  GridDataGetCommand gridDataGetCommand{&app};
  commands.add(&gridDataGetCommand);

  int argc = 10;
  char const *argv[10] = {"mbtiles-cli", "griddata-get", "-f", fileName.c_str(), "-z", "0", "-c", "0", "-r", "0"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  gridDataGetCommand.execute(instream, outstream);

  std::string result = outstream.str();
  EXPECT_NE(std::string::npos, result.find("config = {\"name\": \"value\"}"));
  EXPECT_NE(std::string::npos, result.find("values = [1,2,3]"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}