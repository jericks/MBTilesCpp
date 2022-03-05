#include "GridSetCommand.hpp"

GridSetCommand::GridSetCommand(CLI::App* app): Command ("grid-set") {
    CLI::App* cmd = app->add_subcommand("grid-set", "Add or Update a Grid");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-i", options.inputFileName, "Input file name")->required();
}

void GridSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    mbtiles.setGrid(mbtiles::Grid{options.zoom, options.column, options.row, options.inputFileName});
}