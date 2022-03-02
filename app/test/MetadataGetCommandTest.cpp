#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "MetadataGetCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, metadata_get_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  MetadataGetCommand metadataGetCommand{&app};
  commands.add(&metadataGetCommand);

  int argc = 6;
  char const *argv[6] = {"mbtiles-cli", "metadata-get", "-f", fileName.c_str(), "-n", "version"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  metadataGetCommand.execute(instream, outstream);
  std::string result = outstream.str();
  ASSERT_EQ("1.0\n",result);

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}