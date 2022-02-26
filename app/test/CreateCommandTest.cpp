#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "CreateCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, create_test) {
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  CreateCommand createCommand{&app};
  commands.add(&createCommand);

  int argc = 6;
  char const *argv[6] = {"mbtiles-cli", "create", "-f", "world.mbtiles", "--name", "World"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  createCommand.execute(instream, outstream);
  EXPECT_TRUE(std::filesystem::exists("world.mbtiles"));
  EXPECT_TRUE(std::filesystem::remove("world.mbtiles"));
}