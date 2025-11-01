#include "../Command.h"

namespace cmd {
    void Exit::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool Exit::execute() {
        std::cout << "Exitting...\n";
        return true;
    }
    
    void Exit::build() {}
}