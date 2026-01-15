#include <cassert>
#include "Shape.h"

namespace obj{

    Square::Square() : FilledShapes(){ }

    void Square::accept(const files::IVisitor& visitor) {
        visitor.visit(*this);
    }

    void Square::create(const Geometry& coords) {
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for Square should be 2");
        
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

    const std::string& Square::get_type() const {
        static const std::string type = "Square";
        return type;    
    }

    double Square::get_side() const {
        return side;
    }
    void Square::set_side(double value){
        side = value;
        pos[1].first = pos[0].first+value;
        pos[1].second += pos[0].second+value;
    }

}