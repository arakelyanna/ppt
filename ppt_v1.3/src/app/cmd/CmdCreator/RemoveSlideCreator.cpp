#include "CmdCreator.h"

namespace cmd{
    RemoveSlideCreator::RemoveSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"at", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> RemoveSlideCreator::create() {
        auto val = std::get_if<int>(&options["at"].val);
        if(val)
            return std::make_unique<RemoveSlide>(ppt, *val);
        else return std::make_unique<RemoveSlide>(ppt);
        
    }
}