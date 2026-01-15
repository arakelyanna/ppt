#include "CmdCreator.h"

namespace cmd{

    ShowSlideCreator::ShowSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"at", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> ShowSlideCreator::create() {
        auto val = std::get_if<int>(&options["at"].val);
        if(val)
            return std::make_unique<ShowSlide>(ppt, *val);
        else throw std::runtime_error("(command) ERROR: The slide position (id) is not specified.");
        
    }
}