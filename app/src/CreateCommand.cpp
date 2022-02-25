#include "CreateCommand.hpp"

CreateCommand::CreateCommand(CLI::App* app): Command ("create") {
    CLI::App* cmd = app->add_subcommand("create", "Create an empty MBTiles file");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void CreateCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTilesOptions mbtilesOptions{};
    mbtiles::MBTiles mbtiles {options.fileName, mbtilesOptions};
}