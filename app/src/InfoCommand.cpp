    #include "InfoCommand.hpp"

InfoCommand::InfoCommand(CLI::App* app): Command ("info") {
    CLI::App* cmd = app->add_subcommand("info", "Get info on a MBTiles file");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void InfoCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::map<std::string,std::string> metadata = mbtiles.getMetadata();
    ostream << "Metadata" << "\n";
    for(const auto  &metadatum : metadata) {
        ostream << metadatum.first << " = " << metadatum.second << "\n";
    }
    ostream << "\n" << "Tiles" << "\n";
    for(int z = mbtiles.getMinZoom(); z <= mbtiles.getMaxZoom(); ++z) {
        ostream << z << " = " << mbtiles.countTiles(z) << "\n";    
    }
}