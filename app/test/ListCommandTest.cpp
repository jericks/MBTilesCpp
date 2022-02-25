#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "ListCommand.hpp"
#include "gtest/gtest.h"

TEST(MBTilesCliTests, list_test) {
  
  CLI::App app{"MBTilesCpp CLI"};  

  Commands commands;
  ListCommand listCommand{&app, &commands};
  commands.add(&listCommand);

  int argc = 2;
  char const *argv[2] = {"mbtiles-cli", "list"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  listCommand.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("list"));
  ASSERT_EQ(std::string::npos, result.find("notacommand"));
}