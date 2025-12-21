#include <iostream>
#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    Rectangle::Rectangle() : FilledShapes(), height(1), width(1){
        pos={{0, 0}, {1, 1}};
    }

    void Rectangle::accept(const out::IVisitor& visitor) {
        visitor.visit(*this);
    }

    void Rectangle::create(const Geometry& coords) {
        assert(coords.size() == 2);
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for Rectangle should be 2");
        pos = coords;
        width= std::abs(pos[0].first-pos[1].first);
        height= std::abs(pos[0].second-pos[1].second);
    }

    const std::string& Rectangle::get_type() const {
        static const std::string type = "Rectangle";
        return type;    
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
}