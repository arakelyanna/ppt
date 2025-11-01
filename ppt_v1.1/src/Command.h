#pragma once
#include <vector>
#include <variant>
#include <unordered_map>
#include <variant>
#include <memory>
#include "Presentation.h"
#include "Shape.h"
#include "Slide.h"
#include "Text.h"

namespace cmd {
    using Data = std::variant<std::monostate, double, int, bool, obj::Position, std::string>;
    class ICommand {
    public:
        ICommand() = default;
        virtual void execute() = 0;
        virtual void setPosition() = 0;
    
    };


    class AddShape : public ICommand {
    public:
        AddShape(const std::string& shape_type) : shape(nullptr){
            if (shape_type=="rectangle") shape = std::make_unique<obj::Rectangle>();
            else if (shape_type=="square") shape = std::make_unique<obj::Square>();
            else if (shape_type=="triangle") shape = std::make_unique<obj::Triangle>();
            else if (shape_type=="circle") shape = std::make_unique<obj::Circle>();
            else if (shape_type=="Line") shape = std::make_unique<obj::Line>();
            else if (shape_type=="Arrow") shape = std::make_unique<obj::Arrow>();

        }
        void execute() override{
            std::cout << "shape added";
        }
        void setPosition(const obj::Position& pos){
            shape->create(pos);
        }
        void setFilled(bool val){
            shape->set_filled(val);
        }
        void setLineColor(const std::string& color){
            shape->set_line_color(color);
        }
        void setColor(const std::string& color){
            shape->set_color(color);
        }
        void setLineWidth(double width){
            shape->set_line_width(width);
        }
    private:
        std::unique_ptr<obj::IShape> shape;
    };

    class AddSlide : public ICommand {
    public:
        AddSlide() : position(0){}
        void execute() override{
            std::cout << "shape added";
        }
        void at(size_t pos){
            position = pos;
        }

    private:
        doc::Ppt ppt;
        size_t position;
    };


    class AddPicture : public ICommand {
    public:
        AddPicture(const std::string& file){
            pic.open(file);
            if (!pic)  throw std::runtime_error("ERROR: Picture file not found\n");
            
        }
        void execute() override{
            std::cout << "shape added";
        }
    
    private:
        std::fstream pic;
        
    };


    class AddText : public ICommand {
    public:
        AddText(){ }
        void execute() override{
            std::cout << "shape added";
        }
        
        void setPosition(const obj::Position& pos){
            text.create(pos);
        }
        void setSize(double size){
            text.set_size(size);
        }
        void setColor(const std::string& color){
            text.set_color(color);
        }
        void setStyle(const std::string& style){
            text.set_style(style);
        }
        void setValue(const std::string& value){
            text.set_value(value);
        }
    private:
        obj::Text text;
        std::pair<double, double> posistion;
    };
}