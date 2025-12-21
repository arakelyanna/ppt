#include <stdexcept>
#include "Command.h"

namespace cmd {
    bool ShowSlide::execute(std::ostream& output) {
        out::CLIPrinterVisitor printer(editor->get_doc(), output);
        printer.printSlide(pos);
        return true;
    }

}