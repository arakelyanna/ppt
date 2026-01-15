#include "Command.h"
#include "../../files/doc_handling/Deserializer/Deserializer.h"

namespace cmd {
    bool Open::execute(std::ostream& output) {

        try {
            auto deserializer = files::JSONDeserializer(filename);
            editor->set_file(deserializer.open()); 
            
            output << "File " << filename << " successfully opened!\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        return true;
    }
}