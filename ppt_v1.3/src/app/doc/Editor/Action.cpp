#include "Action.h"
#include "../Editor/Editor.h"   // if needed

namespace doc {

    AddSlideAction::AddSlideAction(std::shared_ptr<Slide> slide, size_t pos) {
        this->pSlide = slide;
        this->pos = pos;
    }

    std::shared_ptr<IAction> AddSlideAction::carry_out(std::shared_ptr<Ppt> doc) {
        doc->add_slide(pSlide, pos);
        return std::make_shared<RemoveSlideAction>(pos);
    }


    RemoveSlideAction::RemoveSlideAction(size_t pos) {
        this->pos = pos;
    }

    std::shared_ptr<IAction> RemoveSlideAction::carry_out(std::shared_ptr<Ppt> doc) {
        pSlide = doc->remove_slide(pos);
        return std::make_shared<AddSlideAction>(pSlide, pos);
    }

    AddObjectAction::AddObjectAction(std::shared_ptr<obj::Object> obj) {
        pObj = obj;
        std::cout << "ACTION!\n";
        if (obj && !obj->get_geometry().empty()) {
            coord = obj->get_geometry()[0];
        } else {
            coord = {0.0, 0.0};
        }
    }

    std::shared_ptr<IAction> AddObjectAction::carry_out(std::shared_ptr<Ppt> doc) {
        doc->add_object(pObj);
        return std::make_shared<RemoveObjectAction>(coord);
    }


    RemoveObjectAction::RemoveObjectAction(const Coord& position) {
        coord = position;
    }

    std::shared_ptr<IAction> RemoveObjectAction::carry_out(std::shared_ptr<Ppt> doc) {
        pObj = doc->remove_object(coord);
        return std::make_shared<AddObjectAction>(pObj);
    }

}
