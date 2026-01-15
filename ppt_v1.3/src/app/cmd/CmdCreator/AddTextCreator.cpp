#include "CmdCreator.h"

namespace cmd{
    AddTextCreator::AddTextCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"text", OptInfo(true)},
            {"pos", OptInfo(true)},
            {"font", OptInfo(true)},
            {"style", OptInfo(true)},
            {"size", OptInfo(true)},
            {"color", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> AddTextCreator::create() {
        auto text = std::make_shared<obj::Text>();
        
        auto pos = std::get_if<obj::Geometry>(&options.at("pos").val);
        if(pos) text->create(*pos);
        else throw std::runtime_error("(command) ERROR: The text position is not ok, please fix it.");
        
        auto arg = std::get_if<std::string>(&options.at("text").val);
        if(arg) text->set_value(*arg);
        else text->set_value("text");
        

        arg = std::get_if<std::string>(&options.at("style").val);
        if(arg) text->set_style(*arg);

        arg = std::get_if<std::string>(&options.at("color").val);
        if(arg) text->set_color(*arg);

        auto size = std::get_if<int>(&options.at("size").val);
        if(size) text->set_size(*size);

        return std::make_unique<AddText>(ppt, text);
    }
}