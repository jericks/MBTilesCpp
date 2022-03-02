#include "MetadataGetCommand.hpp"

MetadataGetCommand::MetadataGetCommand(CLI::App* app): Command ("metadata-get") {
    CLI::App* cmd = app->add_subcommand("metadata-get", "Get a metadatum by name");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void MetadataGetCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    auto metadatum = mbtiles.getMetadatum(options.name);
    if (metadatum) {
        ostream << metadatum->value << "\n";
    }
}