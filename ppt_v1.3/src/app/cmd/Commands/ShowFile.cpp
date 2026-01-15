#include <stdexcept>
#include "Command.h"
#include "../../files/printer/printer_visitor/PrinterVisitor.h"

namespace cmd {
    bool ShowFile::execute(std::ostream& output) {
        out::CLIPrinterVisitor printer(editor->get_doc(), output);
        printer.visit();
        return true;
    }
}
