#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridDataGetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string name;
};

class GridDataGetCommand : public Command {

    public:

        GridDataGetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridDataGetOptions options;

};