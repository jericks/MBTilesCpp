    #include "InfoCommand.hpp"

InfoCommand::InfoCommand(CLI::App* app): Command ("info") {
    CLI::App* cmd = app->add_subcommand("info", "Get info on a MBTiles file");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void InfoCommand::execute(std::istream& istream, std::ostream& ostream) {
    mbtiles::MBTiles mbtiles {options.fileName};
    std::map<std::string,std::string> metadata = mbtiles.getMetadata();
    std::cout << "Metadata" << "\n";
    for(const auto  &metadatum : metadata) {
        std::cout << metadatum.first << " = " << metadatum.second << "\n";
    }
    std::cout << "\n" << "Tiles" << "\n";
    for(int z = mbtiles.getMinZoom(); z <= mbtiles.getMaxZoom(); ++z) {
        std::cout << z << " = " << mbtiles.countTiles(z) << "\n";    
    }
}