#include "CmdCreator.h"

namespace cmd{

    RedoCreator::RedoCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {}

    std::unique_ptr<I_Command> RedoCreator::create() {
        return std::make_unique<Redo>(ppt);
        
    }
}