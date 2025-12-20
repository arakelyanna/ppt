#include "CmdCreator.h"

namespace cmd{
    RemoveObjectCreator::RemoveObjectCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"at", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> RemoveObjectCreator::create() {
        auto pos = std::get_if<obj::Geometry>(&options.at("at").val);
        if(pos && (*pos).size()==1)
            return std::make_unique<RemoveObject>(ppt, (*pos)[0]);
        else return std::make_unique<RemoveObject>(ppt);
        
    }
}