#include "Shape.h"
#include <iostream>
#include <stdexcept>

namespace obj {
    Picture::Picture(const std::string& file): FilledShapes(), height(1), width(1){
        pos={{0, 0}, {1, 1}};
        path = file;
        pic.open(path);
    }
    
    void Picture::accept(const out::IVisitor& visitor) {
        visitor.visit(*this);
    }

    void Picture::create(const Geometry& coords) {
        if (!pic) throw std::runtime_error("(object) ERROR: Picture file not found");
        if(coords.size() != 2) throw std::runtime_error("(object) ERROR: The Coordinates for Picture should be 2");
        pos = coords;
        width= std::abs(pos[0].first-pos[1].first);
        height= std::abs(pos[0].second-pos[1].second);
    }
    
    void Picture::set_color(const std::string& color) { }

    const std::string& Picture::get_type() const {
        static const std::string type = "Picture";
        return type;    
    }

    const std::string& Picture::get_path() const {
        return path;
    }

    
    double Picture::get_height() const {
        return height;
    }

    double Picture::get_width() const {
        return width;
    }
    
    void Picture::set_height(double value) {
        height = value;
        pos[1].second += pos[0].second;
    }

    void Picture::set_width(double value) {
        width = value;
        pos[1].first += pos[0].first;
    }
}