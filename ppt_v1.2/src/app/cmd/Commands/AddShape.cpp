#include "../Command.h"

namespace cmd {
    void AddShape::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }
    
    bool AddShape::execute() {
        ppt.add_object(std::move(shape));
        return true;

    }

    void AddShape::build() {
        shape = builder.build_shape();
    }
}