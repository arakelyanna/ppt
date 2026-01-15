#include "Command.h"

namespace cmd {
    bool RemoveSlide::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::RemoveSlideAction>(pos);
        editor->carry_out(pAct);
        output << "Slide at " << pos << " successfully removed!\n";

        return true;
    }
}