#include <stdexcept>
#include "Command.h"
#include "../../files/printer/printer_visitor/PrinterVisitor.h"

namespace cmd {
    bool CurrentSlide::execute(std::ostream& output) {
        auto currDoc = editor->get_doc();
        out::CLIPrinterVisitor printer(currDoc, output);
        printer.visitSlide(currDoc->get_current());
        return true;
    }
}
