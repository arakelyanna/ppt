#pragma once

#include <memory>
#include <cstddef>
#include "../Slide/Slide.h"
#include "../ppt/Presentation.h"
#include "../../../objects/Object.h"
#include "../../../objects/Shapes/Shape.h"
#include "../../../objects/Text/Text.h"

namespace doc {

    using obj::Coord;

    class IAction {
    public:
        IAction() = default;
        virtual ~IAction() = default;
        virtual std::shared_ptr<IAction> carry_out(std::shared_ptr<Ppt> doc) = 0;

    protected:
        std::shared_ptr<Slide> pSlide = nullptr;
        std::shared_ptr<obj::Object> pObj = nullptr;
        size_t pos = 0;
        Coord coord{};
    };

    class AddSlideAction : public IAction {
    public:
        AddSlideAction(std::shared_ptr<Slide> slide, size_t pos = 0);
        std::shared_ptr<IAction> carry_out(std::shared_ptr<Ppt> doc) override;
    };

    class RemoveSlideAction : public IAction {
    public:
        RemoveSlideAction(size_t pos);
        std::shared_ptr<IAction> carry_out(std::shared_ptr<Ppt> doc) override;
    };

    class AddObjectAction : public IAction {
    public:
        AddObjectAction(std::shared_ptr<obj::Object> obj);
        std::shared_ptr<IAction> carry_out(std::shared_ptr<Ppt> doc) override;
    };

    class RemoveObjectAction : public IAction {
    public:
        RemoveObjectAction(const Coord& position);
        std::shared_ptr<IAction> carry_out(std::shared_ptr<Ppt> doc) override;
    };

}
