#include "Picture.h"
#include <iostream>
#include <stdexcept>

namespace obj {
    void Picture::create(const Position& coords, const std::string& file) {
        assert(coords.size() == 2);
        path = file;
        pos = coords;
        pic.open(path);
        if (!pic) throw std::runtime_error("ERROR: Picture file not found\n");
    }
    
    void Picture::show() const {
        std::cout << "Picture at (" << pos[0].first << ", " << pos[0].second << ") with\n" 
            "\npath: " << path  <<
            "\n---------------------\n";
    }
    
    double Picture::get_height() const {
        return height;
    }

    double Picture::get_width() const {
        return width;
    }
    
    void Picture::set_height(double value) {
        height = value;
        pos[1].second += pos[0].second;
    }

    void Picture::set_width(double value) {
        width = value;
        pos[1].first += pos[0].first;
    }
}