#include "GridDeleteCommand.hpp"

GridDeleteCommand::GridDeleteCommand(CLI::App* app): Command ("grid-delete") {
    CLI::App* cmd = app->add_subcommand("grid-delete", "Delete a Grid");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
}

void GridDeleteCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::optional<mbtiles::Grid> grid = mbtiles.getGrid(options.zoom, options.column, options.row);
    if (grid) {
        mbtiles.deleteGrid(grid.value());
    }
}