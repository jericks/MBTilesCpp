#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"

class ImportOptions {
    public:
        std::string fileName;
        std::string directory;
};

class ImportCommand : public Command {

    public:

        ImportCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ImportOptions options;

};