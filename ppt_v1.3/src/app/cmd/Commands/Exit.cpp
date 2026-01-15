#include "Command.h"

namespace cmd {
    bool Exit::execute(std::ostream& output) {
        std::cout << "Exitting...\n";
        return false;
    }
}