#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

namespace cmd {
    class I_Command;

    class CmdFactory {
    public:
        std::unique_ptr<I_Command> create(const std::string& command_name);
    };
}