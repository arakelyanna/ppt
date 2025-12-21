#include "CmdCreator.h"

namespace cmd{

    SetCurrentSlideCreator::SetCurrentSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) { 
        options = {
            {"to", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> SetCurrentSlideCreator::create() {
        auto val = std::get_if<int>(&options["to"].val);
        if(val)
            return std::make_unique<SetCurrentSlide>(ppt, *val);
        throw std::runtime_error("(command) ERROR: Slide position (id) not valid or not specified");
    }
}