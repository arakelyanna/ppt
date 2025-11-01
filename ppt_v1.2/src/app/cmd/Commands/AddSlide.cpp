#include <stdexcept>
#include "../Command.h"

namespace cmd {

    void AddSlide::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool AddSlide::execute() {
        if (pos > ppt.size()) 
            throw std::runtime_error("ERROR: Invalid position " + std::to_string(pos));
        ppt.add_slide(slide, pos);
        return true;

    }

    void AddSlide::build() {
        pos = builder.build_slide_command();
    }
}