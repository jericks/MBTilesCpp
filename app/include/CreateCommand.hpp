#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class CreateOptions {
    public:
        std::string fileName;
};

class CreateCommand : public Command {

    public:

        CreateCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateOptions options;

};