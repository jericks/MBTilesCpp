#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"

class MetadataDeleteOptions {
    public:
        std::string fileName;
        std::string name;
};

class MetadataDeleteCommand : public Command {

    public:

        MetadataDeleteCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        MetadataDeleteOptions options;

};