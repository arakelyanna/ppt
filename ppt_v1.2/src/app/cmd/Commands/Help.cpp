#include "Command.h"
#include "../MetaCmd/MetaCmd.h"

namespace cmd {
    bool Help::execute(std::ostream& output) {
        output << "======================== Help ========================\n";
        static MetaCmd meta_cmd;
        meta_cmd.showHelp(output, cmd_name);        
        output << "====================================================\n";
        return true;
    }

}
