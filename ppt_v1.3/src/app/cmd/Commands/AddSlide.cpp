#include <stdexcept>
#include "Command.h"

namespace cmd {
    bool AddSlide::execute(std::ostream& output) {
        std::shared_ptr<doc::IAction> pAct = std::make_shared<doc::AddSlideAction>(slide, pos);
        editor->carry_out(pAct);
        output << "Slide successfully added at " << pos << '\n';
        return true;
    }
}