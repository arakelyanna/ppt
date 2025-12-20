#include <iostream>
#include <cassert>
#include "Shape.h"

namespace obj{

    Circle::Circle() : FilledShapes(), radius(1){
        pos={{0, 0}};
    }

    void Circle::create(const Geometry& coords) {
        assert(coords.size() == 2 && (pos[0].first - pos[1].first) == (pos[0].second - pos[1].second));
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for triangle should be 3");
        else if ((pos[0].first - pos[1].first) != (pos[0].second - pos[1].second)) throw std::runtime_error("(object) ERROR: Cannot construct Circle with these coordinates");
        pos = coords;
        radius = (pos[0].first - pos[1].first)/2;
    }

    const std::string& Circle::get_type() const {
        static const std::string type = "Circle";
        return type;    
    }

    double Circle::get_radius() const {
        return radius;
    }

    void Circle::set_radius(double rad){
        radius = rad;
    }
    
}