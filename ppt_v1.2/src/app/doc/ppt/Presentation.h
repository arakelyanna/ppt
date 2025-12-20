#pragma once
#include <stdexcept>
#include "../Slide/Slide.h"

namespace doc {
    class Ppt {
    public:
        Ppt(const std::string& path);
        void setFilePath(const std::string& file);
        void add_slide(std::shared_ptr<Slide> slide, size_t pos = 0);
        std::shared_ptr<Slide> remove_slide(size_t pos = 0);

        void add_object(std::shared_ptr<obj::Object> obj);
        std::shared_ptr<obj::Object> remove_object(const obj::Coord& pos);
        
        size_t size() const;
        
        std::shared_ptr<Slide> operator[](size_t i);
        std::shared_ptr<Slide> const operator[](size_t i) const;

    private:
        std::vector<std::shared_ptr<Slide>> ppt;
        size_t current;
        std::string filePath;
    };
}