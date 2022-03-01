#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class TileSetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string inputFileName;
};

class TileSetCommand : public Command {

    public:

        TileSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        TileSetOptions options;

};