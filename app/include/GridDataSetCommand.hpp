#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridDataSetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string name;
        std::string json;
};

class GridDataSetCommand : public Command {

    public:

        GridDataSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridDataSetOptions options;

};