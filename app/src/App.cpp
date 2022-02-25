#include <iostream>
#include "CLI/CLI.hpp"
#include "Commands.hpp"
#include "Command.hpp"
#include "ListCommand.hpp"
#include "CreateCommand.hpp"
#include "ExportCommand.hpp"
#include "ImportCommand.hpp"
#include "InfoCommand.hpp"

int main(int argc, char *argv[]) {

    CLI::App app{"MBTiles CLI"};
    app.require_subcommand(1);

    Commands commands;
    
    ListCommand listCommand(&app, &commands);
    commands.add(&listCommand);
    
    CreateCommand createCommand(&app);
    commands.add(&createCommand);
    
    ExportCommand exportCommand(&app);
    commands.add(&exportCommand);
    
    ImportCommand importCommand(&app);
    commands.add(&importCommand);

    InfoCommand infoCommand(&app);
    commands.add(&infoCommand);

    CLI11_PARSE(app, argc, argv);

    for(Command* cmd : commands.get()) {
      if (app.got_subcommand(cmd->getName())) {
        cmd->execute(std::cin, std::cout);
        break;
      }
    }

    return 0;

}