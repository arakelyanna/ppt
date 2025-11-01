#include <cassert>
#include "Shape.h"

namespace obj{

    Square::Square() : FilledShapes(){ }

    void Square::create(const Position& coords) {
        assert(coords.size() == 2);
        if ((coords[0].first - coords[1].first) != (coords[0].second-coords[1].second))
        {
            side = std::max(std::abs(coords[0].first - coords[1].first), std::abs(coords[0].second-coords[1].second));
            pos[0] = coords[0];
            pos[1] = coords[0];
            pos[1].first = pos[0].first+side;
            pos[1].second += pos[0].second+side;
            return;
        }
        
        pos = coords;
        side = std::abs(pos[0].first-pos[1].first);
    }

    double Square::get_side() const {
        return side;
    }
    void Square::set_side(double value){
        side = value;
        pos[1].first = pos[0].first+value;
        pos[1].second += pos[0].second+value;
    }

    void Square::show() const {
        std::cout<< "Square at (" << pos[0].first << ", " << pos[0].second << ") with\n" <<
            "filled: " << filled <<
            "\ncolor: " << ((filled) ? color : "none" )<<
            "\nborderline color: " << borderline_color <<
            "\nborderline width: " << borderline_width <<
            "\nside" << side <<
            "\ntext" << ((text.get_text() == "add text") ? "none" : text.get_text()) <<
            "\n---------------------\n";
    }
    
}