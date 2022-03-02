#include "MetadataListCommand.hpp"

MetadataListCommand::MetadataListCommand(CLI::App* app): Command ("metadata-list") {
    CLI::App* cmd = app->add_subcommand("metadata-list", "List all metadata");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void MetadataListCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::map<std::string,std::string> metadata = mbtiles.getMetadata();
    for(const auto  &metadatum : metadata) {
        ostream << metadatum.first << " = " << metadatum.second << "\n";
    }
}