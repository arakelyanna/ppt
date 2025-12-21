#include <algorithm>
#include "Shape.h"

namespace obj{

    Arrow::Arrow() : Line() {
        pointing = "clockwise";
    }

    void Arrow::accept(const out::IVisitor& visitor) {
        visitor.visit(*this);
    }

    void Arrow::create(const Geometry& coords){
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for Line should be 2");

        pos = coords;
        length =  std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
        
        if (pos[0].second > pos[1].second)
            pointing = "clockwise";
        else pointing = "counter-clockwise";
    }

    const std::string& Arrow::get_type() const {
        static const std::string type = "Arrow";
        return type;    
    }

    void Arrow::point_other_way(){
        std::swap(pos[0], pos[1]);
    }

    const std::string& Arrow::points_to() const {
        return pointing;
    }
    
}