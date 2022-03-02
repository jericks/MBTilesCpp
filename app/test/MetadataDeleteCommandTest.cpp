#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "MetadataDeleteCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, metadata_delete_test) {
  
  const std::string fileName = "world.mbtiles";
  mbtiles::MBTiles mbtiles { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  MetadataDeleteCommand metadataDeleteCommand{&app};
  commands.add(&metadataDeleteCommand);

  int argc = 6;
  char const *argv[6] = {"mbtiles-cli", "metadata-delete", "-f", fileName.c_str(), "-n", "version"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  metadataDeleteCommand.execute(instream, outstream);
  EXPECT_FALSE(mbtiles.getMetadatum("version"));

  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}