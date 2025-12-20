#include "Presentation.h"

namespace doc {
    Ppt::Ppt(const std::string& path="") : current(0) {
        if (path != "") {

        }
        ppt.push_back(std::make_shared<Slide>());
    }
    void Ppt::setFilePath(const std::string& file = "./ppt_test") {
        filePath = file;
    }

    void Ppt::add_slide(std::shared_ptr<Slide> slide, size_t pos) {
        if (pos > ppt.size())
            throw std::out_of_range("(doc) ERROR: Invalid slide index " +  std::to_string(pos));
        for (size_t i = pos; i < ppt.size(); i++)
        {
            ppt[i]->set_id(ppt[i]->get_id() + 1);
        }
        
        slide->set_id(pos);
        ppt.insert(ppt.begin() + pos, slide);
    }
    
    std::shared_ptr<Slide> Ppt::remove_slide(size_t pos) {
        if (pos > ppt.size())
            throw std::out_of_range("(doc) ERROR: Invalid slide index " +  std::to_string(pos));
        for (size_t i = pos; i < ppt.size(); i++)
        {
            ppt[i]->set_id(ppt[i]->get_id() - 1);
        }
        std::shared_ptr<Slide> erased = ppt[pos];
        ppt.erase(ppt.begin() + pos);
        return erased;
    }

    
    void Ppt::add_object(std::shared_ptr<obj::Object> obj) {
        ppt[current]->add_object(obj);
    }

    std::shared_ptr<obj::Object> Ppt::remove_object(const obj::Coord& pos) {
        std::shared_ptr<obj::Object> pObj = ppt[current]->get_object(pos);
        if (!pObj) 
            throw std::runtime_error("(action) ERROR: At the specified point no object has been found");
        return ppt[current]->remove_object(pObj);
    }


    size_t Ppt::size() const {
        return ppt.size();
    }

    std::shared_ptr<Slide> Ppt::operator[](size_t i) {
        if (i >= ppt.size()) throw std::runtime_error("(doc) ERROR: Invalid Slide index");
        return ppt[i];
    }

    std::shared_ptr<Slide> const Ppt::operator[](size_t i) const {
        if (i >= ppt.size()) throw std::runtime_error("(doc) ERROR: Invalid Slide index");
        return ppt[i];
    }
}

