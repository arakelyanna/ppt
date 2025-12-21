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
        bool exact_match = commands.find(command_name) != commands.end();
        bool has_longer = false;
        
        // Check if there are longer commands starting with this prefix
        for (const auto& [key, creator] : commands) {
            if (key.starts_with(command_name) && key.length() > command_name.length()) {
                has_longer = true;
                break;
            }
        }
        
        if (has_longer) {
            return "starts_with";
        }
        
        if (exact_match) {
            return "is";
        }
        
        throw std::runtime_error("(command) ERROR: Invalid command " + command_name + "\n");
    }
}
