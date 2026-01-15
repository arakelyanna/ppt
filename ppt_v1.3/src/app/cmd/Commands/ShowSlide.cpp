#include <stdexcept>
#include "../../files/printer/printer_visitor/PrinterVisitor.h"
#include "Command.h"

namespace cmd {
    bool ShowSlide::execute(std::ostream& output) {
        out::CLIPrinterVisitor printer(editor->get_doc(), output);
        printer.visitSlide(pos);
        return true;
    }

}