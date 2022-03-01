#include "TileSetCommand.hpp"

TileSetCommand::TileSetCommand(CLI::App* app): Command ("tile-set") {
    CLI::App* cmd = app->add_subcommand("tile-set", "Add or Update a Tile");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-i", options.inputFileName, "Input file name")->required();
}

void TileSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    mbtiles.setTile(mbtiles::Tile{options.zoom, options.column, options.row, options.inputFileName});
}