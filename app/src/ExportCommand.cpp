#include "ExportCommand.hpp"

ExportCommand::ExportCommand(CLI::App* app): Command ("export") {
    CLI::App* cmd = app->add_subcommand("export", "Export an MBTIles tiles to a directory");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-d", options.directory, "Directory")->required();
}

void ExportCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTilesOptions mbtilesOptions{};
    mbtiles::MBTiles mbtiles {options.fileName, mbtilesOptions};
    mbtiles.exportToDirectory(options.directory);
}