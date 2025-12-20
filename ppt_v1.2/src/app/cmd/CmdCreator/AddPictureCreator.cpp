#include "CmdCreator.h"

namespace cmd {

    AddPictureCreator::AddPictureCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"pos", OptInfo(true)},
            {"file", OptInfo(true)},
            {"h", OptInfo(true)},
            {"w", OptInfo(true)}
        };
    }

    std::unique_ptr<I_Command> AddPictureCreator::create() {
        auto file = std::get_if<std::string>(&options.at("file").val);
        if (!file) 
            throw std::runtime_error("(command creator) ERROR: The file path not specified.");

        auto pic = std::make_shared<obj::Picture>(*file);

        auto pos = std::get_if<obj::Geometry>(&options.at("pos").val);
        if(!pos) 
            throw std::runtime_error("(command creator) ERROR: The picture Geometry is missed.");
        pic->create(*pos);
        
        auto val = std::get_if<double>(&options.at("h").val);
        if(val) pic->set_height(*val);

        val = std::get_if<double>(&options.at("w").val);
        if(val) pic->set_width(*val);

        return std::make_unique<AddPicture>(ppt, pic);
    }

}