#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridDataDeleteOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string name;
};

class GridDataDeleteCommand : public Command {

    public:

        GridDataDeleteCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridDataDeleteOptions options;

};