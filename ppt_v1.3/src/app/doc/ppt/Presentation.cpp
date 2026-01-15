#include "Presentation.h"
#include "../../files/doc_handling/Deserializer/Deserializer.h"

namespace doc {

    Ppt::Ppt(const std::string& path) : current(0) {
        if (path != "") {
            auto deserializer = files::JSONDeserializer(path);
            std::shared_ptr<doc::Ppt> loadedPpt = deserializer.open();
            
            if (!loadedPpt) { 
                throw std::runtime_error("(files) ERROR: Could not open file " + path);
            }
            
            this->ppt = loadedPpt->ppt;
            this->current = loadedPpt->current;
            this->filePath = loadedPpt->filePath;
        }
        else {
            ppt.push_back(std::make_shared<Slide>());
        }
    }


    void Ppt::setFilePath(const std::string& file) {
        filePath = file;
    }

    void Ppt::add_slide(std::shared_ptr<Slide> slide, size_t pos)
    {
        if (pos == std::numeric_limits<size_t>::max())
            pos = ppt.size();

        if (pos > ppt.size())
            throw std::out_of_range(
                "(doc) ERROR: Invalid slide index " + std::to_string(pos)
            );

        for (size_t i = pos; i < ppt.size(); ++i) {
            ppt[i]->set_id(ppt[i]->get_id() + 1);
        }

        slide->set_id(pos);
        ppt.insert(ppt.begin() + pos, slide);
        current = pos;
    }

    
    std::shared_ptr<Slide> Ppt::remove_slide(size_t pos)
    {
        if (ppt.empty())
            throw std::out_of_range("(doc) ERROR: No slides to remove");

        if (pos == std::numeric_limits<size_t>::max())
            pos = ppt.size() - 1;

        if (pos >= ppt.size())
            throw std::out_of_range("(doc) ERROR: Invalid slide index " + std::to_string(pos));

        auto erased = ppt[pos];
        ppt.erase(ppt.begin() + pos);

        for (size_t i = pos; i < ppt.size(); ++i) {
            ppt[i]->set_id(i); 
        }

        if (current >= ppt.size())
            current = ppt.size() - 1;

        return erased;
    }
    
    void Ppt::add_object(std::shared_ptr<obj::Object> obj) {
        ppt[current]->add_object(obj);
    }

    std::shared_ptr<obj::Object> Ppt::remove_object(const obj::Coord& pos) {
        std::shared_ptr<obj::Object> pObj = ppt[current]->get_object(pos);
        if (!pObj) 
            throw std::runtime_error("(action) ERROR: No object has been found at the specified point");
        return ppt[current]->remove_object(pObj);
    }

    void Ppt::set_current(size_t pos) {
        if (pos >= ppt.size()) {
            throw std::out_of_range(
                "(doc) ERROR: Invalid slide index " + std::to_string(pos));
        }
        current = pos;
    }
    
    size_t Ppt::get_current() const {
        return current;
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

