#include <stdexcept>
#include "Command.h"

namespace cmd {
    bool ShowFile::execute(std::ostream& output) {
        return true;
    }
}
