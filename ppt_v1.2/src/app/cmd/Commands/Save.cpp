#include "Command.h"
#include "../../files/factory/serializerFactory.h"

namespace cmd {
    bool Save::execute(std::ostream& output) {
        // Get the CURRENT ppt from editor, not the stored one
        auto currentPpt = editor->get_doc();
        
        if (!currentPpt) {
            output << "Error: No presentation to save!\n";
            return false;
        }
        
        auto& factory = file::SerializationFactory::createDefaultFactory();
        
        if (factory.saveToFile(currentPpt, file_path)) {
            output << "File successfully saved in " << file_path << "!\n";
        } else {
            output << "Failed to save file!\n";
        }
        
        return true;
    }
}