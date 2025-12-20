#include "CmdCreator.h"

namespace cmd{

    SaveCreator::SaveCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"file", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> SaveCreator::create() {
        auto val = std::get_if<std::string>(&options["file"].val);
        if(val)
            return std::make_unique<Save>(ppt, *val);
        return std::make_unique<Save>(ppt);
        
    }
}