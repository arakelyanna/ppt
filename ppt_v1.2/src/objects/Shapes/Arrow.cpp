#include <algorithm>
#include "Shape.h"

namespace obj{

    Arrow::Arrow() : Line() {
        pointing = "clockwise";
    }
    void Arrow::create(const Position& coords){
        assert(coords.size() == 2);
        pos = coords;
        length =  std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
        
        if (pos[0].second > pos[1].second)
            pointing = "clockwise";
        else pointing = "counter-clockwise";
    }
    void Arrow::point_other_way(){
        std::swap(pos[0], pos[1]);
    }
    const std::string& Arrow::points_to() const {
        return pointing;
    }
    void Arrow::show() const {
        std::cout<< "Arrow at (" << pos[0].first << ", " << pos[0].second << ")\n" <<
            "color: " << color<<
            "\nwidth: " << width <<
            "\nlength: " << length <<
            "\npointing to " << pointing <<
            "\n---------------------\n";
    }
}