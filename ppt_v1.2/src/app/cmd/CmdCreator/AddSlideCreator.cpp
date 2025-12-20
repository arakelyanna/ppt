#include "CmdCreator.h"

namespace cmd{
    AddSlideCreator::AddSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"at", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> AddSlideCreator::create() {
        auto slide = std::make_shared<doc::Slide>();
        auto val = std::get_if<int>(&options["at"].val);
        if(val)
            return std::make_unique<AddSlide>(ppt, slide, *val);
        else return std::make_unique<AddSlide>(ppt, slide);
        
    }
}