#include "Command.h"
#include "../../files/factory/serializerFactory.h"

namespace cmd {
    bool Save::execute(std::ostream& output) {
        auto currentPpt = editor->get_doc();
        
        if (!currentPpt) {
            output << "Error: No presentation to save!\n";
            return false;
        }
        
        auto& factory = file::SerializationFactory::createDefaultFactory();
        
        if (factory.saveToFile(currentPpt, file_path)) {
            output << "File successfully saved in " << file_path << "!\n";
        } else {
            throw std::runtime_error("(command) ERROR: Failed to save file!\n");
        }
        
        return true;
    }
}