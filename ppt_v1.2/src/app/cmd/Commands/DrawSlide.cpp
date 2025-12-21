#include <stdexcept>
#include "Command.h"
#include "../../printer/Visitor/Visitor.h"

namespace cmd {
    bool DrawSlide::execute(std::ostream& output) {
        out::SVGPrinterVisitor printer(editor->get_doc());
        printer.printSlide(pos);
        return true;
    }
}
