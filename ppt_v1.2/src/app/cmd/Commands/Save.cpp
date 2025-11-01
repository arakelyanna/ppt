#include "../Command.h"

namespace cmd {
    void Save::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool Save::execute() {
        std::fstream file(file_path);
        if (!file) {
            throw std::runtime_error("ERROR: Invalid file path!");
        }
        else 
            ppt.save(file_path);
        return true;
    }

    void Save::build() {
        file_path = builder.build_file();
    }
}
