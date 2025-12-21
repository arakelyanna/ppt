#include "CmdCreator.h"

namespace cmd {

    DrawCreator::DrawCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) { }

    std::unique_ptr<I_Command> DrawCreator::create() {
        return std::make_unique<Draw>(ppt);
    }

}