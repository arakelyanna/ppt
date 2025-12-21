#include <stdexcept>
#include "Command.h"
#include "../../printer/Visitor/Visitor.h"

namespace cmd {
    bool SetCurrentSlide::execute(std::ostream& output) {
        editor->get_doc()->set_current(pos);
        output<<"Current slide changed to " << pos << '\n';
        return true;
    }
}
