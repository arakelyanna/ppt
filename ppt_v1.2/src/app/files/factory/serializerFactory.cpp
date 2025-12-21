#include "serializerFactory.h"
#include "../serializer/Serializer.h"
#include "../deserializer/Deserializer.h"
#include "../../doc/ppt/Presentation.h"
#include <fstream>
#include <iostream>

namespace file {

    void SerializationFactory::registerDeserializer(const std::string& typeName,
                             std::function<std::shared_ptr<obj::Object>(const json&)> creator) {
        deserializerCreators_[typeName] = creator;
    }

    std::unique_ptr<ISerializer> SerializationFactory::createSerializer(const obj::Object& obj) const {

        auto typeIdx = std::type_index(typeid(obj));
        auto it = serializerCreators_.find(typeIdx);
        
        if (it == serializerCreators_.end()) {
            throw std::runtime_error("(files) WARNING: No serializer registered for object type " + std::string(typeid(obj).name()) + "\n");
        }
        
        auto result = it->second(obj);
        
        return result;
    }

    std::shared_ptr<obj::Object> SerializationFactory::createObject(const json& j) const {
        if (!j.contains("type")) {
            throw std::runtime_error("(files) ERROR: JSON object missing 'type' field");
        }
        
        std::string type = j["type"].get<std::string>();
        auto it = deserializerCreators_.find(type);
        if (it == deserializerCreators_.end()) {
            throw std::runtime_error("(files) ERROR: No deserializer registered for type: " + type);
        }
        return it->second(j);
    }

    json SerializationFactory::serializeSlide(const doc::Slide& slide) const {
        json j;
        j["id"] = slide.get_id();
        j["objects"] = json::array();
        
        // ONE loop, no vector!
        for (auto it = slide.begin(); it != slide.end(); ++it) {
            const auto& obj = *it;
            if (obj) {
                auto serializer = createSerializer(*obj);  // Create
                j["objects"].push_back(serializer->serialize());  // Use immediately
            }
        }
        
        return j;
    }

    std::shared_ptr<doc::Slide> SerializationFactory::deserializeSlide(const json& j) const {
        std::vector<std::shared_ptr<obj::Object>> objects;
        
        
        if (j.contains("objects")) {
            
            for (const auto& objJson : j["objects"]) {
                try {
                    auto obj = createObject(objJson);
                    objects.push_back(obj);
                } catch (const std::exception& e) {
                    throw std::runtime_error("(files) WARNING: Failed to deserialize slide: " + std::string(e.what()) + "\n");

                }
            }
        }
        
        
        return SlideDeserializer::deserialize(j, objects);
    }

    json SerializationFactory::serializePresentation(std::shared_ptr<doc::Ppt> ppt) const {
        json j;
        j["version"] = "1.0";
        j["slide_count"] = ppt->size();
        j["slides"] = json::array();
        
        for (size_t i = 0; i < ppt->size(); ++i) {
            auto slidePtr = (*ppt)[i];
            if (!slidePtr) continue;
            
            j["slides"].push_back(serializeSlide(*slidePtr));
        }
        
        return j;
    }

    std::shared_ptr<doc::Ppt> SerializationFactory::deserializePresentation(const json& j) const {
        std::vector<std::shared_ptr<doc::Slide>> slides;
        
        if (j.contains("slides")) {
            for (const auto& slideJson : j["slides"]) {
                try {
                    slides.push_back(deserializeSlide(slideJson));
                } catch (const std::exception& e) {
                    throw std::runtime_error("(files) WARNING: Failed to deserialize slide: " + std::string(e.what()) + "\n");
                }
            }
        }
        
        return PresentationDeserializer::deserialize(j, slides);
    }

    bool SerializationFactory::saveToFile(std::shared_ptr<doc::Ppt> ppt, const std::string& filename = "./ppt_test") const {
        try {
            
            if (!ppt) {
                return false;
            }
            
            json j = serializePresentation(ppt);
            
            
            std::ofstream file(filename);
            if (!file.is_open()) {
                return false;
            }
            
            file << j.dump(4);
            file.close();
            
            return true;
        } catch (const std::exception& e) {
            throw std::runtime_error("(files) ERROR: Could not save presentation: " + std::string(e.what()));
        }
    }

    std::shared_ptr<doc::Ppt> SerializationFactory::loadFromFile(const std::string& filename) const {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("(files) ERROR: Could not open file " + filename);
            }
            
            json j;
            file >> j;
            file.close();
            
            return deserializePresentation(j);
        } catch (const std::exception& e) {
            throw std::runtime_error("(files) ERROR: Could not load presentation " + std::string(e.what()));
        }
    }

    SerializationFactory& SerializationFactory::createDefaultFactory() {
        static SerializationFactory factory;
        
        // Register Text
        factory.registerSerializer<obj::Text>([](const obj::Text& text) -> std::unique_ptr<ISerializer> {
                return std::make_unique<TextSerializer>(text);
            });
        factory.registerDeserializer("text",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return TextDeserializer::deserialize(j);
            });
        
        // Register Circle
        factory.registerSerializer<obj::Circle>([](const obj::Circle& circle) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(circle, "circle");
            });
        factory.registerDeserializer("circle", [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Circle>::deserialize(j);
            });
        
        // Register Rectangle
        factory.registerSerializer<obj::Rectangle>([](const obj::Rectangle& rect) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(rect, "rectangle");
            });
        factory.registerDeserializer("rectangle",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Rectangle>::deserialize(j);
            });
        
        // Register Square
        factory.registerSerializer<obj::Square>([](const obj::Square& sq) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(sq, "square");
            });
        factory.registerDeserializer("square",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Square>::deserialize(j);
            });
        
        // Register Triangle
        factory.registerSerializer<obj::Triangle>([](const obj::Triangle& tri) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(tri, "triangle");
            });
        factory.registerDeserializer("triangle", [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Triangle>::deserialize(j);
            });
        
        // Register Picture
        factory.registerSerializer<obj::Picture>([](const obj::Picture& pic) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(pic, "picture");
            });
        factory.registerDeserializer("picture",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Picture>::deserialize(j);
            });
        
        // Register Line
        factory.registerSerializer<obj::Line>([](const obj::Line& line) -> std::unique_ptr<ISerializer> {
                return std::make_unique<LinedShapeSerializer>(line, "line");
            });
        factory.registerDeserializer("line", [](const json& j) -> std::shared_ptr<obj::Object> {
                return LinedShapeDeserializer<obj::Line>::deserialize(j);
            });
        
        // Register Arrow
        factory.registerSerializer<obj::Arrow>([](const obj::Arrow& arrow) -> std::unique_ptr<ISerializer> {
                return std::make_unique<LinedShapeSerializer>(arrow, "arrow");
            });
        factory.registerDeserializer("arrow",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return LinedShapeDeserializer<obj::Arrow>::deserialize(j);
            });
        
        return factory;
    }
    
}