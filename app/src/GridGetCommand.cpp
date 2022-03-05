#include "GridGetCommand.hpp"

GridGetCommand::GridGetCommand(CLI::App* app): Command ("grid-get") {
    CLI::App* cmd = app->add_subcommand("grid-get", "Get a Grid");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-o", options.outFileName, "Output file")->required();
}

void GridGetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::optional<mbtiles::Grid> grid = mbtiles.getGrid(options.zoom, options.column, options.row);
    if (grid) {
        grid->save(options.outFileName);
    }
}