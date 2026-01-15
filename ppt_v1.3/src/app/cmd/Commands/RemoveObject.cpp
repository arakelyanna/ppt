#include "Command.h"

namespace cmd {
    bool RemoveObject::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::RemoveObjectAction>(pos);
        editor->carry_out(pAct);
        output << "Object successfully removed!\n";

        return true;
    }
}