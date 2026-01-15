#include "Command.h"

namespace cmd {
    bool Undo::execute(std::ostream& output) {
        editor->undo();
        return true;
    }

}
