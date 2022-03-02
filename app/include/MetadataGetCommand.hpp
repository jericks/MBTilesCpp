#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"

class MetadataGetOptions {
    public:
        std::string fileName;
        std::string name;
};

class MetadataGetCommand : public Command {

    public:

        MetadataGetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        MetadataGetOptions options;

};