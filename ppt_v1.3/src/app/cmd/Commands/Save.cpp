#include "Command.h"
#include "../../files/doc_handling/Serializer/SerializerVisitor/SerializerVisitor.h"

namespace cmd {
    bool Save::execute(std::ostream& output) {
        auto currentPpt = editor->get_doc();
        
        if (!currentPpt) {
            output << "Error: No presentation to save!\n";
            return false;
        }
        
        auto serializer = files::JSONSerializerVisitor(currentPpt, filename);
        serializer.visit();

        output << filename << " successfully saved\n";
        return true;
    }
}