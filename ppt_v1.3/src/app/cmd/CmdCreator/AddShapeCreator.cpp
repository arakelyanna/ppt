#include "CmdCreator.h"

namespace cmd{
    AddShapeCreator::AddShapeCreator(std::shared_ptr<doc::Ppt> ppt)
        : I_CmdCreator(ppt) {
        options = {
            {"shape", false},
            {"pos", true},
            {"color", true},
            {"text", true},
            {"size", true},
            {"line_color", true},
            {"line_width", true},
            {"filled", false},
        };
    }

    std::unique_ptr<I_Command> AddShapeCreator::create() {
        std::shared_ptr<obj::IShape> shape;
        
        // Check if "shape" key exists
        if (options.find("shape") == options.end()) {
            throw std::runtime_error("(command) ERROR: 'shape' option missing");
        }
        
        auto arg = std::get_if<std::string>(&options.at("shape").val);
        
        // Check if it's actually a string
        if (!arg) {
            throw std::runtime_error("(command) ERROR: 'shape' value is not a string");
        }
        
        std::cout << "Shape type: " << *arg << std::endl;
        if (filled_shapes.find(*arg) != filled_shapes.end()) {
            std::shared_ptr<obj::FilledShapes> filledShape;

            if (*arg == "rectangle") {
                filledShape = std::make_shared<obj::Rectangle>();
            }
            else if (*arg == "square") {
                filledShape = std::make_shared<obj::Square>();
            }
            else if (*arg == "triangle") {
                filledShape = std::make_shared<obj::Triangle>();
            }
            else {
                filledShape = std::make_shared<obj::Circle>();
            }
            auto pos = std::get_if<obj::Geometry>(&options.at("pos").val);
            if(pos) filledShape->create(*pos);
            else throw std::runtime_error("(command) ERROR: The shape Geometry is not ok, please fix it.");
            
            arg = std::get_if<std::string>(&options.at("color").val);
            if(arg) filledShape->set_color(*arg);
            
            auto is_filled = std::get_if<bool>(&options.at("filled").val);
            if(is_filled) filledShape->set_filled(*is_filled);

            arg = std::get_if<std::string>(&options.at("line_color").val);
            if(arg) filledShape->set_line_color(*arg);

            auto width = std::get_if<double>(&options.at("line_width").val);
            if(width) filledShape->set_line_width(*width);
            auto text_arg = std::get_if<std::string>(&options.at("text").val);
            if (text_arg) {
                filledShape->set_text(*text_arg);
                auto size = std::get_if<double>(&options.at("size").val);
                if (size) filledShape->set_text_size(*size);
            }

            shape = filledShape;
        }
        else if (lined_shapes.find(*arg) != lined_shapes.end()) {
            std::shared_ptr<obj::LinedShapes> linedShape;
            if (*arg == "line") {
                linedShape = std::make_shared<obj::Line>();
            }
            else if (*arg == "arrow") {
                linedShape = std::make_shared<obj::Arrow>();
            }
            
            auto pos = std::get_if<obj::Geometry>(&options.at("pos").val);
            if(pos) linedShape->create(*pos);
            else throw std::runtime_error("(command) ERROR: The shape Geometry is not ok, please fix it.");
            
            // ADD CHECKS!
            arg = std::get_if<std::string>(&options.at("color").val);
            if(arg) linedShape->set_color(*arg);  // ✓ Check before dereferencing
            
            auto width = std::get_if<double>(&options.at("line_width").val);
            if(width) linedShape->set_width(*width);  // ✓ Check before dereferencing

            auto text_arg = std::get_if<std::string>(&options.at("text").val);
            if (text_arg) {
                linedShape->set_text(*text_arg);
                auto size = std::get_if<double>(&options.at("size").val);
                if (size) linedShape->set_text_size(*size);
            }

            shape = linedShape;
        }
        else throw std::runtime_error("(command) ERROR: Unsupported shape type '" + *arg + "'!");

        std::shared_ptr<obj::Object> objPtr = std::static_pointer_cast<obj::Object>(shape);
        return std::make_unique<AddShape>(ppt, objPtr);
    }

}