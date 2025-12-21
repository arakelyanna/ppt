#include "CmdCreator.h"

namespace cmd{

    CurrentSlideCreator::CurrentSlideCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) { }

    std::unique_ptr<I_Command> CurrentSlideCreator::create() {
        return std::make_unique<CurrentSlide>(ppt);
    }
}