#include "CreateCommand.hpp"

CreateCommand::CreateCommand(CLI::App* app): Command ("create") {
    CLI::App* cmd = app->add_subcommand("create", "Create an empty MBTiles file");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("--name", options.name, "Name");
    cmd->add_option("--version", options.version, "Version");
    cmd->add_option("--description", options.description, "Description");
    cmd->add_option("--attribution", options.attribution, "Attribution");
    cmd->add_option("--type", options.type, "Type");
    cmd->add_option("--format", options.format, "Format");
    cmd->add_option("--bounds", options.bounds, "Bounds");
    cmd->add_option("--minZoom", options.minzoom, "Min Zoom");
    cmd->add_option("--maxZoom", options.maxzoom, "Max Zoom");
}

void CreateCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTilesOptions mbtilesOptions{};
    if (!options.name.empty()) {
        mbtilesOptions.name = options.name;
    }
    if (!options.version.empty()) {
        mbtilesOptions.version = options.version;
    }
    if (!options.description.empty()) {
        mbtilesOptions.description = options.description;
    }
    if (!options.attribution.empty()) {
        mbtilesOptions.attribution = options.attribution;
    }
    if (!options.type.empty()) {
        mbtilesOptions.type = options.type;
    }
    if (!options.format.empty()) {
        mbtilesOptions.format = options.format;
    }
    if (!options.bounds.empty()) {
        mbtilesOptions.bounds = options.bounds;
    }
    if (!options.minzoom.empty()) {
        mbtilesOptions.minzoom = options.minzoom;
    }
    if (!options.maxzoom.empty()) {
        mbtilesOptions.maxzoom = options.maxzoom;
    }
    mbtiles::MBTiles mbtiles {options.fileName, mbtilesOptions};
}