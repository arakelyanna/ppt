#include "SerializerVisitor.h"

namespace files {

    void JSONSerializerVisitor::visit() {
        for (size_t i = 0; i < ppt->size(); ++i)
        {
            visitSlide(i);
        }
        serializer->save();
    }

    void JSONSerializerVisitor::visitSlide(size_t pos) {
        auto slide = ppt->operator[](pos);

        serializer->serialize_slide(slide);
        for (auto& obj: *slide)
        {
            obj->accept(*this);
        }
        serializer->end_serialize_slide();
    }

    void JSONSerializerVisitor::visit(const obj::Rectangle& obj) const {
        serializer->serialize_rectangle(obj);
    }

    void JSONSerializerVisitor::visit(const obj::Triangle& obj) const {
        serializer->serialize_triangle(obj);

    }

    void JSONSerializerVisitor::visit(const obj::Circle& obj) const {
        serializer->serialize_circle(obj);
    }

    void JSONSerializerVisitor::visit(const obj::Square& obj) const {
        serializer->serialize_square(obj);
    }

    void JSONSerializerVisitor::visit(const obj::Picture& obj) const {
        serializer->serialize_picture(obj);
    
    }

    void JSONSerializerVisitor::visit(const obj::Text& obj) const {
        serializer->serialize_text(obj);
    }

    void JSONSerializerVisitor::visit(const obj::Line& obj) const {
        serializer->serialize_line(obj);
    }

    void JSONSerializerVisitor::visit(const obj::Arrow& obj) const {
        serializer->serialize_arrow(obj);
    }

}
