#pragma once
#include "../../../Visitor.h"
#include "../Serializer.h"
#include "../../../../../objects/Shapes/Shape.h"

namespace files{
    class JSONSerializerVisitor : public IVisitor {
    public:
        JSONSerializerVisitor(std::shared_ptr<doc::Ppt> ppt, const std::string& filename) :
            IVisitor(ppt) {
            serializer = std::make_shared<JSONSerializer>(filename);  // Pass filename
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
        std::shared_ptr<ISerializer> serializer;
    };

}