#include "CmdCreator.h"

namespace cmd {

    ShowFileCreator::ShowFileCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) { }

    std::unique_ptr<I_Command> ShowFileCreator::create() {
        return std::make_unique<ShowFile>(ppt);
    }

}