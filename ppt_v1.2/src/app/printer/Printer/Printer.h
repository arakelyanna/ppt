#pragma once
#include "../../doc/ppt/Presentation.h"
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
namespace out{
    class IPrinter
    {
    public:
        virtual void printSlide(std::shared_ptr<doc::Slide>) = 0;
        virtual void print_rectangle(const obj::Rectangle& obj) = 0;
        virtual void print_triangle(const obj::Triangle& obj) = 0;
        virtual void print_circle(const obj::Circle& obj) = 0;
        virtual void print_square(const obj::Square& obj) = 0;
        virtual void print_line(const obj::Line& obj) = 0;
        virtual void print_arrow(const obj::Arrow& obj) = 0;
        virtual void print_picture(const obj::Picture& obj) = 0;
        virtual void print_text(const obj::Text& obj) = 0;

        virtual ~IPrinter() = default;
    };

    class CLIPrinter : public IPrinter{
    public:
        CLIPrinter(std::ostream& output) : output(output){}

        void printSlide(std::shared_ptr<doc::Slide>) override;
        void print_rectangle(const obj::Rectangle& obj) override;
        void print_triangle(const obj::Triangle& obj) override;
        void print_circle(const obj::Circle& obj) override;
        void print_square(const obj::Square& obj) override;
        void print_line(const obj::Line& obj) override;
        void print_arrow(const obj::Arrow& obj) override;
        void print_picture(const obj::Picture& obj) override;
        void print_text(const obj::Text& obj) override;
    protected:
        std::ostream& output;
    };

    class SVGPrinter : public IPrinter{
    public:
        std::string getSVGContent() const;
        void clearContent();
        void addContent(const std::string& content);

        void printSlide(std::shared_ptr<doc::Slide>) override;
        void print_rectangle(const obj::Rectangle& obj) override;
        void print_triangle(const obj::Triangle& obj) override;
        void print_circle(const obj::Circle& obj) override;
        void print_square(const obj::Square& obj) override;
        void print_line(const obj::Line& obj) override;
        void print_arrow(const obj::Arrow& obj) override;
        void print_picture(const obj::Picture& obj) override;
        void print_text(const obj::Text& obj) override;
    private:
        std::string svgContent;
    };
}