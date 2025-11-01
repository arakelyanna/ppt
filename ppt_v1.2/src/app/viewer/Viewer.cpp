#include "Viewer.h"
#include "CLI_Viewer.h"

namespace view {
    std::unique_ptr<I_Viewer> I_Viewer::create(const std::string& type) {
        if (type == "cli") return std::make_unique<CLI_Viewer>();
        // if (type == "gui")  return std::make_unique<GUI_Viewer>();
        throw std::runtime_error("ERROR: Unsupported viewer!");
    }
}
