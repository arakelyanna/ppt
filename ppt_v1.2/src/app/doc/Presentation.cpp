#include "Presentation.h"
#include <stdexcept>

namespace doc {
    Ppt::Ppt(const std::string& path) : current(0) {
        if (path != "") {
            open(path);
        }
        ppt.push_back(Slide());
    }
    
    bool Ppt::save(const std::string& file) {
        //not implemented
        return true;
    }

    bool Ppt::open(const std::string& file) {
        //not implemented
        return true;
    }

    void Ppt::add_slide(Slide& slide, size_t pos) {
        ppt.insert(ppt.begin() + pos, std::move(slide));
    }
    
    void Ppt::remove_slide(size_t pos) {
        ppt.erase(ppt.begin() + pos);
    }
    
    void Ppt::add_object(std::unique_ptr<obj::Object> obj) {
        ppt[current].add_object(std::move(obj));
    }

    size_t Ppt::size() const {
        return ppt.size();
    }

    Slide& Ppt::operator[](size_t i) {
        if (i >= ppt.size()) throw std::runtime_error("ERROR: Invalid Slide ID!");
        return ppt[i];
    }

    const Slide& Ppt::operator[](size_t i) const {
        if (i >= ppt.size()) throw std::runtime_error("ERROR: Invalid Slide ID!");
        return ppt[i];
    }
}

