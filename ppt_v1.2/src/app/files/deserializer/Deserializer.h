#pragma once
#include <string>
#include <memory>
#include "../../../objects/Text/Text.h"
#include "../../../objects/Shapes/Shape.h"
#include "../../doc/Slide/Slide.h"
#include "../../doc/ppt/Presentation.h"
#include "../json.hpp"

using json = nlohmann::json;

namespace file {
    
    // Base deserializer interface
    class IDeserializer {
    public:
        virtual ~IDeserializer() = default;
    };

    // Text deserializer
    class TextDeserializer : public IDeserializer {
    public:
        static std::shared_ptr<obj::Text> deserialize(const json& j) {
            auto text = std::make_shared<obj::Text>();
            
            if (j.contains("value")) {
                text->set_value(j["value"].get<std::string>());
            }
            if (j.contains("size")) {
                text->set_size(j["size"].get<size_t>());
            }
            if (j.contains("color")) {
                text->set_color(j["color"].get<std::string>());
            }
            if (j.contains("style")) {
                text->set_style(j["style"].get<std::string>());
            }
            if (j.contains("geometry")) {
                obj::Geometry geom;
                for (const auto& coord : j["geometry"]) {
                    geom.push_back({coord[0].get<double>(), coord[1].get<double>()});
                }
                text->create(geom);
            }
            
            return text;
        }
    };

    // FilledShape deserializer template
    template<typename ShapeType>
    class FilledShapeDeserializer : public IDeserializer {
    public:
        static std::shared_ptr<ShapeType> deserialize(const json& j) {
            auto shape = std::make_shared<ShapeType>();
            
            // Deserialize geometry first if present
            if (j.contains("geometry")) {
                obj::Geometry geom;
                for (const auto& coord : j["geometry"]) {
                    geom.push_back({coord[0].get<double>(), coord[1].get<double>()});
                }
                shape->create(geom);
            }
            
            if (j.contains("color")) {
                shape->set_color(j["color"].get<std::string>());
            }
            if (j.contains("borderline_color")) {
                shape->set_line_color(j["borderline_color"].get<std::string>());
            }
            if (j.contains("borderline_width")) {
                shape->set_line_width(j["borderline_width"].get<double>());
            }
            if (j.contains("filled")) {
                shape->set_filled(j["filled"].get<bool>());
            }
            
            // Deserialize text content
            if (j.contains("text")) {
                const auto& textJson = j["text"];
                if (textJson.contains("value")) {
                    shape->set_text(textJson["value"].get<std::string>());
                }
                if (textJson.contains("size")) {
                    shape->set_text_size(textJson["size"].get<size_t>());
                }
                if (textJson.contains("color")) {
                    shape->set_text_color(textJson["color"].get<std::string>());
                }
                if (textJson.contains("style")) {
                    shape->set_text_style(textJson["style"].get<std::string>());
                }
            }
            
            return shape;
        }
    };

    // LinedShape deserializer template
    template<typename ShapeType>
    class LinedShapeDeserializer : public IDeserializer {
    public:
        static std::shared_ptr<ShapeType> deserialize(const json& j) {
            auto shape = std::make_shared<ShapeType>();
            
            // Deserialize geometry first if present
            if (j.contains("geometry")) {
                obj::Geometry geom;
                for (const auto& coord : j["geometry"]) {
                    geom.push_back({coord[0].get<double>(), coord[1].get<double>()});
                }
                shape->create(geom);
            }
            
            if (j.contains("color")) {
                shape->set_color(j["color"].get<std::string>());
            }
            if (j.contains("width")) {
                shape->set_width(j["width"].get<double>());
            }
            
            // Deserialize text content
            if (j.contains("text")) {
                const auto& textJson = j["text"];
                if (textJson.contains("value")) {
                    shape->set_text(textJson["value"].get<std::string>());
                }
                if (textJson.contains("size")) {
                    shape->set_text_size(textJson["size"].get<size_t>());
                }
                if (textJson.contains("color")) {
                    shape->set_text_color(textJson["color"].get<std::string>());
                }
                if (textJson.contains("style")) {
                    shape->set_text_style(textJson["style"].get<std::string>());
                }
            }
            
            return shape;
        }
    };

    // Slide deserializer
    class SlideDeserializer : public IDeserializer {
    public:
        // Deserialize slide with already-deserialized objects
        static std::shared_ptr<doc::Slide> deserialize(const json& j, 
                                                   std::vector<std::shared_ptr<obj::Object>>& objects) {
            auto slide = std::make_shared<doc::Slide>();
            
            if (j.contains("id")) {
                slide->set_id(j["id"].get<size_t>());
            }
            
            for (auto& obj : objects) {
                slide->add_object(obj);
            }
            
            return slide;
        }
    };

    // Presentation deserializer
    class PresentationDeserializer : public IDeserializer {
    public:
        static std::shared_ptr<doc::Ppt> deserialize(const json& j, 
                                        std::vector<std::shared_ptr<doc::Slide>>& slides) {
            auto ppt = std::make_shared<doc::Ppt>("");
            
            // Clear the default slide
            if (ppt->size() > 0) {
                ppt->remove_slide(0);
            }
            
            for (size_t i = 0; i < slides.size(); ++i) {
                int objCount = 0;
                for (auto it = slides[i]->begin(); it != slides[i]->end(); ++it) {
                    objCount++;
                }
                
                ppt->add_slide(slides[i], ppt->size());  // Add at END
            }
            
            return ppt;
        }
    };
    
}