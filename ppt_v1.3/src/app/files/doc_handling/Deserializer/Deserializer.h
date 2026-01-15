#pragma once
#include "../../../doc/ppt/Presentation.h"
#include "../json.hpp"
#include <memory>

using json = nlohmann::json;

// Forward declarations
namespace obj {
    class Circle;
    class Rectangle;
    class Square;
    class Triangle;
    class Line;
    class Arrow;
    class Picture;
    class Text;
    class FilledShapes;
    class LinedShapes;
}

namespace files {
    class JSONDeserializer {
    public:
        JSONDeserializer(const std::string& file);
        
        std::shared_ptr<doc::Ppt> open();
        
    private:
        std::shared_ptr<doc::Slide> deserialize_slide(const json& slide_json);
        
        obj::Geometry deserialize_geometry(const json& geom_json);
        
        std::shared_ptr<obj::Circle> deserialize_circle(const json& obj_json);
        std::shared_ptr<obj::Rectangle> deserialize_rectangle(const json& obj_json);
        std::shared_ptr<obj::Square> deserialize_square(const json& obj_json);
        std::shared_ptr<obj::Triangle> deserialize_triangle(const json& obj_json);
        std::shared_ptr<obj::Line> deserialize_line(const json& obj_json);
        std::shared_ptr<obj::Arrow> deserialize_arrow(const json& obj_json);
        std::shared_ptr<obj::Picture> deserialize_picture(const json& obj_json);
        std::shared_ptr<obj::Text> deserialize_text(const json& obj_json);
        
        void apply_filled_shape_properties(std::shared_ptr<obj::FilledShapes> shape, const json& obj_json);
        void apply_lined_shape_properties(std::shared_ptr<obj::LinedShapes> shape, const json& obj_json);
        
        json j;
    };
}