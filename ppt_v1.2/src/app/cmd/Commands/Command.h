#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <fstream>
#include "../../doc/ppt/Presentation.h"
#include "../../doc/Editor/Editor.h"
#include "../../../objects/Shapes/Shape.h"
#include "../../../objects/Text/Text.h"
#include "../../doc/Slide/Slide.h"

namespace cmd {
    class I_Command {
    public:
        I_Command(std::shared_ptr<doc::Ppt> ppt) {
            if(!editor) {
                editor = std::make_shared<doc::Editor>(ppt);
            }
        }

        virtual bool execute(std::ostream& output) = 0;
        virtual ~I_Command() = default;

    protected:
        static std::shared_ptr<doc::Editor> editor;
        
    };
    std::shared_ptr<doc::Editor> I_Command::editor=nullptr;

    class AddSlide : public I_Command {
    public:
        AddSlide(std::shared_ptr<doc::Ppt> ppt, std::shared_ptr<doc::Slide> slide, size_t pos=0)
            : I_Command(ppt), slide(slide), pos(pos) {}

        bool execute(std::ostream& output) override;
    private:
        std::shared_ptr<doc::Slide> slide;
        size_t pos;
    };

    class RemoveSlide : public I_Command {
    public:
        RemoveSlide(std::shared_ptr<doc::Ppt> ppt, size_t pos = 0)
            : I_Command(ppt), pos(pos) {}
        bool execute(std::ostream& output) override;
    private:
        size_t pos;
    };

    class AddShape : public I_Command {
    public:
        AddShape(std::shared_ptr<doc::Ppt> ppt, std::shared_ptr<obj::Object> shape)
            : I_Command(ppt), shape(std::move(shape)) {}
        bool execute(std::ostream& output) override;
    private:
        std::shared_ptr<obj::Object> shape;
    };


    class RemoveObject : public I_Command {
    public:
        RemoveObject(std::shared_ptr<doc::Ppt> ppt, const obj::Coord& pos = {0, 0})
            : I_Command(ppt), pos(pos) {}
        bool execute(std::ostream& output) override;
    private:
        obj::Coord pos;
    };

    class AddPicture : public I_Command {
    public:
        AddPicture(std::shared_ptr<doc::Ppt> ppt, std::shared_ptr<obj::Object> picture)
            : I_Command(ppt), pic(picture) {}
        bool execute(std::ostream& output) override;
    private:
        std::shared_ptr<obj::Object> pic;
    };

    class AddText : public I_Command {
    public:
        AddText(std::shared_ptr<doc::Ppt> ppt, std::shared_ptr<obj::Object> txt)
            : I_Command(ppt), text(txt) {}
        bool execute(std::ostream& output) override;
    private:
        std::shared_ptr<obj::Object> text;
    };

    class ShowSlide : public I_Command {
    public:
        ShowSlide(std::shared_ptr<doc::Ppt> ppt, size_t pos, std::ostream& output = std::cout)
            : I_Command(ppt), pos(pos), output(output) {}
        bool execute(std::ostream& output) override;
    private:
        size_t pos;
        std::ostream& output;
    };

    class ShowFile : public I_Command {
    public:
        ShowFile(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout)
            : I_Command(ppt), output(output) {}
        bool execute(std::ostream& output) override;
    private:
        std::ostream& output;
    };

    class Open : public I_Command {
    public:
        Open(std::shared_ptr<doc::Ppt> ppt, const std::string& path = "./ppt_test")
            : I_Command(ppt), file_path(path) {}
        bool execute(std::ostream& output) override;
    private:
        std::string file_path;
    };

    class Save : public I_Command {
    public:
        Save(std::shared_ptr<doc::Ppt> ppt, const std::string& path = "./ppt_test")
            : I_Command(ppt), file_path(path) {}
        bool execute(std::ostream& output) override;
    private:
        std::string file_path; 
    };

    class Exit : public I_Command {
    public:
        Exit(std::shared_ptr<doc::Ppt> ppt)
            : I_Command(ppt) {}
        bool execute(std::ostream& output) override;
    };

    class Undo : public I_Command {
    public:
        Undo(std::shared_ptr<doc::Ppt> ppt)
            : I_Command(ppt) {}
        bool execute(std::ostream& output) override;
    };

    class Redo : public I_Command {
    public:
        Redo(std::shared_ptr<doc::Ppt> ppt)
            : I_Command(ppt) {}
        bool execute(std::ostream& output) override;
    };
}