#include "CmdCreator.h"

namespace cmd{

    UndoCreator::UndoCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {}

    std::unique_ptr<I_Command> UndoCreator::create() {
        return std::make_unique<Undo>(ppt);
        
    }
}