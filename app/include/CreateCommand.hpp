#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "MBTiles.hpp"


class CreateOptions {
    public:
        std::string fileName;
        std::string name;
        std::string version;
        std::string description;
        std::string attribution;
        std::string type;
        std::string format;
        std::string bounds;
        std::string minzoom;
        std::string maxzoom;
};

class CreateCommand : public Command {

    public:

        CreateCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateOptions options;

};