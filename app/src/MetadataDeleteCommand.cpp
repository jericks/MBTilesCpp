#include "MetadataDeleteCommand.hpp"

MetadataDeleteCommand::MetadataDeleteCommand(CLI::App* app): Command ("metadata-delete") {
    CLI::App* cmd = app->add_subcommand("metadata-delete", "Delete a metadatum by name");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void MetadataDeleteCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    auto metadatum = mbtiles.getMetadatum(options.name);
    if (metadatum) {
        mbtiles.deleteMetadatum(metadatum.value());
    }
}