#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <fstream>
#include "CmdBuilder.h"
#include "../viewer/Viewer.h"
#include "../doc/Presentation.h"
#include "../../objects/Object.h"
#include "../../objects/Shapes/Shape.h"
#include "../../objects/Text/Text.h"
#include "../../objects/Picture/Picture.h"
#include "../doc/Slide.h"

namespace cmd {
    class I_Command {
    public:
        virtual bool execute() = 0;
        virtual void set(const std::string&, const Value&) = 0;
        virtual void build() = 0;
        virtual void set_viewer(const std::string& viewer) = 0;
        virtual ~I_Command() {}
        
    protected:
        Builder builder;
        doc::Ppt ppt;
        std::string viewer_type;
    };
    
    class AddSlide : public I_Command {
    public:
        AddSlide() : pos(0) {}
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        doc::Slide slide;
        size_t pos;
    };
    
    class RemoveSlide : public I_Command {
    public:
        RemoveSlide() : pos(0){}
        
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:

        doc::Slide slide;
        size_t pos;
    };

    class AddShape : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        std::unique_ptr<obj::IShape> shape;
    };

    class AddPicture : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        obj::Picture pic;
    };

    class AddText : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        std::unique_ptr<obj::Text> text;
    };

    class ShowSlide : public I_Command {
    public:
        ShowSlide();

        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        size_t pos;
    };

    class ShowFile : public I_Command {
    public:
        ShowFile();
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        doc::Slide slide;
        size_t pos;
    };

    class Open : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        std::string file_path;
    };

    class Save : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override {
            viewer_type = viewer;
        }
    private:
        std::string file_path;
    };

    class Exit : public I_Command {
    public:
        void set(const std::string& key, const Value& val) override;
        bool execute() override;
        void build() override;
        void set_viewer(const std::string& viewer) override { }
    };

}