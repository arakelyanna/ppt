#include "Command.h"

namespace cmd {
    bool AddText::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::AddObjectAction>(text);
        editor->carry_out(pAct);
        output << "Text successfully added!\n";
        return true;
    }
}