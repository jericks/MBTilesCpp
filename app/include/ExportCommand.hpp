#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class ExportOptions {
    public:
        std::string fileName;
        std::string directory;
};

class ExportCommand : public Command {

    public:

        ExportCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ExportOptions options;

};