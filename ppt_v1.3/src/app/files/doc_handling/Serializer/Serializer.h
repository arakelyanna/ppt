#pragma once
#include "../../../doc/ppt/Presentation.h"
#include "../json.hpp"
#include <fstream>

using json = nlohmann::json;

namespace obj {
    class Rectangle;
    class Triangle;
    class Circle;
    class Square;
    class Line;
    class Arrow;
    class Picture;
    class Text;
}
namespace files {
    class ISerializer
    {
    public:
        virtual void save() = 0;
        virtual void serialize_slide(std::shared_ptr<doc::Slide>) = 0;
        virtual void end_serialize_slide() = 0;
        virtual void serialize_rectangle(const obj::Rectangle& obj) = 0;
        virtual void serialize_triangle(const obj::Triangle& obj) = 0;
        virtual void serialize_circle(const obj::Circle& obj) = 0;
        virtual void serialize_square(const obj::Square& obj) = 0;
        virtual void serialize_line(const obj::Line& obj) = 0;
        virtual void serialize_arrow(const obj::Arrow& obj) = 0;
        virtual void serialize_picture(const obj::Picture& obj) = 0;
        virtual void serialize_text(const obj::Text& obj) = 0;

        virtual ~ISerializer() = default;
    };

    class JSONSerializer : public ISerializer{
    public:
        JSONSerializer(const std::string& file);

        void save() override;
        void serialize_slide(std::shared_ptr<doc::Slide>) override;
        void end_serialize_slide() override;
        void serialize_rectangle(const obj::Rectangle& obj) override;
        void serialize_triangle(const obj::Triangle& obj) override;
        void serialize_circle(const obj::Circle& obj) override;
        void serialize_square(const obj::Square& obj) override;
        void serialize_line(const obj::Line& obj) override;
        void serialize_arrow(const obj::Arrow& obj) override;
        void serialize_picture(const obj::Picture& obj) override;
        void serialize_text(const obj::Text& obj) override;
    protected:
        json j;
        json json_slide;
        std::ofstream output;
    };
}