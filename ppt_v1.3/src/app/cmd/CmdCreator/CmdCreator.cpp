#include "CmdCreator.h"

namespace cmd{
    void I_CmdCreator::set(const std::string key, const Value& val) {
        auto lookUp = options.find(key);
        if (lookUp != options.end())                
            options[key].val = val;
        else throw std::runtime_error("(command) ERROR: Invalid option " + key);
    }
    
    OptInfo I_CmdCreator::get(const std::string& key) {
        auto lookUp = options.find(key);
        if (lookUp != options.end())
        {
            return lookUp->second;
        }
        else throw std::runtime_error("(command) ERROR: No such option '" + key + "'.");
    }

}