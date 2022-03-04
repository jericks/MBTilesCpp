#include "GridDataGetCommand.hpp"

GridDataGetCommand::GridDataGetCommand(CLI::App* app): Command ("griddata-get") {
    CLI::App* cmd = app->add_subcommand("griddata-get", "Get grid data");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-n", options.name, "Name");
}

void GridDataGetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    if (options.name.empty()) {
        std::map<std::string,std::string> gridData = mbtiles.getGridData(options.zoom, options.column, options.row);
        for(const auto  &gridDatum : gridData) {
            ostream << gridDatum.first << " = " << gridDatum.second << "\n";
        }    
    } else {
        std::optional<mbtiles::GridData> gridData = mbtiles.getGridData(options.zoom, options.column, options.row, options.name);
        if (gridData) {
            ostream << gridData->json;
        }   
    }
}