#include <stdexcept>
#include "Command.h"
#include "../../printer/Visitor/Visitor.h"

namespace cmd {
    bool CurrentSlide::execute(std::ostream& output) {
        auto currDoc = editor->get_doc();
        out::CLIPrinterVisitor printer(currDoc, output);
        printer.printSlide(currDoc->get_current());
        return true;
    }
}
