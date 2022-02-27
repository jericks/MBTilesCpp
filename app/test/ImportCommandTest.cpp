#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "ImportCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, import_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  ImportCommand importCommand{&app};
  commands.add(&importCommand);

  int argc = 6;
  char const *argv[6] = {"mbtiles-cli", "import", "-f", fileName.c_str(), "-d", "../../../data/tms"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  importCommand.execute(instream, outstream);
  EXPECT_TRUE(mbtiles.getTile(0,0,0));
  EXPECT_TRUE(mbtiles.getTile(1,1,1));

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}