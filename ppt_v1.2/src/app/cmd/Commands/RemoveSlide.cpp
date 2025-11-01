#include <stdexcept>
#include "../Command.h"

namespace cmd {
   
    void RemoveSlide::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool RemoveSlide::execute() {
        if (pos > ppt.size()) 
            throw std::runtime_error("ERROR: Invalid position " + std::to_string(pos));
        ppt.remove_slide(pos);
        return true;

    }

    void RemoveSlide::build() {
        pos = builder.build_slide_command();
    }
    
}