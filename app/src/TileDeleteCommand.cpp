#include "TileDeleteCommand.hpp"

TileDeleteCommand::TileDeleteCommand(CLI::App* app): Command ("tile-delete") {
    CLI::App* cmd = app->add_subcommand("tile-delete", "Delete a Tile");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
}

void TileDeleteCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    mbtiles.deleteTile(mbtiles::Tile{options.zoom, options.column, options.row});
}