#include <stdexcept>
#include "Command.h"
// #include "../../files/doc_handling/"

namespace cmd {
    bool SetCurrentSlide::execute(std::ostream& output) {
        editor->get_doc()->set_current(pos);
        output<<"Current slide changed to " << pos << '\n';
        return true;
    }
}
