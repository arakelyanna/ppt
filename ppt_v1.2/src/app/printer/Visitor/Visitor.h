#pragma once
#include "../Printer/Printer.h"
#include "../../../objects/Shapes/Shape.h"

namespace out{
    class IVisitor {
    public:
        IVisitor() = default;
        IVisitor(std::shared_ptr<doc::Ppt> ppt) : ppt(ppt) {}
        virtual void print() = 0;
        virtual void printSlide(size_t pos) = 0;
        virtual void visit(const obj::Rectangle& obj) const = 0;
        virtual void visit(const obj::Triangle& obj) const = 0; 
        virtual void visit(const obj::Circle& obj) const = 0;   
        virtual void visit(const obj::Square& obj) const = 0;   
        virtual void visit(const obj::Picture& obj) const = 0;  
        virtual void visit(const obj::Text& obj) const = 0;     
        virtual void visit(const obj::Line& obj) const = 0;     
        virtual void visit(const obj::Arrow& obj) const = 0;    
        
    protected:
        std::shared_ptr<IPrinter> printer;
        std::shared_ptr<doc::Ppt> ppt;
    };

    class CLIPrinterVisitor : public IVisitor {
    public:
        CLIPrinterVisitor(std::shared_ptr<doc::Ppt> ppt, std::ostream& output) :
             IVisitor(ppt) {
           printer = std::make_shared<CLIPrinter>(output);
        }
        void print() override;
        void printSlide(size_t pos) override;
        void visit(const obj::Rectangle& obj) const override;
        void visit(const obj::Triangle& obj) const override;
        void visit(const obj::Circle& obj) const override;
        void visit(const obj::Square& obj) const override;
        void visit(const obj::Picture& obj) const override;
        void visit(const obj::Text& obj) const override;
        void visit(const obj::Line& obj) const override;
        void visit(const obj::Arrow& obj) const override;
    };

    class SVGPrinterVisitor : public IVisitor {
    public:
        SVGPrinterVisitor(std::shared_ptr<doc::Ppt> ppt) : IVisitor(ppt) { }
        void print() override;
        void printSlide(size_t pos) override;
        void visit(const obj::Rectangle& obj) const override;
        void visit(const obj::Triangle& obj) const override;
        void visit(const obj::Circle& obj) const override;
        void visit(const obj::Square& obj) const override;
        void visit(const obj::Picture& obj) const override;
        void visit(const obj::Text& obj) const override;
        void visit(const obj::Line& obj) const override;
        void visit(const obj::Arrow& obj) const override; 
    };
}