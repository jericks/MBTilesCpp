#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class GridGetOptions {
    public:
        std::string fileName;
        int zoom;
        int column;
        int row;
        std::string outFileName;
};

class GridGetCommand : public Command {

    public:

        GridGetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GridGetOptions options;

};