#include "GridDataSetCommand.hpp"

GridDataSetCommand::GridDataSetCommand(CLI::App* app): Command ("griddata-set") {
    CLI::App* cmd = app->add_subcommand("griddata-set", "Set grid data");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-n", options.name, "Name")->required();
    cmd->add_option("-j", options.json, "JSON")->required();
}

void GridDataSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    mbtiles.setGridData(mbtiles::GridData{options.zoom, options.column, options.row, options.name, options.json});
}