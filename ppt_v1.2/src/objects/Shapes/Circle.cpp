#include <iostream>
#include <cassert>
#include "Shape.h"

namespace obj{

    Circle::Circle() : FilledShapes(), radius(1){
        pos={{0, 0}};
    }

    void Circle::create(const Position& coords) {
        assert(coords.size() == 2 && (pos[0].first - pos[1].first) == (pos[0].second - pos[1].second));
        pos = coords;
        radius = (pos[0].first - pos[1].first)/2;
    }

    double Circle::get_radius() const {
        return radius;
    }

    void Circle::set_radius(double rad){
        radius = rad;
    }
    void Circle::show() const {
        std::cout<< "Circle at (" << pos[0].first << ", " << pos[0].second << ") with\n" <<
            "filled: " << filled <<
            "\ncolor: " << ((filled) ? color : "none" )<<
            "\nborderline color: " << borderline_color <<
            "\nborderline width: " << borderline_width <<
            "\nradius" << radius <<
            "\ntext" << ((text.get_text() == "add text") ? "none" : text.get_text()) <<
            "\n---------------------\n";
    }
}