#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"

class MetadataListOptions {
    public:
        std::string fileName;
};

class MetadataListCommand : public Command {

    public:

        MetadataListCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        MetadataListOptions options;

};