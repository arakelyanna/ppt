#pragma once
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <memory>
#include <string>
#include "../json.hpp"

// Forward declarations
namespace obj {
    class Object;
}

namespace doc {
    class Slide;
    class Ppt;
}

namespace file {
    class ISerializer;
    
    using json = nlohmann::json;
    
    class SerializationFactory {
    public:
        SerializationFactory() = default;
        ~SerializationFactory() = default;

        static SerializationFactory& createDefaultFactory();

        bool saveToFile(std::shared_ptr<doc::Ppt> ppt, const std::string& filename) const;
        std::shared_ptr<doc::Ppt> loadFromFile(const std::string& filename) const;
        
    private:
        template<typename T>
        void registerSerializer(const std::string& typeName,
                               std::function<std::unique_ptr<ISerializer>(const T&)> creator);

        void registerDeserializer(const std::string& typeName,
                                 std::function<std::shared_ptr<obj::Object>(const json&)> creator);

        std::unique_ptr<ISerializer> createSerializer(const obj::Object& obj) const;

        std::shared_ptr<obj::Object> createObject(const json& j) const;

        // Serialize a single slide using iterators (no objects parameter needed)
        json serializeSlide(const doc::Slide& slide) const;

        std::shared_ptr<doc::Slide> deserializeSlide(const json& j) const;

        // Serialize entire presentation (uses iterators internally)
        json serializePresentation(std::shared_ptr<doc::Ppt> ppt) const;

        std::shared_ptr<doc::Ppt> deserializePresentation(const json& j) const;

    private:
        std::unordered_map<std::type_index, 
                          std::function<std::unique_ptr<ISerializer>(const obj::Object&)>> serializerCreators_;
        std::unordered_map<std::type_index, std::string> typeNames_;
        std::unordered_map<std::string, 
                          std::function<std::shared_ptr<obj::Object>(const json&)>> deserializerCreators_;
    };

    template<typename T>
    void SerializationFactory::registerSerializer(const std::string& typeName,
                           std::function<std::unique_ptr<ISerializer>(const T&)> creator) {
        auto typeIdx = std::type_index(typeid(T));
        serializerCreators_[typeIdx] = [creator, typeName](const obj::Object& obj) {
            return creator(dynamic_cast<const T&>(obj));
        };
        typeNames_[typeIdx] = typeName;
    }

    // SerializationFactory createDefaultFactory();
    
}