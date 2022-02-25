#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class InfoOptions {
    public:
        std::string fileName;
};

class InfoCommand : public Command {

    public:

        InfoCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        InfoOptions options;

};