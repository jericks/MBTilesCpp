#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "MetadataListCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, metadata_list_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  MetadataListCommand metadataListCommand{&app};
  commands.add(&metadataListCommand);

  int argc = 4;
  char const *argv[4] = {"mbtiles-cli", "metadata-list", "-f", fileName.c_str()};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  metadataListCommand.execute(instream, outstream);
  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("attribution = Create with MBTilesCpp"));
  ASSERT_NE(std::string::npos, result.find("version = 1.0"));

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}