#include "Deserializer.h"
#include "../../../../objects/Shapes/Shape.h"
#include <fstream>
#include <stdexcept>

namespace files {

    JSONDeserializer::JSONDeserializer(const std::string& file) {
        std::string file_path = "./ztest/files/" + file;
        std::ifstream input(file_path);

        if (!input.is_open()) {
            throw std::runtime_error("(command) ERROR: Failed to open file!\n");
        }
        
        input >> j;
        input.close();
    }

    std::shared_ptr<doc::Ppt> JSONDeserializer::open() {
        auto ppt = std::make_shared<doc::Ppt>();
        
        // Remove the default slide created by the Ppt constructor
        if (ppt->size() > 0) {
            ppt->remove_slide(0);
        }
        
        if (!j.contains("Slides") || !j["Slides"].is_array()) {
            throw std::runtime_error("(deserializer) ERROR: Invalid JSON format - missing Slides array\n");
        }
        
        for (const auto& slide_json : j["Slides"]) {
            auto slide = deserialize_slide(slide_json);
            ppt->add_slide(slide);
        }
        
        return ppt;
    }

    std::shared_ptr<doc::Slide> JSONDeserializer::deserialize_slide(const json& slide_json) {
        auto slide = std::make_shared<doc::Slide>();
        
        // Set slide properties
        if (slide_json.contains("Slide ID")) {
            slide->set_id(slide_json["Slide ID"].get<size_t>());
        }
        
        if (slide_json.contains("color")) {
            std::string color = slide_json["color"].get<std::string>();
            if (!color.empty()) {
                slide->set_color(color);
            }
        }
        
        // Deserialize objects
        if (slide_json.contains("objects") && slide_json["objects"].is_array()) {
            for (const auto& obj_json : slide_json["objects"]) {
                if (!obj_json.contains("type")) continue;
                
                std::string type = obj_json["type"].get<std::string>();
                
                if (type == "Circle") {
                    slide->add_object(deserialize_circle(obj_json));
                } else if (type == "Rectangle") {
                    slide->add_object(deserialize_rectangle(obj_json));
                } else if (type == "Square") {
                    slide->add_object(deserialize_square(obj_json));
                } else if (type == "Triangle") {
                    slide->add_object(deserialize_triangle(obj_json));
                } else if (type == "Line") {
                    slide->add_object(deserialize_line(obj_json));
                } else if (type == "Arrow") {
                    slide->add_object(deserialize_arrow(obj_json));
                } else if (type == "Picture") {
                    slide->add_object(deserialize_picture(obj_json));
                } else if (type == "Text") {
                    slide->add_object(deserialize_text(obj_json));
                }
            }
        }
        
        return slide;
    }

    obj::Geometry JSONDeserializer::deserialize_geometry(const json& geom_json) {
        obj::Geometry geom;
        for (const auto& point : geom_json) {
            double x = point["x"].get<double>();
            double y = point["y"].get<double>();
            geom.push_back({x, y});
        }
        return geom;
    }

    std::shared_ptr<obj::Circle> JSONDeserializer::deserialize_circle(const json& obj_json) {
        auto circle = std::make_shared<obj::Circle>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            circle->create(geom);
        }
        
        if (obj_json.contains("radius")) {
            circle->set_radius(obj_json["radius"].get<double>());
        }
        
        apply_filled_shape_properties(circle, obj_json);
        
        return circle;
    }

    std::shared_ptr<obj::Rectangle> JSONDeserializer::deserialize_rectangle(const json& obj_json) {
        auto rect = std::make_shared<obj::Rectangle>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            rect->create(geom);
        }
        
        if (obj_json.contains("height")) {
            rect->set_height(obj_json["height"].get<double>());
        }
        if (obj_json.contains("width")) {
            rect->set_width(obj_json["width"].get<double>());
        }
        
        apply_filled_shape_properties(rect, obj_json);
        
        return rect;
    }

    std::shared_ptr<obj::Square> JSONDeserializer::deserialize_square(const json& obj_json) {
        auto square = std::make_shared<obj::Square>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            square->create(geom);
        }
        
        if (obj_json.contains("side")) {
            square->set_side(obj_json["side"].get<double>());
        }
        
        apply_filled_shape_properties(square, obj_json);
        
        return square;
    }

    std::shared_ptr<obj::Triangle> JSONDeserializer::deserialize_triangle(const json& obj_json) {
        auto triangle = std::make_shared<obj::Triangle>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            triangle->create(geom);
        }
        
        apply_filled_shape_properties(triangle, obj_json);
        
        return triangle;
    }

    std::shared_ptr<obj::Line> JSONDeserializer::deserialize_line(const json& obj_json) {
        auto line = std::make_shared<obj::Line>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            line->create(geom);
        }
        
        apply_lined_shape_properties(line, obj_json);
        
        return line;
    }

    std::shared_ptr<obj::Arrow> JSONDeserializer::deserialize_arrow(const json& obj_json) {
        auto arrow = std::make_shared<obj::Arrow>();
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            arrow->create(geom);
        }
        
        apply_lined_shape_properties(arrow, obj_json);
        
        return arrow;
    }

    std::shared_ptr<obj::Picture> JSONDeserializer::deserialize_picture(const json& obj_json) {
        std::string path = obj_json.contains("path") ? obj_json["path"].get<std::string>() : "./pic.png";
        auto picture = std::make_shared<obj::Picture>(path);
        
        if (obj_json.contains("geometry")) {
            obj::Geometry geom = deserialize_geometry(obj_json["geometry"]);
            picture->create(geom);
        }
        
        if (obj_json.contains("height")) {
            picture->set_height(obj_json["height"].get<double>());
        }
        if (obj_json.contains("width")) {
            picture->set_width(obj_json["width"].get<double>());
        }
        
        apply_filled_shape_properties(picture, obj_json);
        
        return picture;
    }

    std::shared_ptr<obj::Text> JSONDeserializer::deserialize_text(const json& obj_json) {
        auto text = std::make_shared<obj::Text>();
        
        if (obj_json.contains("text")) {
            text->set_value(obj_json["text"].get<std::string>());
        }
        if (obj_json.contains("size")) {
            text->set_size(obj_json["size"].get<size_t>());
        }
        if (obj_json.contains("color")) {
            text->set_color(obj_json["color"].get<std::string>());
        }
        if (obj_json.contains("style")) {
            text->set_style(obj_json["style"].get<std::string>());
        }
        
        return text;
    }

    void JSONDeserializer::apply_filled_shape_properties(std::shared_ptr<obj::FilledShapes> shape, const json& obj_json) {
        if (obj_json.contains("color")) {
            shape->set_color(obj_json["color"].get<std::string>());
        }
        if (obj_json.contains("line_color")) {
            shape->set_line_color(obj_json["line_color"].get<std::string>());
        }
        if (obj_json.contains("line_width")) {
            shape->set_line_width(obj_json["line_width"].get<double>());
        }
        if (obj_json.contains("filled")) {
            shape->set_filled(obj_json["filled"].get<bool>());
        }
        if (obj_json.contains("text")) {
            shape->set_text(obj_json["text"].get<std::string>());
        }
        if (obj_json.contains("text_size")) {
            shape->set_text_size(obj_json["text_size"].get<size_t>());
        }
        if (obj_json.contains("text_color")) {
            shape->set_text_color(obj_json["text_color"].get<std::string>());
        }
        if (obj_json.contains("text_style")) {
            shape->set_text_style(obj_json["text_style"].get<std::string>());
        }
    }

    void JSONDeserializer::apply_lined_shape_properties(std::shared_ptr<obj::LinedShapes> shape, const json& obj_json) {
        if (obj_json.contains("color")) {
            shape->set_color(obj_json["color"].get<std::string>());
        }
        if (obj_json.contains("width")) {
            shape->set_width(obj_json["width"].get<double>());
        }
        if (obj_json.contains("text")) {
            shape->set_text(obj_json["text"].get<std::string>());
        }
        if (obj_json.contains("text_size")) {
            shape->set_text_size(obj_json["text_size"].get<size_t>());
        }
        if (obj_json.contains("text_color")) {
            shape->set_text_color(obj_json["text_color"].get<std::string>());
        }
        if (obj_json.contains("text_style")) {
            shape->set_text_style(obj_json["text_style"].get<std::string>());
        }
    }

}