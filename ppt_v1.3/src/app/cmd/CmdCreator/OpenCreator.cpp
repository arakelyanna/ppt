#include "CmdCreator.h"

namespace cmd{
    OpenCreator::OpenCreator(std::shared_ptr<doc::Ppt> ppt) : I_CmdCreator(ppt) {
        options={
            {"file", true}
        };
    }

    std::unique_ptr<I_Command> OpenCreator::create() {
        auto val = std::get_if<std::string>(&options["file"].val);
        if(val)
            return std::make_unique<Open>(ppt, *val);
        else throw std::runtime_error("(command) ERROR: The file is not specified.");
        
    }
}