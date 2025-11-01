#include <stdexcept>
#include "../Command.h"

namespace cmd {
    ShowFile::ShowFile() : pos(pos) {}
    
    void ShowFile::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool ShowFile::execute() {
        view::I_Viewer::create(viewer_type)->show(ppt);
        return true;

    }

    
    void ShowFile::build() { }
}