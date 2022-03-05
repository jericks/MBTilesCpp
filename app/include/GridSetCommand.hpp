#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridSetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string inputFileName;
};

class GridSetCommand : public Command {

    public:

        GridSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridSetOptions options;

};