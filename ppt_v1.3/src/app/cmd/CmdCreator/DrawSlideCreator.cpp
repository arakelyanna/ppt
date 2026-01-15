#include "CmdCreator.h"

namespace cmd {

    DrawSlideCreator::DrawSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) { 
            options = {
                {"at", OptInfo(true)}
            };
        }

    std::unique_ptr<I_Command> DrawSlideCreator::create() {
        auto val = std::get_if<int>(&options["at"].val);
        if(val)
            return std::make_unique<DrawSlide>(ppt, *val);
        else throw std::runtime_error("(command) ERROR: The slide position (id) is not specified.");
    }

}