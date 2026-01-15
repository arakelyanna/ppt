#pragma once
#include <memory>

namespace doc {
    class Ppt;
}

namespace obj {
    class Rectangle;
    class Triangle;
    class Circle;
    class Square;
    class Picture;
    class Text;
    class Line;
    class Arrow;
}

namespace files {
    class IVisitor {
    public:
        IVisitor() = default;
        IVisitor(std::shared_ptr<doc::Ppt> ppt) : ppt(ppt) {}
        virtual void visit() = 0;
        virtual void visitSlide(size_t pos) = 0;
        virtual void visit(const obj::Rectangle& obj) const = 0;
        virtual void visit(const obj::Triangle& obj) const = 0; 
        virtual void visit(const obj::Circle& obj) const = 0;   
        virtual void visit(const obj::Square& obj) const = 0;   
        virtual void visit(const obj::Picture& obj) const = 0;  
        virtual void visit(const obj::Text& obj) const = 0;     
        virtual void visit(const obj::Line& obj) const = 0;     
        virtual void visit(const obj::Arrow& obj) const = 0;    
        virtual ~IVisitor() = default;
        
    protected:
        std::shared_ptr<doc::Ppt> ppt;
    };
}