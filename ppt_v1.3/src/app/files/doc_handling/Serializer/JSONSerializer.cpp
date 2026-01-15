#include "Serializer.h"
#include "../../../../objects/Shapes/Shape.h"

namespace files {

    JSONSerializer::JSONSerializer(const std::string& file) {
        std::string file_path = "./ztest/files/" + file;
        output.open(file_path);

        if (!output.is_open()) {
            throw std::runtime_error("(command) ERROR: Failed to save file!\n");
        }
        
        j["Slides"] = json::array();
    }

    void JSONSerializer::save() {
        output << j.dump(4);
    }

    void JSONSerializer::serialize_slide(std::shared_ptr<doc::Slide> slide) {
        json_slide = json::object();
        json_slide["Slide ID"] = slide->get_id();
        json_slide["color"] = slide->get_color();
        json_slide["objects"] = json::array();
    }

    void JSONSerializer::end_serialize_slide() {
        j["Slides"].push_back(json_slide);
        json_slide.clear();
    }

    void JSONSerializer::serialize_rectangle(const obj::Rectangle& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Dimensions
        obj_json["height"] = obj.get_height();
        obj_json["width"] = obj.get_width();
        
        // Style properties
        obj_json["color"] = obj.get_color();
        obj_json["line_color"] = obj.get_line_color();
        obj_json["line_width"] = obj.get_line_width();
        obj_json["filled"] = obj.is_filled();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();

        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_triangle(const obj::Triangle& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry (3 points)
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Sides
        const auto& sides = obj.get_sides();
        obj_json["sides"] = {sides[0], sides[1], sides[2]};
        
        // Style properties
        obj_json["color"] = obj.get_color();
        obj_json["line_color"] = obj.get_line_color();
        obj_json["line_width"] = obj.get_line_width();
        obj_json["filled"] = obj.is_filled();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_circle(const obj::Circle& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry (center point)
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Radius
        obj_json["radius"] = obj.get_radius();
        
        // Style properties
        obj_json["color"] = obj.get_color();
        obj_json["line_color"] = obj.get_line_color();
        obj_json["line_width"] = obj.get_line_width();
        obj_json["filled"] = obj.is_filled();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_square(const obj::Square& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Side length
        obj_json["side"] = obj.get_side();
        
        // Style properties
        obj_json["color"] = obj.get_color();
        obj_json["line_color"] = obj.get_line_color();
        obj_json["line_width"] = obj.get_line_width();
        obj_json["filled"] = obj.is_filled();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_line(const obj::Line& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry (2 endpoints)
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Line properties
        obj_json["length"] = obj.get_length();
        obj_json["width"] = obj.get_width();
        obj_json["color"] = obj.get_color();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_arrow(const obj::Arrow& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry (2 endpoints)
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Arrow-specific properties
        obj_json["length"] = obj.get_length();
        obj_json["width"] = obj.get_width();
        obj_json["pointing"] = obj.points_to();
        obj_json["color"] = obj.get_color();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_picture(const obj::Picture& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = obj.get_type();
        
        // Geometry
        const auto& geom = obj.get_geometry();
        obj_json["geometry"] = json::array();
        for (const auto& point : geom) {
            obj_json["geometry"].push_back({{"x", point.first}, {"y", point.second}});
        }
        
        // Picture-specific properties
        obj_json["path"] = obj.get_path();
        obj_json["height"] = obj.get_height();
        obj_json["width"] = obj.get_width();
        
        // Note: Picture doesn't use color in the traditional sense
        // but has line properties from FilledShapes
        obj_json["line_color"] = obj.get_line_color();
        obj_json["line_width"] = obj.get_line_width();
        obj_json["filled"] = obj.is_filled();
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["text_size"] = obj.get_text_size();
        obj_json["text_color"] = obj.get_text_color();
        obj_json["text_style"] = obj.get_text_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
    void JSONSerializer::serialize_text(const obj::Text& obj) {
        json obj_json = json::object();
        
        obj_json["type"] = "Text";
        
        // Text properties
        obj_json["text"] = obj.get_text();
        obj_json["size"] = obj.get_size();
        obj_json["color"] = obj.get_color();
        obj_json["style"] = obj.get_style();
        
        json_slide["objects"].push_back(obj_json);
    }
    
}