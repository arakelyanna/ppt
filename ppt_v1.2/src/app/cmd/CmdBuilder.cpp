#include <stdexcept>
#include "CmdBuilder.h"

namespace cmd {
    const std::set<std::string> filled_shapes = {"rectangle", "triangle", "circle", "square"};
    const std::set<std::string> lined_shapes = {"line", "arrow"};

    void Builder::set(const std::string key, const Value& val) {
        auto lookUp = options.find(key);
        if (lookUp != options.end())                
            options[key] = val;
        else throw std::runtime_error("ERROR: Invalid option " + key);
    }

    std::unique_ptr<obj::IShape> Builder::build_shape() {
        auto arg = std::get_if<std::string>(&options.at("args"));

        if (filled_shapes.find(*arg) != filled_shapes.end()) {
            std::unique_ptr<obj::FilledShapes> shape;
            if (*arg == "rectangle") {
                shape = std::make_unique<obj::Rectangle>();
            }
            else if (*arg == "square") {
                shape = std::make_unique<obj::Square>();
            }
            else if (*arg == "triangle") {
                shape = std::make_unique<obj::Triangle>();
            }
            else {
                shape = std::make_unique<obj::Circle>();
            }
            auto pos = std::get_if<Position>(&options.at("pos"));
            shape->create(*pos);
            
            arg = std::get_if<std::string>(&options.at("color"));
            shape->set_color(*arg);

            auto is_filled = std::get_if<bool>(&options.at("filled"));
            shape->set_filled(*is_filled);

            arg = std::get_if<std::string>(&options.at("borderline_color"));
            shape->set_line_color(*arg);

            auto width = std::get_if<double>(&options.at("borderline_width"));
            shape->set_line_width(*width);

            return shape;
        }
        else if (lined_shapes.find(*arg) != lined_shapes.end()) {
            std::unique_ptr<obj::LinedShapes> shape;
            if (*arg == "line") {
                shape = std::make_unique<obj::Line>();
            }
            else if (*arg == "arrow") {
                shape = std::make_unique<obj::Arrow>();
            }
            auto pos = std::get_if<Position>(&options.at("pos"));
            shape->create(*pos);
            
            arg = std::get_if<std::string>(&options.at("color"));
            shape->set_color(*arg);

            auto width = std::get_if<double>(&options.at("borderline_width"));
            shape->set_width(*width);

            auto text_arg = std::get_if<std::string>(&options.at("text"));
            if (text_arg) shape->set_text(*text_arg);

            return shape;
        }
     
        else throw std::runtime_error("ERROR: Unsupported shape type '" + *arg + "'!");
    }

    obj::Picture Builder::build_picture() {
        obj::Picture pic;
        auto pos = std::get_if<Position>(&options.at("pos"));
        auto file = std::get_if<std::string>(&options.at("files"));
        pic.create(*pos, *file);
        return pic;
    }
    
    std::unique_ptr<obj::Text> Builder::build_text() {
        std::unique_ptr<obj::Text> text = std::make_unique<obj::Text>();
        auto pos = std::get_if<Position>(&options.at("pos"));
        text->create(*pos);
        auto arg = std::get_if<std::string>(&options.at("text"));
        text->set_value(*arg);
        arg = std::get_if<std::string>(&options.at("style"));
        text->set_style(*arg);
        arg = std::get_if<std::string>(&options.at("color"));
        text->set_color(*arg);

        auto size = std::get_if<int>(&options.at("size"));
        text->set_size(*size);
        return text;
    }

    const std::string& Builder::build_file() {
        auto arg = std::get_if<std::string>(&options.at("file"));
        return *arg;
    }

    size_t Builder::build_slide_command(){
        auto pos = std::get_if<int>(&options.at("pos"));
        return *pos;
    }
}