#pragma once
#include <string>
#include <memory>
#include "../../../objects/Text/Text.h"
#include "../../../objects/Shapes/Shape.h"
#include "../../doc/ppt/Presentation.h"
#include "../json.hpp" 

using json = nlohmann::json;

namespace file {
    // Base serializer interface
    class ISerializer {
    public:
        virtual ~ISerializer() = default;
        virtual json serialize() const = 0;
    };

    // Text serializer
    class TextSerializer : public ISerializer {
    public:
        explicit TextSerializer(const obj::Text& text) : text_(text) {}
        
        json serialize() const override {
            json j;
            j["type"] = "text";
            j["value"] = text_.get_text();
            j["size"] = text_.get_size();
            j["color"] = text_.get_color();
            j["style"] = text_.get_style();
            
            const auto& geom = text_.get_geometry();
            j["geometry"] = json::array();
            for (const auto& coord : geom) {
                j["geometry"].push_back({coord.first, coord.second});
            }
            
            return j;
        }
        
    private:
        const obj::Text& text_;
    };

    // FilledShape serializer
    class FilledShapeSerializer : public ISerializer {
    public:
        explicit FilledShapeSerializer(const obj::FilledShapes& shape, const std::string& shapeType) 
            : shape_(shape), shapeType_(shapeType) {}
        
        json serialize() const override {
            json j;
            j["type"] = shapeType_;
            const auto& geom = shape_.get_geometry();
            j["geometry"] = json::array();
            for (const auto& coord : geom) {
                j["geometry"].push_back({coord.first, coord.second});
            }
            j["color"] = shape_.get_color();
            j["borderline_color"] = shape_.get_line_color();
            j["borderline_width"] = shape_.get_line_width();
            j["filled"] = shape_.is_filled();
            // Text content
            j["text"] = {
                {"value", shape_.get_text()},
                {"size", shape_.get_text_size()},
                {"color", shape_.get_text_color()},
                {"style", shape_.get_text_style()}
            };
            
            return j;
        }
        
    private:
        const obj::FilledShapes& shape_;
        std::string shapeType_;
    };

    // LinedShape serializer
    class LinedShapeSerializer : public ISerializer {
    public:
        explicit LinedShapeSerializer(const obj::LinedShapes& shape, const std::string& shapeType) 
            : shape_(shape), shapeType_(shapeType) {}
        
        json serialize() const override {
            json j;
            j["type"] = shapeType_;
            const auto& geom = shape_.get_geometry();
            j["geometry"] = json::array();
            for (const auto& coord : geom) {
                j["geometry"].push_back({coord.first, coord.second});
            }
            j["color"] = shape_.get_color();
            j["width"] = shape_.get_width();
            j["length"] = shape_.get_length();
            
            // Text content
            j["text"] = {
                {"value", shape_.get_text()},
                {"size", shape_.get_text_size()},
                {"color", shape_.get_text_color()},
                {"style", shape_.get_text_style()}
            };
            
            return j;
        }
        
    private:
        const obj::LinedShapes& shape_;
        std::string shapeType_;
    };

    // doc::Slide serializer
    class SlideSerializer : public ISerializer {
    public:
        explicit SlideSerializer(const doc::Slide& slide, 
                                const std::vector<std::unique_ptr<ISerializer>>& objectSerializers) 
            : slide_(slide), objectSerializers_(objectSerializers) {}
        
        json serialize() const override {
            
            json j;
            j["id"] = slide_.get_id();
            j["objects"] = json::array();
            
            
            for (size_t i = 0; i < objectSerializers_.size(); ++i) {
                
                if (!objectSerializers_[i]) {
                    continue;
                }
                
                try {
                    json objJson = objectSerializers_[i]->serialize();
                    j["objects"].push_back(objJson);
                } catch (const std::exception& e) {
                    throw std::runtime_error("(files) ERROR: Could not serialize object " + std::to_string(i) + ": " + std::string(e.what()));
                }
            }
            
            return j;
        }
        
    private:
        const doc::Slide& slide_;
        const std::vector<std::unique_ptr<ISerializer>>& objectSerializers_;
    };

    // Presentation serializer
    class PresentationSerializer : public ISerializer {
    public:
        explicit PresentationSerializer(std::shared_ptr<doc::Ppt> ppt, 
                                       const std::vector<std::unique_ptr<ISerializer>>& slideSerializers)
            : ppt_(ppt), slideSerializers_(slideSerializers) {}
        
        json serialize() const override {
            json j;
            j["version"] = "1.0";
            j["slide_count"] = ppt_->size();
            j["slides"] = json::array();
            
            for (const auto& serializer : slideSerializers_) {
                j["slides"].push_back(serializer->serialize());
            }
            
            return j;
        }
        
    private:
        std::shared_ptr<doc::Ppt> ppt_;
        const std::vector<std::unique_ptr<ISerializer>>& slideSerializers_;
    };
}

