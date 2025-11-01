#include "../Command.h"

namespace cmd {
    void AddPicture::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }
    
    bool AddPicture::execute() {
        ppt.add_object(std::make_unique<obj::Picture>(std::move(pic)));
        return true;
    }

    void AddPicture::build() {
        pic = builder.build_picture();
    }
}