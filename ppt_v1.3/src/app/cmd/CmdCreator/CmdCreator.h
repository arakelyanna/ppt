#pragma once
#include <algorithm>
#include <set>
#include <string>
#include <memory>
#include <variant>
#include <unordered_map>
#include <vector>
#include "../Commands/Command.h"

namespace cmd {
    using Value = std::variant<std::monostate, int, double, bool, std::string, obj::Geometry>;
    struct OptInfo {
        OptInfo(bool getsArg=true, const Value& val = std::monostate()) : getsArg(getsArg), val(val) {}
        Value val;
        bool getsArg;
    };
    
    using Option = std::unordered_map<std::string, OptInfo>;

    const std::set<std::string> filled_shapes = {"rectangle", "triangle", "circle", "square"};
    const std::set<std::string> lined_shapes = {"line", "arrow"};

    class I_CmdCreator {
    public:
        I_CmdCreator(std::shared_ptr<doc::Ppt> ppt) : ppt(ppt) {}
        virtual void set(const std::string key, const Value& val);
        virtual OptInfo get(const std::string& key);
        virtual std::unique_ptr<I_Command> create() = 0;
        virtual ~I_CmdCreator() = default;
    protected:
        Option options;
        std::unique_ptr<I_Command> command; // to be built
        std::shared_ptr<doc::Ppt> ppt;
    };

    class AddSlideCreator : public I_CmdCreator {
    public:
        AddSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class RemoveSlideCreator : public I_CmdCreator {
    public:
        RemoveSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class RemoveObjectCreator : public I_CmdCreator {
    public:
        RemoveObjectCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class AddShapeCreator : public I_CmdCreator {
    public:
        AddShapeCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class AddPictureCreator : public I_CmdCreator {
    public:
        AddPictureCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class AddTextCreator : public I_CmdCreator {
    public:
        AddTextCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class ShowSlideCreator : public I_CmdCreator {
    public:
        ShowSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class ShowFileCreator : public I_CmdCreator {
    public:
        ShowFileCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class DrawSlideCreator : public I_CmdCreator {
    public:
        DrawSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class DrawCreator : public I_CmdCreator {
    public:
        DrawCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };


    class OpenCreator : public I_CmdCreator {
    public:
        OpenCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class SaveCreator : public I_CmdCreator {
    public:
        SaveCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };
    
    class UndoCreator : public I_CmdCreator {
    public:
        UndoCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class RedoCreator : public I_CmdCreator {
    public:
        RedoCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class ExitCreator : public I_CmdCreator {
    public:
        ExitCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    
    class CurrentSlideCreator : public I_CmdCreator {
    public:
        CurrentSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class SetCurrentSlideCreator : public I_CmdCreator {
    public:
        SetCurrentSlideCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };

    class HelpCreator : public I_CmdCreator {
    public:
        HelpCreator(std::shared_ptr<doc::Ppt> ppt);
        std::unique_ptr<I_Command> create() override;
    };
}