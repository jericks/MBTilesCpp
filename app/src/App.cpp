#include <iostream>
#include "CLI/CLI.hpp"
#include "Commands.hpp"
#include "Command.hpp"
#include "ListCommand.hpp"
#include "CreateCommand.hpp"
#include "ExportCommand.hpp"
#include "ImportCommand.hpp"
#include "InfoCommand.hpp"
#include "TileGetCommand.hpp"
#include "TileSetCommand.hpp"
#include "TileDeleteCommand.hpp"
#include "MetadataListCommand.hpp"
#include "MetadataGetCommand.hpp"
#include "MetadataDeleteCommand.hpp"
#include "GridDataDeleteCommand.hpp"
#include "GridDataGetCommand.hpp"
#include "GridDataSetCommand.hpp"
#include "GridSetCommand.hpp"
#include "GridDeleteCommand.hpp"
#include "GridGetCommand.hpp"

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

    // Tile Commands

    TileGetCommand tileGetCommand(&app);
    commands.add(&tileGetCommand);

    TileSetCommand tileSetCommand(&app);
    commands.add(&tileSetCommand);

    TileDeleteCommand tileDeleteCommand(&app);
    commands.add(&tileDeleteCommand);

    // Metadata Commands

    MetadataListCommand metadataListCommand(&app);
    commands.add(&metadataListCommand);

    MetadataGetCommand metadataGetCommand(&app);
    commands.add(&metadataGetCommand);

    MetadataDeleteCommand metadataDeleteCommand(&app);
    commands.add(&metadataDeleteCommand);

    // Grid Data
    
    GridDataGetCommand gridDataGetCommand(&app);
    commands.add(&gridDataGetCommand);

    GridDataSetCommand gridDataSetCommand(&app);
    commands.add(&gridDataSetCommand);

    GridDataDeleteCommand gridDataDeleteCommand(&app);
    commands.add(&gridDataDeleteCommand);
    
    // Grid
    
    GridSetCommand gridSetCommand(&app);
    commands.add(&gridSetCommand);

    GridDeleteCommand gridDeleteCommand(&app);
    commands.add(&gridDeleteCommand);

    GridGetCommand gridGetCommand(&app);
    commands.add(&gridGetCommand);

    CLI11_PARSE(app, argc, argv);

    for(Command* cmd : commands.get()) {
      if (app.got_subcommand(cmd->getName())) {
        cmd->execute(std::cin, std::cout);
        break;
      }
    }

    return 0;

}