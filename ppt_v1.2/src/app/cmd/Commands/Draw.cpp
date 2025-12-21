#include <stdexcept>
#include "Command.h"
#include "../../printer/Visitor/Visitor.h"

namespace cmd {
    bool Draw::execute(std::ostream& output) {
        out::SVGPrinterVisitor printer(editor->get_doc());
        printer.print();
        return true;
    }
}
