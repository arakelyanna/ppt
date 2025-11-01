#include <stdexcept>
#include "Command.h"
#include "CmdFactory.h"

namespace cmd {
    std::unique_ptr<I_Command> CmdFactory::create(const std::string& command_name) {
        static std::unordered_map<std::string, std::function<std::unique_ptr<I_Command>()>> commands = {
            {"add shape", [](){ return std::make_unique<AddShape>(); }},
            {"add slide", [](){ return std::make_unique<AddSlide>(); }},
            {"remove slide", [](){ return std::make_unique<AddSlide>(); }},
            {"add text", [](){ return std::make_unique<AddText>(); }},
            {"add picture", [](){ return std::make_unique<AddPicture>(); }},
            {"show slide", [](){ return std::make_unique<ShowSlide>(); }},
            {"show file", [](){ return std::make_unique<ShowFile>(); }},
            {"open", [](){ return std::make_unique<Open>(); }},
            {"save", [](){ return std::make_unique<Save>(); }},
            {"exit", [](){ return std::make_unique<Exit>(); }}
        };
        
        auto it = commands.find(command_name);
        if (it != commands.end())
            return it->second();
        else throw std::runtime_error("ERROR: Invalid command " + command_name);
    }
}