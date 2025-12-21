#include "Text.h"
#include "../../app/printer/Visitor/Visitor.h"

namespace obj {
    Text::Text() : Object(), value("text"), size(11), color("black"), style("arial") {}
    
    Text::Text(const std::string& value, size_t size, const std::string& color, const std::string& style) :
        Object(), value(value), size(size), color(color), style(style) {}

    void Text::create(const Geometry& coords) {
        std::cout << coords.size() << '\n';
        if(coords.size() != 1) throw std::runtime_error("(object) ERROR: The Coordinates for Text should be 1");
        pos = coords;
    }

    void Text::accept(const out::IVisitor& visitor) {
        visitor.visit(*this);
    }

    void Text::set_value(const std::string& val) {
        if(val.size() > 100) throw std::runtime_error("(object) ERROR: The length of the text should not exceed 250");

        value = val;
    }

    void Text::set_size(size_t size) {
        if (size < 1) this->size = 1;
        else if (size >= 500) this->size = 500;
        else this->size = size;
    }

    void Text::set_style(const std::string& value) {
        auto lookUp = std::find(styles.begin(), styles.end(), value);
        if (lookUp == styles.end()) std::cerr << ("ERROR: Color not supported\n");
        this->style = value;
    }

    void Text::set_color(const std::string& value) {
        auto lookUp = std::find(colors.begin(), colors.end(), value);
        if (lookUp == colors.end()) std::cerr << ("ERROR: Color not supported\n");
        this->color = value;
    }

    const std::string& Text::get_color() const {
        return color;
    }

    const std::string& Text::get_text() const {
        return value;
    }

    const std::string& Text::get_style() const {
        return style;
    }

    size_t Text::get_size() const {
        return size;
    }

    const Geometry& Text::get_geometry() const {
        return pos;
    }



}