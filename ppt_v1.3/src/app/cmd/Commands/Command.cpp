#include "Command.h"

namespace cmd{
    I_Command::I_Command(std::shared_ptr<doc::Ppt> ppt) {
        if(!editor) {
            editor = std::make_shared<doc::Editor>(ppt);
        }
    }

    std::shared_ptr<doc::Editor> I_Command::editor;
}