#include "CmdCreator.h"

namespace cmd {

    ExitCreator::ExitCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        // No options needed
    }

    std::unique_ptr<I_Command> ExitCreator::create() {
        return std::make_unique<Exit>(ppt);
    }

}