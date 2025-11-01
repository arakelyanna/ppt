#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    Triangle::Triangle() : FilledShapes() {
        pos={{0, 0}, {1, 1}, {0, 1}};
    }

    void Triangle::create(const Position& coords) {
        assert(coords.size() == 3);
        pos = coords;
        sides[0] = std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
        sides[1] = std::sqrt(std::pow(pos[1].first-pos[2].first, 2)+std::pow(pos[1].second-pos[2].second, 2));
        sides[2] = std::sqrt(std::pow(pos[2].first-pos[0].first, 2)+std::pow(pos[2].second-pos[0].second, 2));
    }
    void Triangle::show() const {
        std::cout<< "Triangle at (" << pos[0].first << ", " << pos[0].second << ") with\n" <<
            "filled: " << filled <<
            "\ncolor: " << ((filled) ? color : "none" )<<
            "\nborderline color: " << borderline_color <<
            "\nborderline width: " << borderline_width <<
            "\nsides" << sides[0] << ", " <<sides[1] << ", " << sides[2] << "\n" <<
            "\nsides" << sides[0] << ", " <<sides[1] << ", " << sides[2] << "\n" <<
            "\n---------------------\n";
    }

    const std::array<double, 3>& Triangle::get_sides() const {
        return sides;
    }

}