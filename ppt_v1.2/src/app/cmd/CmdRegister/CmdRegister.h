#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "../CmdCreator/CmdCreator.h"

namespace cmd {
    class CmdRegister {
    public:
        CmdRegister(std::shared_ptr<doc::Ppt> ppt) : ppt(ppt) {
            commands.emplace("add slide", [ppt](){ return std::make_unique<AddSlideCreator>(ppt); });
            commands.emplace("remove slide", [ppt](){ return std::make_unique<RemoveSlideCreator>(ppt); });
            commands.emplace("add shape", [ppt](){ return std::make_unique<AddShapeCreator>(ppt); });
            commands.emplace("add text", [ppt](){ return std::make_unique<AddTextCreator>(ppt); });
            commands.emplace("add picture", [ppt](){ return std::make_unique<AddPictureCreator>(ppt); });
            commands.emplace("remove object", [ppt](){ return std::make_unique<RemoveObjectCreator>(ppt); });
            commands.emplace("show slide", [ppt](){ return std::make_unique<ShowSlideCreator>(ppt); });
            commands.emplace("show", [ppt](){ return std::make_unique<ShowFileCreator>(ppt); });
            commands.emplace("draw slide", [ppt](){ return std::make_unique<DrawSlideCreator>(ppt); });
            commands.emplace("draw", [ppt](){ return std::make_unique<DrawCreator>(ppt); });
            commands.emplace("open", [ppt](){ return std::make_unique<OpenCreator>(ppt); });
            commands.emplace("save", [ppt](){ return std::make_unique<SaveCreator>(ppt); });
            commands.emplace("undo", [ppt](){ return std::make_unique<UndoCreator>(ppt); });
            commands.emplace("redo", [ppt](){ return std::make_unique<RedoCreator>(ppt); });
            commands.emplace("set current slide", [ppt](){ return std::make_unique<SetCurrentSlideCreator>(ppt); });
            commands.emplace("current slide", [ppt](){ return std::make_unique<CurrentSlideCreator>(ppt); });
            commands.emplace("help", [ppt](){ return std::make_unique<HelpCreator>(ppt); });
            commands.emplace("exit", [ppt](){ return std::make_unique<ExitCreator>(ppt); });
            commands.emplace("q", [ppt](){ return std::make_unique<ExitCreator>(ppt); });
        }
        std::string find(const std::string& command_name) const;
        std::unique_ptr<I_CmdCreator> get(const std::string& command_name) const;
    private:
        std::shared_ptr<doc::Ppt> ppt;
        std::unordered_map<std::string, std::function<std::unique_ptr<I_CmdCreator>()>> commands;
    };
}