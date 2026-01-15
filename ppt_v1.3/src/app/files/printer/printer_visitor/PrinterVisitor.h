#pragma once
#include "../Printer/Printer.h"
#include "../../Visitor.h"
#include "../../../../objects/Shapes/Shape.h"

namespace out{
    class CLIPrinterVisitor : public files::IVisitor {
    public:
        CLIPrinterVisitor(std::shared_ptr<doc::Ppt> ppt, std::ostream& output) :
             IVisitor(ppt) {
           printer = std::make_shared<CLIPrinter>(output);
        }
        void visit() override;
        void visitSlide(size_t pos) override;
        void visit(const obj::Rectangle& obj) const override;
        void visit(const obj::Triangle& obj) const override;
        void visit(const obj::Circle& obj) const override;
        void visit(const obj::Square& obj) const override;
        void visit(const obj::Picture& obj) const override;
        void visit(const obj::Text& obj) const override;
        void visit(const obj::Line& obj) const override;
        void visit(const obj::Arrow& obj) const override;
    private:
        std::shared_ptr<IPrinter> printer;
    };

    class SVGPrinterVisitor : public files::IVisitor {
    public:
        SVGPrinterVisitor(std::shared_ptr<doc::Ppt> ppt) : IVisitor(ppt) { }
        void visit() override;
        void visitSlide(size_t pos) override;
        void visit(const obj::Rectangle& obj) const override;
        void visit(const obj::Triangle& obj) const override;
        void visit(const obj::Circle& obj) const override;
        void visit(const obj::Square& obj) const override;
        void visit(const obj::Picture& obj) const override;
        void visit(const obj::Text& obj) const override;
        void visit(const obj::Line& obj) const override;
        void visit(const obj::Arrow& obj) const override; 
    private:
        std::shared_ptr<IPrinter> printer;
    };
}