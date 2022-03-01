#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class TileGetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string outputFileName;
};

class TileGetCommand : public Command {

    public:

        TileGetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        TileGetOptions options;

};