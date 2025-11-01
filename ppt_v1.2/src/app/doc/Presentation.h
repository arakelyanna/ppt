#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "Slide.h"

namespace doc {
    class Ppt {
    public:
        Ppt(const std::string& path = "");
        
        bool save(const std::string& file);
        bool open(const std::string& file);
        
        void add_slide(Slide& slide, size_t pos = 0);
        void remove_slide(size_t pos = 0);
        void add_object(std::unique_ptr<obj::Object> obj);
        
        size_t size() const;
        
        Slide& operator[](size_t i);
        const Slide& operator[](size_t i) const;
        
    private:
        std::vector<Slide> ppt;
        size_t current;
        std::string filePath;
    };
}