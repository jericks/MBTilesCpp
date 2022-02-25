#include "ImportCommand.hpp"

ImportCommand::ImportCommand(CLI::App* app): Command ("import") {
    CLI::App* cmd = app->add_subcommand("import", "Import a directory of tiles into an MBTiles file");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-d", options.directory, "Directory")->required();
}

void ImportCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTilesOptions mbtilesOptions{};
    mbtiles::MBTiles mbtiles {options.fileName, mbtilesOptions};
    mbtiles.loadFromDirectory(options.directory);
}