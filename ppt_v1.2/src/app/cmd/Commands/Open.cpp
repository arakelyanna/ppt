#include <stdexcept>
#include <fstream>
#include "../Command.h"

namespace cmd {
    void Open::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }
    
    bool Open::execute() {
        std::fstream file(file_path);
        if (!file) {
            throw std::runtime_error("ERROR: Invalid file path, or the file doesn't exist!");
        }
        else {
            ppt.open(file_path);
        }
        return true;
    }
    
    void Open::build() {
        file_path = builder.build_file();
    }
}