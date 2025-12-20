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
        std::cout << "DEBUG: createSerializer - typeid = " << typeid(obj).name() << std::endl;
        
        // Debug: print all registered types
        std::cout << "DEBUG: Number of registered types: " << serializerCreators_.size() << std::endl;
        std::cout << "DEBUG: Registered types:" << std::endl;
        for (const auto& pair : serializerCreators_) {
            std::cout << "  - " << pair.first.name() << std::endl;
        }
        
        auto typeIdx = std::type_index(typeid(obj));
        auto it = serializerCreators_.find(typeIdx);
        
        if (it == serializerCreators_.end()) {
            std::cerr << "ERROR: No serializer for type: " << typeid(obj).name() << std::endl;
            throw std::runtime_error("No serializer registered for object type");
        }
        
        std::cout << "DEBUG: Found serializer, calling creator..." << std::endl;
        auto result = it->second(obj);
        std::cout << "DEBUG: Serializer created successfully" << std::endl;
        
        return result;
    }

    std::shared_ptr<obj::Object> SerializationFactory::createObject(const json& j) const {
        if (!j.contains("type")) {
            throw std::runtime_error("JSON object missing 'type' field");
        }
        
        std::string type = j["type"].get<std::string>();
        auto it = deserializerCreators_.find(type);
        if (it == deserializerCreators_.end()) {
            throw std::runtime_error("No deserializer registered for type: " + type);
        }
        return it->second(j);
    }

    json SerializationFactory::serializeSlide(const doc::Slide& slide) const {
        std::vector<std::unique_ptr<ISerializer>> objectSerializers;
        
        std::cout << "DEBUG: serializeSlide - counting objects..." << std::endl;
        int count = 0;
        
        json j;
        j["id"] = slide.get_id();
        
        for (auto it = slide.begin(); it != slide.end(); ++it) {
            count++;
        }
        std::cout << "DEBUG: Slide has " << count << " objects" << std::endl;
        
        for (auto it = slide.begin(); it != slide.end(); ++it) {
            const auto& obj = *it;
            if (obj) {
                std::cout << "DEBUG: Serializing object type: " << typeid(*obj).name() << std::endl;
                objectSerializers.push_back(createSerializer(*obj));
            } else {
                std::cout << "DEBUG: Skipping null object" << std::endl;
            }
        }
        j["objects"] = json::array();
        
        for (const auto& serializer : objectSerializers) {
            j["objects"].push_back(serializer->serialize());
        }
        
        return j;  
    }

    std::shared_ptr<doc::Slide> SerializationFactory::deserializeSlide(const json& j) const {
        std::vector<std::shared_ptr<obj::Object>> objects;
        
        std::cout << "DEBUG: deserializeSlide - checking for objects..." << std::endl;
        
        if (j.contains("objects")) {
            std::cout << "DEBUG: Found objects array, size = " << j["objects"].size() << std::endl;
            
            for (const auto& objJson : j["objects"]) {
                try {
                    std::cout << "DEBUG: Deserializing object type: " << objJson["type"] << std::endl;
                    auto obj = createObject(objJson);
                    objects.push_back(obj);
                    std::cout << "DEBUG: Object deserialized successfully" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Failed to deserialize object: " 
                            << e.what() << std::endl;
                }
            }
        } else {
            std::cout << "DEBUG: No objects array found in JSON!" << std::endl;
        }
        
        std::cout << "DEBUG: Total objects deserialized: " << objects.size() << std::endl;
        
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
            
            // Serialize slide immediately
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
                    std::cerr << "Warning: Failed to deserialize slide: " 
                              << e.what() << std::endl;
                }
            }
        }
        
        return PresentationDeserializer::deserialize(j, slides);
    }

    bool SerializationFactory::saveToFile(std::shared_ptr<doc::Ppt> ppt, const std::string& filename = "./ppt_test") const {
        try {
            std::cout << "DEBUG: saveToFile - starting serialization..." << std::endl;
            
            if (!ppt) {
                std::cerr << "ERROR: ppt is null in saveToFile!" << std::endl;
                return false;
            }
            
            std::cout << "DEBUG: Calling serializePresentation..." << std::endl;
            json j = serializePresentation(ppt);
            
            std::cout << "DEBUG: Serialization complete, opening file..." << std::endl;
            
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
                return false;
            }
            
            std::cout << "DEBUG: Writing JSON to file..." << std::endl;
            file << j.dump(4);
            file.close();
            
            std::cout << "DEBUG: File saved successfully!" << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error saving presentation: " << e.what() << std::endl;
            return false;
        }
    }

    std::shared_ptr<doc::Ppt> SerializationFactory::loadFromFile(const std::string& filename) const {
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
                return nullptr;
            }
            
            json j;
            file >> j;
            file.close();
            
            return deserializePresentation(j);
        } catch (const std::exception& e) {
            std::cerr << "Error loading presentation: " << e.what() << std::endl;
            return nullptr;
        }
    }

    SerializationFactory& SerializationFactory::createDefaultFactory() {
        static SerializationFactory factory;
        
        // Register Text
        factory.registerSerializer<obj::Text>("text", 
            [](const obj::Text& text) -> std::unique_ptr<ISerializer> {
                return std::make_unique<TextSerializer>(text);
            });
        factory.registerDeserializer("text",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return TextDeserializer::deserialize(j);
            });
        
        // Register Circle
        factory.registerSerializer<obj::Circle>("circle",
            [](const obj::Circle& circle) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(circle, "circle");
            });
        factory.registerDeserializer("circle",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Circle>::deserialize(j);
            });
        
        // Register Rectangle
        factory.registerSerializer<obj::Rectangle>("rectangle",
            [](const obj::Rectangle& rect) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(rect, "rectangle");
            });
        factory.registerDeserializer("rectangle",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Rectangle>::deserialize(j);
            });
        
        // Register Square
        factory.registerSerializer<obj::Square>("square",
            [](const obj::Square& sq) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(sq, "square");
            });
        factory.registerDeserializer("square",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Square>::deserialize(j);
            });
        
        // Register Triangle
        factory.registerSerializer<obj::Triangle>("triangle",
            [](const obj::Triangle& tri) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(tri, "triangle");
            });
        factory.registerDeserializer("triangle",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Triangle>::deserialize(j);
            });
        
        // Register Picture
        factory.registerSerializer<obj::Picture>("picture",
            [](const obj::Picture& pic) -> std::unique_ptr<ISerializer> {
                return std::make_unique<FilledShapeSerializer>(pic, "picture");
            });
        factory.registerDeserializer("picture",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return FilledShapeDeserializer<obj::Picture>::deserialize(j);
            });
        
        // Register Line
        factory.registerSerializer<obj::Line>("line",
            [](const obj::Line& line) -> std::unique_ptr<ISerializer> {
                return std::make_unique<LinedShapeSerializer>(line, "line");
            });
        factory.registerDeserializer("line",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return LinedShapeDeserializer<obj::Line>::deserialize(j);
            });
        
        // Register Arrow
        factory.registerSerializer<obj::Arrow>("arrow",
            [](const obj::Arrow& arrow) -> std::unique_ptr<ISerializer> {
                return std::make_unique<LinedShapeSerializer>(arrow, "arrow");
            });
        factory.registerDeserializer("arrow",
            [](const json& j) -> std::shared_ptr<obj::Object> {
                return LinedShapeDeserializer<obj::Arrow>::deserialize(j);
            });
        
        return factory;
    }
    
}