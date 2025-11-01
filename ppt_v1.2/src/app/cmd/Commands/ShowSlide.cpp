#include <stdexcept>
#include "../Command.h"

namespace cmd {
    ShowSlide::ShowSlide() : pos(ppt.size() - 1) {}
    
    void ShowSlide::set(const std::string& key, const Value& val) {
        builder.set(key, val);
    }

    bool ShowSlide::execute() {
        if (pos > ppt.size()) 
            throw std::runtime_error("ERROR: Invalid position " + std::to_string(pos));
        view::I_Viewer::create(viewer_type)->show_slide(ppt, pos);
        return true;

    }

    
    void ShowSlide::build() {
        pos = builder.build_slide_command();
    }

}