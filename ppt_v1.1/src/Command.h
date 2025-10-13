#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include "Presentation.h"
#include "Shape.h"
#include "Slide.h"
#include "Text.h"

namespace dec {
    using Data = std::variant<std::monostate, std::string, double, std::pair<double, double>, bool>;

    class ICommand {
    public:
        ICommand() = default;
        virtual void execute() = 0;
    };


    class AddShape : public ICommand {
    public:
        AddShape() : shape(nullptr){}
        void execute() override{
            std::cout << "shape added";
        }
    private:
        std::shared_ptr<obj::IShape> shape;

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
        obj::Presentation ppt;
        size_t position;
    };


    class AddPicture : public ICommand {
    public:
        AddPicture() : path("./image.jpg"), posistion({0, 0}){}
        void execute() override{
            std::cout << "shape added";
        }
    private:
        std::pair<double, double> posistion;
        std::string path;
        std::unordered_map<std::string, Data> params = {
            {"position", std::monostate{}},
            {"angle", std::monostate{}},
            {"height", std::monostate{}},
            {"width", std::monostate{}},
            {"length", std::monostate{}},
            {"borderline width", 0.0},
            {"borderline color", std::monostate{}}
        };
    };


    class AddText : public ICommand {
    public:
        AddText() : text("text"), posistion({0, 0}){}
        void execute() override{
            std::cout << "shape added";
        }
    private:
        obj::Text text;
        std::pair<double, double> posistion;
    };
};