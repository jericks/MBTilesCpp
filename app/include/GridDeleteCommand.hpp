#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridDeleteOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
};

class GridDeleteCommand : public Command {

    public:

        GridDeleteCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridDeleteOptions options;

};