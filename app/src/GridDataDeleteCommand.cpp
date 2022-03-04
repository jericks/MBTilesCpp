#include "GridDataDeleteCommand.hpp"

GridDataDeleteCommand::GridDataDeleteCommand(CLI::App* app): Command ("griddata-delete") {
    CLI::App* cmd = app->add_subcommand("griddata-delete", "Delete grid data");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void GridDataDeleteCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::optional<mbtiles::GridData> gridData = mbtiles.getGridData(options.zoom, options.column, options.row, options.name);
    if (gridData) {
        mbtiles.deleteGridData(gridData.value());
    }   
}