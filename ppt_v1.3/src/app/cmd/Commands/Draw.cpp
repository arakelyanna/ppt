#include <stdexcept>
#include "Command.h"
#include "../../files/printer/printer_visitor/PrinterVisitor.h"

namespace cmd {
    bool Draw::execute(std::ostream& output) {
        out::SVGPrinterVisitor printer(editor->get_doc());
        printer.visit();
        return true;
    }
}
