#include "Command.h"
#include "../../files/factory/serializerFactory.h"

namespace cmd {
    bool Open::execute(std::ostream& output) {
        auto& deserializer = file::SerializationFactory::createDefaultFactory();
        std::shared_ptr<doc::Ppt> loadedPpt = deserializer.loadFromFile(file_path);
        
        if (!loadedPpt) {  // ✅ Fixed semicolon
            output << "Failed to open file " << file_path << "\n";
            return false;
        }
        
        editor->set_file(loadedPpt);  // ✅ Update editor's ppt pointer
        
        output << "File " << file_path << " successfully opened!\n";
        return true;
    }
}