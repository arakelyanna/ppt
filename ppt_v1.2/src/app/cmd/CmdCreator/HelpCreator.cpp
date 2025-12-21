#include "CmdCreator.h"

namespace cmd{
    HelpCreator::HelpCreator(std::shared_ptr<doc::Ppt> ppt) : I_CmdCreator(ppt) {
        options={
            {"cmd", true}
        };
    }

    std::unique_ptr<I_Command> HelpCreator::create() {
        auto val = std::get_if<std::string>(&options["cmd"].val);
        if(val)
            return std::make_unique<Help>(ppt, *val);
        else return std::make_unique<Help>(ppt, "");
    }
}