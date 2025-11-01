#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    void Line::create(const Position& coords){
        assert(coords.size() == 2);
        pos = coords;
        length =  std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
    }

    double Line::get_length() const {
        return length;
    }

    double Line::get_width() const {
        return width;
    }
    void Line::show() const {
        std::cout<< "Line at (" << pos[0].first << ", " << pos[0].second << ")\n" <<
            "color: " << color<<
            "\nwidth: " << width <<
            "\nlength: " << length <<
            "\n---------------------\n";
    }

    void Line::set_width(double) {

    }

}