#include "Visitor.h"

namespace out{

    void CLIPrinterVisitor::print() {
        for (size_t i = 0; i < ppt->size(); i++)
        {
            printSlide(i);
        }
    }

    void CLIPrinterVisitor::printSlide(size_t pos) {
        auto slide = ppt->operator[](pos);
        printer->printSlide(slide);
        for (auto& obj : *slide)
        {
            obj->accept(*this);
        }
    }

    void CLIPrinterVisitor::visit(const obj::Rectangle &obj) const {
        printer->print_rectangle(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Triangle &obj) const {
        printer->print_triangle(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Circle &obj) const {
        printer->print_circle(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Square &obj) const {
        printer->print_square(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Picture &obj) const {
        printer->print_picture(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Text &obj) const {
        printer->print_text(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Line &obj) const {
        printer->print_line(obj);
    }
    void CLIPrinterVisitor::visit(const obj::Arrow &obj) const {
        printer->print_arrow(obj);
    }
}