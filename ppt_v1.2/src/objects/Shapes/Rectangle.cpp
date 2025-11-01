#include <iostream>
#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    Rectangle::Rectangle() : FilledShapes(), height(1), width(1){
        pos={{0, 0}, {1, 1}};
    }

    void Rectangle::create(const Position& coords) {
        assert(coords.size() == 2);
        pos = coords;
        width= std::abs(pos[0].first-pos[1].first);
        height= std::abs(pos[0].second-pos[1].second);
    }

    double Rectangle::get_height() const {
        return height;
    }

    double Rectangle::get_width() const {
        return height;
    }
    
    void Rectangle::set_height(double value) {
        height = value;
        pos[1].second += pos[0].second;
    }

    void Rectangle::set_width(double value) {
        width = value;
        pos[1].first += pos[0].first;
    }
    void Rectangle::show() const {
        std::cout<< "Rectangle at (" << pos[0].first << ", " << pos[0].second << ") with\n" <<
            "filled: " << filled <<
            "\ncolor: " << ((filled) ? color : "none" )<<
            "\nborderline width: " << borderline_width <<
            "\nborderline color: " << borderline_color <<
            "\nheight" << height <<
            "\nwidth" << width <<
            "\ntext" << ((text.get_text() == "add text") ? "none" : text.get_text()) <<
            "\n---------------------\n";
    }
}