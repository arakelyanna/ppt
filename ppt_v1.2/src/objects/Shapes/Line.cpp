#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    void Line::create(const Geometry& coords){
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for Line should be 3");
        assert(coords.size() == 2);
        pos = coords;
        length =  std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
    }

    const std::string& Line::get_type() const {
        static const std::string type = "Line";
        return type;    
    }

    double Line::get_length() const {
        return length;
    }

    double Line::get_width() const {
        return width;
    }
    

    void Line::set_width(double) {

    }

}