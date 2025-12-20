#include <stdexcept>
#include "CmdRegister.h"

namespace cmd {
    std::unique_ptr<I_CmdCreator> CmdRegister::get(const std::string& command_name) const {
        auto it = commands.find(command_name);
        if (it != commands.end())
            return it->second();
        return nullptr;
    }

    std::string CmdRegister::find(const std::string& command_name) const {
        auto it = commands.find(command_name);
        if (it != commands.end())
            return "is";
        
        for (const auto& [key, creator] : commands) {
            if (key.starts_with(command_name)) {
                return "starts_with";
            }
        }
        
        throw std::runtime_error("(command) ERROR: Invalid command " + command_name + "\n");
        return "not found";
    }
}
