#include "Command.h"

namespace cmd {
    bool AddShape::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::AddObjectAction>(shape);
        editor->carry_out(pAct);
        output << "Shape successfully added!";
        return true;

    }
}