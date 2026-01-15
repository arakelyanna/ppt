#include "Command.h"

namespace cmd {
    bool AddPicture::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::AddObjectAction>(pic);
        editor->carry_out(pAct);
        output << "Picture successfully added!\n";
        return true;
    }

}