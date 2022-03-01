#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class TileDeleteOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
};

class TileDeleteCommand : public Command {

    public:

        TileDeleteCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        TileDeleteOptions options;

};