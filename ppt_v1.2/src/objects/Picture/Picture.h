#pragma once
#include <fstream>
#include <string>
#include <cassert>
#include "../Object.h"

namespace obj {
    class Picture : public Object {
    public:
        Picture() = default;
        
        void create(const Position& coords, const std::string& file);
        void show() const override;
        
        double get_height() const;
        double get_width() const;
        void set_height(double value);
        void set_width(double value);
        
    private:
        Position pos;
        std::fstream pic;
        std::string path;
        double height;
        double width;
    };
}