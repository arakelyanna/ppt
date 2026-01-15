#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    Triangle::Triangle() : FilledShapes() {
        pos={{0, 0}, {1, 1}, {0, 1}};
    }
    void Triangle::accept(const files::IVisitor& visitor) {
        visitor.visit(*this);
    }
    void Triangle::create(const Geometry& coords) {
        if(coords.size() != 3) throw std::runtime_error("(object) ERROR: The Coordinates for Triangle should be 3");
        pos = coords;
        sides[0] = std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
        sides[1] = std::sqrt(std::pow(pos[1].first-pos[2].first, 2)+std::pow(pos[1].second-pos[2].second, 2));
        sides[2] = std::sqrt(std::pow(pos[2].first-pos[0].first, 2)+std::pow(pos[2].second-pos[0].second, 2));
    }

    const std::string& Triangle::get_type() const {
        static const std::string type = "Triangle";
        return type;    
    }

    const std::array<double, 3>& Triangle::get_sides() const {
        return sides;
    }

}