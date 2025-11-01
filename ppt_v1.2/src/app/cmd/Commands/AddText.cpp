#include "../Command.h"

namespace cmd {
    void AddText::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }
    
    bool AddText::execute() {
        ppt.add_object(std::make_unique<obj::Text>(std::move(*text)));
        return true;
    }

    void AddText::build() {
        text = builder.build_text();
    }
}