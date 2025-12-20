#include "Command.h"

namespace cmd {
    bool Redo::execute(std::ostream& output) {
        editor->redo();
        return true;
    }

}
